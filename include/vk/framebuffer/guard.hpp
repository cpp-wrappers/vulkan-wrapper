#pragma once

#include <core/exchange.hpp>

#include "handle.hpp"
#include "../device/handle.hpp"
#include "../shared/headers.hpp"
#include "../shared/guarded.hpp"

namespace vk {
	
	template<>
	class guarded<vk::framebuffer> {
		vk::framebuffer framebuffer;
		vk::device device;

	public:

		guarded() = default;

		guarded(vk::framebuffer framebuffer, vk::device device)
			: framebuffer{ framebuffer }, device{ device }
		{}

		template<typename... Args>
		guarded(vk::device device, Args&&... args)
			: framebuffer{ vk::create_framebuffer(forward<Args>(args)..., device) }, device{ device }
		{}

		guarded(guarded&& other)
			: framebuffer{ exchange(other.framebuffer.handle, 0) }, device{ other.device }
		{}

		guarded& operator = (guarded&& other) {
			framebuffer.handle = exchange(other.framebuffer.handle, 0);
			device = other.device;
			return *this;
		}

		~guarded() {
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