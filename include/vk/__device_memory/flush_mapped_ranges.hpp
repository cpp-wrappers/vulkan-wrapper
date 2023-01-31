#pragma once

#include "./mapped_range.hpp"
#include "../__internal/function.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct flush_mammed_memory_ranges_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		uint32 memory_range_count,
		const vk::mapped_memory_range* memory_ranges
	)> {
		static constexpr auto name = "vkFlushMappedMemoryRanges";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_range_of_decayed<vk::mapped_memory_range> == 1
	>
	vk::result try_flush_mapped_memory_ranges(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		auto& ranges = a.template
			get_range_of_decayed<vk::mapped_memory_range>();

		return {
			vk::get_device_function<vk::flush_mammed_memory_ranges_function>(
				instance, device
			)(
				device.underlying(),
				(uint32) ranges.size(),
				ranges.iterator()
			)
		};
	}

	template<typename... Args>
	void flush_mapped_memory_ranges(Args&&... args) {
		vk::result result = vk::try_flush_mapped_memory_ranges(
			forward<Args>(args)...
		);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk