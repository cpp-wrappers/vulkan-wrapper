#pragma once

#include "./handle.hpp"
#include "./allocate_info.hpp"
#include "./allocate_flags_info.hpp"
#include "../__internal/function.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__internal/result.hpp"
#include "../__device/handle.hpp"

#include <tuple.hpp>

namespace vk {

	struct allocate_memory_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		const vk::memory_allocate_info* allocate_info,
		const void* allocator,
		handle<vk::device_memory>::underlying_type* memory
	)> {
		static constexpr auto name = "vkAllocateMemory";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<vk::memory_size> == 1,
		count_of_decayed_same_as<vk::memory_type_index> == 1,
		count_of_decayed_same_as<vk::memory_allocate_flags_info> <= 1
	>
	vk::expected<handle<vk::device_memory>>
	try_allocate_memory(Args&&... args) {
		tuple a { args... };

		vk::memory_allocate_info ai {
			.size = a.template get_decayed_same_as<vk::memory_size>(),
			.memory_type_index = a.template
				get_decayed_same_as<vk::memory_type_index>()
		};

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::memory_allocate_flags_info> > 0
		) {
			ai.next = & a.template
				get_decayed_same_as<vk::memory_allocate_flags_info>();
		}

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::device_memory> device_memory;

		vk::result result {
			vk::get_device_function<vk::allocate_memory_function>(
				instance, device
			)(
				device.underlying(),
				&ai,
				nullptr,
				&device_memory.underlying()
			)
		};

		if(result.error()) return result;

		return device_memory;
	}

	template<typename... Args>
	handle<vk::device_memory> allocate_memory(Args&&... args) {
		vk::expected<handle<vk::device_memory>> result
			= vk::try_allocate_memory(forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk