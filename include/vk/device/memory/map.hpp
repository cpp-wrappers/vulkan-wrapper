#pragma once

#include "handle.hpp"

#include "../../function.hpp"
#include "../../device/handle.hpp"
#include "../../result.hpp"
#include "../../memory_offset.hpp"
#include "../../memory_size.hpp"
#include "../../unexpected_handler.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

extern "C" VK_ATTR int32 VK_CALL vkMapMemory(
	handle<vk::device> device,
	handle<vk::device_memory> memory,
	vk::memory_offset offset,
	vk::memory_size size,
	int32 flags,
	void** dataata
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_one_possibly_guarded_handle_of<vk::device_memory>,
		types::are_may_contain_one_decayed<vk::memory_offset>,
		types::are_contain_one_decayed<vk::memory_size>,
		types::are_contain_one_decayed<void**>
	>::for_types<Args...>
	vk::result try_map_device_memory(Args&&... args) {
		auto& device = elements::possibly_guarded_handle_of<
			vk::device
		>(args...);

		auto& device_memory = elements::possibly_guarded_handle_of<
			vk::device_memory
		>(args...);

		vk::memory_offset offset{ 0 };

		if constexpr (
			types::are_contain_decayed<vk::memory_offset>::for_types<Args...>
		) { offset = elements::decayed<vk::memory_offset>(args...); }

		vk::memory_size size = elements::decayed<vk::memory_size>(args...);

		void** data = data = elements::decayed<void**>(args...);

		return {
			(int32) vkMapMemory(
				vk::get_handle(device),
				vk::get_handle(device_memory),
				offset,
				size,
				0,
				data
			)
		};
	}

	template<typename... Args>
	void map_device_memory(Args&&... args) {
		vk::result result = vk::try_map_device_memory(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk