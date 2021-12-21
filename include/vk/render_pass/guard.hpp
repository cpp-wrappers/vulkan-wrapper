#pragma once

#include "handle.hpp"
#include "../device/handle.hpp"
#include "../shared/guarded.hpp"

namespace vk {

	template<>
	class guarded<vk::render_pass> {
		vk::render_pass render_pass;
		vk::device device;
	public:

		guarded(vk::render_pass render_pass, vk::device device)
			: render_pass{ render_pass }, device{ device }
		{}

		guarded(guarded&& other)
			: render_pass{ exchange(other.render_pass.handle, 0) }, device{ other.device }
		{}

		~guarded() {
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