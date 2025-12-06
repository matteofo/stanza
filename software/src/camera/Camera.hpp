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

		static bool allocateBuffers();
		static bool requestFrames();

		static void _requestHandler(libcamera::Request* request);	

		static const char* _fourcc(u32 code);	
	public:
		static bool init();
		static void end();
		
		static std::optional<std::vector<std::shared_ptr<libcamera::Camera>>> enumerate();
		static bool useCamera(std::shared_ptr<libcamera::Camera> camera);
	};
}