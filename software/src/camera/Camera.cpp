#include <camera/Camera.hpp>

namespace stanza {
    std::shared_ptr<libcamera::Camera> Camera::_camera;
    std::unique_ptr<libcamera::CameraManager> Camera::_mgr;
	std::unique_ptr<libcamera::CameraConfiguration> Camera::_config;

    Logger Camera::logger;
    bool Camera::ready;

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

    void Camera::useCamera(std::shared_ptr<libcamera::Camera> camera) {
        Camera::_camera = Camera::_mgr->get(camera->id());
        int acquired = Camera::_camera->acquire();
        if (acquired != 0) {
            logger.error("Failed to acquire camera {}! ({})", camera->id(), acquired);
        } else {
            logger.log("Acquired camera {}!", camera->id());
        }

        Camera::_config = Camera::_camera->generateConfiguration({ libcamera::StreamRole::Viewfinder });
        if (!Camera::_config) {
            logger.error("Camera {} doesn't support the required configuration!", camera->id());
        }

        libcamera::StreamConfiguration& streamConfig = Camera::_config->at(0);
        Camera::_config->validate();
        logger.log("Validated camera configuration: {}", streamConfig.toString());
    
        Camera::_camera->configure(Camera::_config.get());
    }

    bool Camera::allocateBuffers() {
        libcamera::FrameBufferAllocator* allocator = new libcamera::FrameBufferAllocator(Camera::_camera);

        for (libcamera::StreamConfiguration& cfg : *Camera::_config) {
            int res = allocator->allocate(cfg.stream());
            if (res < 0) {
                logger.error("Failed to allocate framebuffer! ({})", res);
                return false;
            }

            size_t allocated = allocator->buffers(cfg.stream()).size();
            logger.log("Allocated {} framebuffers for the camera stream!", allocated);
        }

        return true;
    }
}