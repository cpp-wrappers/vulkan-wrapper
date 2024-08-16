#pragma once

#include "./handle.hpp"
#include "./flush_mapped_ranges.hpp"

namespace vk {

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::device_memory>>.decayed == 1,
		is_same_as<vk::memory_offset>.decayed <= 1,
		is_same_as<vk::memory_size>.decayed == 1
	>
	vk::result try_flush_mapped_memory_range(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::device_memory> device_memory = a.template
			get<is_same_as<handle<vk::device_memory>>.decayed>();

		vk::memory_offset offset{ 0 };
		
		if constexpr (
			(is_same_as<vk::memory_offset>.decayed > 0).for_types<Args...>()
		) {
			offset = a.template
				get<is_same_as<vk::memory_offset>.decayed>();
		}

		vk::memory_size size = a.template
			get<is_same_as<vk::memory_size>.decayed>();

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
		if (result.error()) vk::unexpected_handler(result);
	}

} // vk