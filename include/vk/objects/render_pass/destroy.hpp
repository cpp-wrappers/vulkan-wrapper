#pragma once

#include "../../object/destroy_or_free.hpp"
#include "../device/handle.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::render_pass> {

		void operator () (vk::handle<vk::device> device, vk::handle<vk::render_pass> render_pass) const {
			vkDestroyRenderPass(
				(VkDevice) device.value,
				(VkRenderPass) render_pass.value,
				nullptr
			);
		}

	};

}