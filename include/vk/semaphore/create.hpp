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

		template<possibly_guarded_handle_of<vk::device> Device>
		vk::expected<handle<vk::semaphore>>
		operator () (Device&& device) const {
			vk::semaphore_create_info ci{};

			handle<vk::semaphore> semaphore;

			vk::result result {
				vkCreateSemaphore(
					vk::get_handle(device),
					&ci,
					nullptr,
					&semaphore
				)
			};

			if(result.error()) return result;
			return handle<vk::semaphore>{ semaphore };
		}

	}; // create_t<semaphore>

} // vk