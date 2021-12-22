#pragma once

#include <core/exchange.hpp>

#include "handle.hpp"
#include "../device/handle.hpp"
#include "../shared/headers.hpp"
#include "../shared/guarded.hpp"

namespace vk {
	
	template<>
	class guarded<vk::framebuffer> {
		vk::handle<vk::framebuffer> framebuffer;
		vk::handle<vk::device> device;

	public:

		guarded() = default;

		guarded(vk::handle<vk::framebuffer> framebuffer, vk::handle<vk::device> device)
			: framebuffer{ framebuffer }, device{ device }
		{}

		guarded(guarded&& other)
			: framebuffer{ exchange(other.framebuffer.value, 0) }, device{ other.device }
		{}

		guarded& operator = (guarded&& other) {
			framebuffer.value = exchange(other.framebuffer.value, 0);
			device = other.device;
			return *this;
		}

		~guarded() {
			if(framebuffer.value) {
				vkDestroyFramebuffer(
					(VkDevice) device.value,
					(VkFramebuffer) exchange(framebuffer.value, 0),
					nullptr
				);
			}
		}

		const vk::handle<vk::framebuffer>& object() const {
			return framebuffer;
		}
	};
}