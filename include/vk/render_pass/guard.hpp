#pragma once

#include "handle.hpp"
#include "../device/handle.hpp"
#include "../shared/guarded_handle.hpp"

namespace vk {

	template<>
	class guarded_handle<vk::render_pass> {
		vk::handle<vk::render_pass> render_pass;
		vk::handle<vk::device> device;
	public:

		guarded_handle(vk::handle<vk::render_pass> render_pass, vk::handle<vk::device> device)
			: render_pass{ render_pass }, device{ device }
		{}

		guarded_handle(guarded_handle&& other)
			: render_pass{ exchange(other.render_pass.value, 0) }, device{ other.device }
		{}

		~guarded_handle() {
			if(render_pass.value) {
				vkDestroyRenderPass(
					(VkDevice) device.value,
					(VkRenderPass) exchange(render_pass.value, 0),
					nullptr
				);
			}
		}

		const vk::handle<vk::render_pass>& object() const { return render_pass; }
	};
}