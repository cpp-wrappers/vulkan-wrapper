#pragma once

#include "mapped_range.hpp"

#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

#include "vk/device/handle.hpp"
#include "vk/headers.hpp"
#include "vk/result.hpp"

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
			(int32) vkFlushMappedMemoryRanges(
				(VkDevice) vk::get_handle_value(device),
				(uint32) ranges.size(),
				(VkMappedMemoryRange*) ranges.data()
			)
		};
	}

	template<typename... Args>
	void flush_mapped_device_memory_ranges(Args&&... args) {
		vk::result result = vk::try_flush_mapped_device_memory_ranges(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk