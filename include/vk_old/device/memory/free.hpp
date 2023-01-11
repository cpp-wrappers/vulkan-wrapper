#pragma once

#include "handle.hpp"

#include "../handle.hpp"
#include "../../function.hpp"
#include "../../destroy_or_free.hpp"

extern "C" VK_ATTR void VK_CALL vkFreeMemory(
	handle<vk::device>        device,
	handle<vk::device_memory> memory,
	const void*               allocator
);

namespace vk {

	template<>
	struct vk::free_t<vk::device_memory> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<handle<vk::device>>,
			types::are_contain_one_decayed<handle<vk::device_memory>>
		>::for_types<Args...>
		void operator () (Args&&... args) const {
			auto device = elements::decayed<handle<vk::device>>(args...);
			auto device_memory {
				elements::decayed<handle<vk::device_memory>>(args...)
			};

			vkFreeMemory(device, device_memory, nullptr);
		} 

	};

} // vk