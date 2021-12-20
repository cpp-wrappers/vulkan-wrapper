#pragma once

#include <core/exchange.hpp>

#include "handle.hpp"
#include "../device/handle.hpp"
#include "../shared/headers.hpp"

namespace vk {

	struct framebuffer_guard {
		vk::framebuffer framebuffer;
		vk::device device;

		framebuffer_guard() = default;

		framebuffer_guard(vk::framebuffer framebuffer, vk::device device)
			: framebuffer{ framebuffer }, device{ device }
		{}

		template<typename... Args>
		framebuffer_guard(vk::device device, Args&&... args)
			: framebuffer{ vk::create_framebuffer(forward<Args>(args)..., device) }, device{ device }
		{}

		framebuffer_guard(framebuffer_guard&& other)
			: framebuffer{ exchange(other.framebuffer.handle, 0) }, device{ other.device }
		{}

		vk::framebuffer_guard& operator = (framebuffer_guard&& other) {
			framebuffer.handle = exchange(other.framebuffer.handle, 0);
			device = other.device;
			return *this;
		}

		~framebuffer_guard() {
			if(framebuffer.handle) {
				vkDestroyFramebuffer(
					(VkDevice) device.handle,
					(VkFramebuffer) exchange(framebuffer.handle, 0),
					nullptr
				);
			}
		}

		const vk::framebuffer& object() const {
			return framebuffer;
		}
	};
}