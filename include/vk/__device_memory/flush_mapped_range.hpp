#pragma once

#include "flush_mapped_ranges.hpp"

#include "../../unexpected_handler.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::device>>,
		types::are_contain_one_decayed<handle<vk::device_memory>>,
		types::are_may_contain_one_decayed<vk::memory_offset>,
		types::are_contain_one_decayed<vk::memory_size>
	>::for_types<Args...>
	vk::result try_flush_mapped_memory_range(Args&&... args) {
		auto device = elements::decayed<handle<vk::device>>(args...);

		auto device_memory {
			elements::decayed<handle<vk::device_memory>>(args...)
		};

		vk::memory_offset offset{ 0 };
		
		if constexpr (
			types::are_contain_decayed<vk::memory_offset>::for_types<Args...>
		) { offset = elements::decayed<vk::memory_offset>(args...); }

		vk::memory_size size = elements::decayed<vk::memory_size>(args...);

		return vk::try_flush_mapped_memory_ranges(
			device,
			array{ vk::mapped_memory_range {
				.memory = device_memory,
				.offset = offset,
				.size = size
			} }
		);
	} // try_flush_mapped_memory_range

	template<typename... Args>
	void flush_mapped_memory_range(Args&&... args) {
		vk::result result = vk::try_flush_mapped_memory_range(
			forward<Args>(args)...
		);

		if(result.error()) vk::unexpected_handler(result);
	}

} // vk

template<typename... Args>
void
handle<vk::device>::flush_mapped_memory_range(Args&&... args) const {
	vk::flush_mapped_memory_range(*this, forward<Args>(args)...);
}