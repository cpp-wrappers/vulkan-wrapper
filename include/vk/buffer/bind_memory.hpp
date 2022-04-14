#pragma once

#include "handle.hpp"

#include "../device/handle.hpp"
#include "../result.hpp"
#include "../memory_offset.hpp"
#include "../unexpected_handler.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

extern "C" VK_ATTR int32 VK_CALL vkBindBufferMemory(
	handle<vk::device> device,
	handle<vk::buffer> buffer,
	handle<vk::device_memory> memory,
	vk::memory_offset memory_offset
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::device>>,
		types::are_contain_one_decayed<handle<vk::buffer>>,
		types::are_contain_one_decayed<handle<vk::device_memory>>,
		types::are_may_contain_one_decayed<vk::memory_offset>
	>::for_types<Args...>
	vk::result try_bind_buffer_memory(Args&&... args) {
		auto device = elements::decayed<handle<vk::device>>(args...);
		auto buffer = elements::decayed<handle<vk::buffer>>(args...);

		auto device_memory {
			elements::decayed<handle<vk::device_memory>>(args...)
		};

		vk::memory_offset offset{ 0 };
		
		if constexpr (
			types::are_contain_decayed<vk::memory_offset>::for_types<Args...>
		) { offset = elements::decayed<vk::memory_offset>(args...); }

		return {
			vkBindBufferMemory(
				device,
				buffer,
				device_memory,
				offset
			)
		};
	}

	template<typename... Args>
	void bind_buffer_memory(Args&&... args) {
		vk::result result = vk::try_bind_buffer_memory(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk

void inline
handle<vk::device>::bind_memory(
	handle<vk::buffer> buffer, handle<vk::device_memory> memory
) const {
	vk::bind_buffer_memory(*this, buffer, memory);
}