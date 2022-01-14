#pragma once

#include "flush_mapped_ranges.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device_memory>,
		types::count_of_type<vk::memory_offset>::less_or_equals<1>::ignore_const::ignore_reference,
		types::count_of_type<vk::memory_size>::equals<1>::ignore_const::ignore_reference
	>::for_types_of<Args...>
	vk::result try_flush_mapped_device_memory_range(Args&&... args) {
		auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);
		auto& device_memory = elements::vk::possibly_guarded_handle_of<vk::device_memory>::for_elements_of(args...);

		vk::memory_offset offset{ 0 };
		
		if constexpr(types::are_contain_type<vk::memory_offset>::ignore_const::ignore_reference::for_types_of<Args...>) {
			offset = elements::of_type<vk::memory_offset>::ignore_const::ignore_reference::for_elements_of(args...);
		}

		vk::memory_size size = elements::of_type<vk::memory_size>::ignore_const::ignore_reference::for_elements_of(args...);

		return vk::try_flush_mapped_device_memory_ranges(
			device,
			array{ vk::mapped_memory_range {
				.memory = vk::get_handle(device_memory),
				.offset = offset,
				.size = size
			} }
		);
	}

	template<typename... Args>
	void flush_mapped_device_memory_range(Args&&... args) {
		vk::result result = vk::try_flush_mapped_device_memory_range(forward<Args>(args)...);
		if(result.error()) default_unexpected_handler(result);
	}

} // vk