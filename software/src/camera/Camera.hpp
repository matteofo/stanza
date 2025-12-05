#pragma once
#include <iostream>
#include <memory>
#include <optional>

#include <libcamera/libcamera.h>

#include <util/Logger.hpp>

namespace stanza {
	class Camera {
	private:
		static std::shared_ptr<libcamera::Camera> _camera;
		static std::unique_ptr<libcamera::CameraManager> _mgr;
		static std::unique_ptr<libcamera::CameraConfiguration> _config;
		
		static Logger logger;
		static bool ready;
	public:
		static bool init();
		static void end();
		
		static std::optional<std::vector<std::shared_ptr<libcamera::Camera>>> enumerate();
		static void useCamera(std::shared_ptr<libcamera::Camera> camera);
	
		static bool allocateBuffers();
	};
}