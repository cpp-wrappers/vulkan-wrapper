#pragma once

#include "mapped_range.hpp"

#include "../handle.hpp"
#include "../../result.hpp"
#include "../../function.hpp"

#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

extern "C" VK_ATTR int32 VK_CALL vkFlushMappedMemoryRanges(
	handle<vk::device> device,
	uint32 memory_range_count,
	const vk::mapped_memory_range* memory_ranges
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_range_of<vk::mapped_memory_range>
	>::for_types<Args...>
	vk::result try_flush_mapped_device_memory_ranges(Args&&... args) {
		auto& device = elements::possibly_guarded_handle_of<vk::device>(args...);
		auto& ranges = elements::range_of<vk::mapped_memory_range>(args...);

		return {
			vkFlushMappedMemoryRanges(
				vk::get_handle(device),
				(uint32) ranges.size(),
				ranges.data()
			)
		};
	}

	template<typename... Args>
	void flush_mapped_device_memory_ranges(Args&&... args) {
		vk::result result = vk::try_flush_mapped_device_memory_ranges(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk