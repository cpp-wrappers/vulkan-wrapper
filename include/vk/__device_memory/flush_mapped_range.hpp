#pragma once

#include "./handle.hpp"
#include "./flush_mapped_ranges.hpp"

namespace vk {

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::device_memory>> == 1,
		count_of_decayed_same_as<vk::memory_offset> <= 1,
		count_of_decayed_same_as<vk::memory_size> == 1
	>
	vk::result try_flush_mapped_memory_range(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::device_memory> device_memory = a.template
			get_decayed_same_as<handle<vk::device_memory>>();

		vk::memory_offset offset{ 0 };
		
		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::memory_offset> > 0
		) {
			offset = a.template get_decayed_same_as<vk::memory_offset>();
		}

		vk::memory_size size = a.template
			get_decayed_same_as<vk::memory_size>();

		return vk::try_flush_mapped_memory_ranges(
			instance,
			device,
			array{ vk::mapped_memory_range {
				.memory = device_memory.underlying(),
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