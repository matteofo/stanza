#include <camera/Camera.hpp>

namespace stanza {
    std::shared_ptr<libcamera::Camera> Camera::_camera;
    std::unique_ptr<libcamera::CameraManager> Camera::_mgr;
	std::unique_ptr<libcamera::CameraConfiguration> Camera::_config;
    libcamera::FrameBufferAllocator* Camera::_allocator;
    libcamera::Stream* Camera::_stream;
    std::vector<std::unique_ptr<libcamera::Request>> Camera::_requests;

    Logger Camera::logger;
    bool Camera::ready;
    Texture* Camera::texture;

    bool Camera::init() {
        setenv("LIBCAMERA_LOG_LEVELS", "ERROR", false);

        Camera::ready = false;
        logger.setClassName("Camera");
        logger.log("Initializing Camera!");

        Camera::_mgr = std::make_unique<libcamera::CameraManager>();
        if (Camera::_mgr == nullptr) {
            logger.error("Failed to initialize libcamera!");
            return false;
        }

        int res = Camera::_mgr->start();
        if (res != 0) {
            logger.error("Failed to initialize libcamera! (error {})", res);
            return false;
        }

        Camera::ready = true;
        return true;
    }

    void Camera::end() {
        if (!Camera::ready) return;
        logger.log("Cleaning up Camera...");

        if (Camera::_camera) {
            Camera::_camera->release();
            Camera::_camera.reset();
        }

        Camera::_mgr->stop();
    }

    std::optional<std::vector<std::shared_ptr<libcamera::Camera>>> Camera::enumerate() {        
        if (!Camera::ready) {
            logger.error("Not initialized!");
            return std::nullopt;
        }
        
        auto cameras = Camera::_mgr->cameras();
        if (cameras.empty()) {
            logger.warn("No cameras found!");
            Camera::_mgr->stop();
            return std::nullopt;
        }

        logger.log("Found {} camera(s)!", cameras.size());
        return cameras;
    }

    bool Camera::useCamera(std::shared_ptr<libcamera::Camera> camera) {
        Camera::_camera = Camera::_mgr->get(camera->id());
        int acquired = Camera::_camera->acquire();
        if (acquired != 0) {
            logger.error("Failed to acquire camera {}! ({})", camera->id(), acquired);
            return false;
        } else {
            logger.log("Acquired camera {}!", camera->id());
        }

        Camera::_config = Camera::_camera->generateConfiguration({ libcamera::StreamRole::Viewfinder });
        if (!Camera::_config) {
            logger.error("Camera {} doesn't support the required configuration!", camera->id());
            return false;
        }

        libcamera::StreamConfiguration& streamConfig = Camera::_config->at(0);
        streamConfig.pixelFormat = streamConfig.pixelFormat.fromString("RGB888");
        logger.warn("IS VALID: {}, {}", Camera::_fourcc(streamConfig.pixelFormat.fourcc()), streamConfig.pixelFormat.isValid());

        Camera::_config->validate();

        const char* format = Camera::_fourcc(streamConfig.pixelFormat.fourcc());
        logger.log("Validated camera configuration ({}): {}", format, streamConfig.toString());
        Camera::_camera->configure(Camera::_config.get());

        u32 width = streamConfig.size.width, height = streamConfig.size.height;
        unsigned int stride = streamConfig.stride;
        Camera::texture = new Texture(width, height, stride);
        if (!Camera::texture) {
            logger.error("Failed to allocate texture of size {}x{}!", height, width);
            return false;
        }

        logger.log("Allocated texture of size {}x{}, {} bpp", width, height, stride);

        return Camera::allocateBuffers();
    }

    bool Camera::allocateBuffers() {
        Camera::_allocator = new libcamera::FrameBufferAllocator(Camera::_camera);

        for (libcamera::StreamConfiguration& cfg : *Camera::_config) {
            int res = Camera::_allocator->allocate(cfg.stream());
            if (res < 0) {
                logger.error("Failed to allocate framebuffer! ({})", res);
                return false;
            }

            size_t allocated = Camera::_allocator->buffers(cfg.stream()).size();
            logger.log("Allocated {} framebuffers for the camera stream!", allocated);
        }

        return Camera::requestFrames();
    }

    bool Camera::requestFrames() {
        libcamera::StreamConfiguration& streamConfig = Camera::_config->at(0);
        Camera::_stream = streamConfig.stream();
        const std::vector<std::unique_ptr<libcamera::FrameBuffer>> &buffers = Camera::_allocator->buffers(Camera::_stream);

        for (u64 i = 0; i < buffers.size(); ++i) {
            std::unique_ptr<libcamera::Request> request = Camera::_camera->createRequest();
            if (!request) {
                logger.error("Couldn't create frame request for camera {}!", Camera::_camera->id());
                return false;
            }

            const std::unique_ptr<libcamera::FrameBuffer> &buffer = buffers[i];
            int res = request->addBuffer(Camera::_stream, buffer.get());
            if (res < 0) {
                logger.log("Couldn't assign buffer {} to request for camera {}!", i, Camera::_camera->id());
                return false;
            }

            logger.log("Queued framebuffer request {}", i);

            Camera::_requests.push_back(std::move(request));
        }

        Camera::_camera->requestCompleted.connect(Camera::_requestHandler);
        Camera::_camera->start();

        for (std::unique_ptr<libcamera::Request>& request : Camera::_requests) {
            Camera::_camera->queueRequest(request.get());
        }

        return true;
    }

    void Camera::_requestHandler(libcamera::Request* request) {
        if (request->status() == libcamera::Request::RequestCancelled) {
            Camera::logger.warn("A request was cancelled!");
            return;
        }

        const std::map<const libcamera::Stream*, libcamera::FrameBuffer*> &buffers = request->buffers();
        for (auto bufferPair : buffers) {
            libcamera::FrameBuffer* buffer = bufferPair.second;
            const libcamera::FrameMetadata &metadata = buffer->metadata();

            for (const auto& plane : buffer->planes()) {
                void* planeData = mmap(nullptr, plane.length,
                    PROT_READ | PROT_WRITE, MAP_SHARED, plane.fd.get(), plane.offset);

                if (!planeData) {
                    logger.error("Failed to mmap() a buffer plane!");
                    continue;
                }

                // logger.log("Plane length: {}", plane.length);

                munmap(planeData, plane.length);
            }
        }

        // Camera::logger.log("Got a frame!");

        request->reuse(libcamera::Request::ReuseBuffers);
        Camera::_camera->queueRequest(request);
    }

    const char* Camera::_fourcc(u32 code) {
        std::string format;
        for (int i = 3; i >= 0; i--) {
            format += (char) (code >> (8 * i)) & 0xff;
        }

        logger.warn("{}", format);

        return format.c_str();
    }
}