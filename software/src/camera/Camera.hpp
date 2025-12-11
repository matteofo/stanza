#pragma once
#include <iostream>
#include <functional>
#include <memory>
#include <optional>
#include <sys/mman.h>

#include <libcamera/libcamera.h>

#include <graphics/Texture.hpp>
#include <util/Logger.hpp>
#include <util/types.hpp>

namespace stanza {
	typedef void (*FrameRequestHandler)(libcamera::Request*);

	class Camera {
	private:
		static std::shared_ptr<libcamera::Camera> _camera;
		static std::unique_ptr<libcamera::CameraManager> _mgr;
		static std::unique_ptr<libcamera::CameraConfiguration> _config;
		static libcamera::FrameBufferAllocator* _allocator;
		static libcamera::Stream* _stream;
		static std::vector<std::unique_ptr<libcamera::Request>> _requests;

		static Logger logger;
		static bool ready;

		static Texture* texture;
		static std::function<void(Texture*)> textureCallback;

		static bool allocateBuffers();
		static bool requestFrames();

		static void _requestHandler(libcamera::Request* request);	

		static void _fourcc(char format[5], u32 code);
	public:
		static bool init();
		static void end();
		
		
		static std::optional<std::vector<std::shared_ptr<libcamera::Camera>>> enumerate();
		
		static bool useCamera(std::shared_ptr<libcamera::Camera> camera);
		static bool useCamera(std::shared_ptr<libcamera::Camera> camera, int cameraWidth, int cameraHeight, bool rotate);
		
		static Texture* getTexture();
		static void onFrame(std::function<void(Texture*)> callback);

		
		static const libcamera::ControlInfoMap& getControls();
		
		template<typename T, typename V>
		static void setControl(const libcamera::Control<T> &ctrl, const V& value)  {
			for (auto& request : Camera::_requests) {
				request->controls().set(ctrl, value);
			}
    	}
	};
}