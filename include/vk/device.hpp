#pragma once

#include <core/forward.hpp>
#include "shader/module/create.hpp"
#include "shader_module.hpp"

namespace vk {

	namespace internal {
		struct device;
	}

	class device {
		vk::internal::device& m_device;
	public:

		device() = delete;
	
	};

}