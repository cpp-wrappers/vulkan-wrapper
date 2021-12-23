#pragma once

#include <core/exchange.hpp>

#include "handle.hpp"
#include "../device/handle.hpp"
#include "../shared/headers.hpp"
#include "../shared/guarded_handle.hpp"

namespace vk {
	
	template<>
	class guarded_handle<vk::framebuffer> {
		vk::handle<vk::framebuffer> framebuffer;
		vk::handle<vk::device> device;

	public:

		guarded_handle() = default;

		guarded_handle(vk::handle<vk::framebuffer> framebuffer, vk::handle<vk::device> device)
			: framebuffer{ framebuffer }, device{ device }
		{}

		guarded_handle(guarded_handle&& other)
			: framebuffer{ exchange(other.framebuffer.value, 0) }, device{ other.device }
		{}

		guarded_handle& operator = (guarded_handle&& other) {
			framebuffer.value = exchange(other.framebuffer.value, 0);
			device = other.device;
			return *this;
		}

		~guarded_handle() {
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