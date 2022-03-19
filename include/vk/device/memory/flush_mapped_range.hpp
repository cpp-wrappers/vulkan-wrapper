#pragma once

#include "flush_mapped_ranges.hpp"

#include "vk/default_unexpected_handler.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_one_possibly_guarded_handle_of<vk::device_memory>,
		types::are_may_contain_one_decayed<vk::memory_offset>,
		types::are_contain_one_decayed<vk::memory_size>
	>::for_types<Args...>
	vk::result try_flush_mapped_device_memory_range(Args&&... args) {
		auto& device = elements::possibly_guarded_handle_of<vk::device>(args...);
		auto& device_memory = elements::possibly_guarded_handle_of<vk::device_memory>(args...);

		vk::memory_offset offset{ 0 };
		
		if constexpr(types::are_contain_decayed<vk::memory_offset>::for_types<Args...>) {
			offset = elements::decayed<vk::memory_offset>(args...);
		}

		vk::memory_size size = elements::decayed<vk::memory_size>(args...);

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
		if(result.error()) vk::default_unexpected_handler(result);
	}

} // vk