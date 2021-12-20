#pragma once

#include "handle.hpp"
#include "../device/handle.hpp"

namespace vk {
	class render_pass_guard {
		vk::render_pass render_pass;
		vk::device device;
	public:

		render_pass_guard(vk::render_pass render_pass, vk::device device)
			: render_pass{ render_pass }, device{ device }
		{}

		render_pass_guard(render_pass_guard&& other)
			: render_pass{ exchange(other.render_pass.handle, 0) }, device{ other.device }
		{}

		~render_pass_guard() {
			if(render_pass.handle) {
				vkDestroyRenderPass(
					(VkDevice) device.handle,
					(VkRenderPass) exchange(render_pass.handle, 0),
					nullptr
				);
			}
		}

		const vk::render_pass& object() const { return render_pass; }
	};
}