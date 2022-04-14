#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include "../create_or_allocate.hpp"
#include "../device/handle.hpp"
#include "../function.hpp"

extern "C" VK_ATTR int32 VK_CALL vkCreateSemaphore(
	handle<vk::device> device,
	const vk::semaphore_create_info* create_info,
	const void* allocator,
	handle<vk::semaphore>* semaphore
);

namespace vk {

	template<>
	struct vk::create_t<vk::semaphore> {

		vk::expected<handle<vk::semaphore>>
		operator () (handle<vk::device> device) const {
			vk::semaphore_create_info ci{};

			handle<vk::semaphore> semaphore;

			vk::result result {
				vkCreateSemaphore(
					device,
					&ci,
					nullptr,
					&semaphore
				)
			};

			if(result.error()) return result;

			return semaphore;
		}

	}; // create_t<semaphore>

} // vk