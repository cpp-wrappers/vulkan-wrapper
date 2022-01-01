#pragma once

#include <core/range/of_value_type.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>

#include "../handle.hpp"
#include "../../shared/headers.hpp"
#include "../../shared/result.hpp"
#include "mapped_range.hpp"

namespace vk {

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::vk::contain_one<vk::device>,
			types::count_of_ranges_of_value_type<vk::mapped_memory_range>::equals<1>
		>::for_types_of<Args...>
	)
	vk::result try_flush_mapped_device_memory_ranges(Args&&... args) {
		auto& device = elements::vk::of_type<vk::device>::for_elements_of(args...);
		auto& ranges = elements::range_of_value_type<vk::mapped_memory_range>::for_elements_of(args...);

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
		if(!result.success()) throw result;
	}
}