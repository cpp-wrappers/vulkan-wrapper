#pragma once

#pragma once

#include "../destroy.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::graphics_pipeline> {
		void operator() (vk::handle<vk::device> device, vk::handle<vk::graphics_pipeline> pipeline) const {
			vk::destroy<vk::pipeline>(device, vk::handle<vk::pipeline>{ pipeline.value });
		}
	};

}