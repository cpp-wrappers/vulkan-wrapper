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
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<vk::memory_size>.decayed == 1,
		is_same_as<vk::memory_type_index>.decayed == 1,
		is_same_as<vk::memory_allocate_flags_info>.decayed <= 1
	>
	vk::expected<handle<vk::device_memory>>
	try_allocate_memory(Args&&... args) {
		tuple a { args... };

		vk::memory_allocate_info ai {
			.size = a.template
				get<is_same_as<vk::memory_size>.decayed>(),
			.memory_type_index = a.template
				get<is_same_as<vk::memory_type_index>.decayed>()
		};

		if constexpr (
			(is_same_as<vk::memory_allocate_flags_info>.decayed > 0)
			.for_types<Args...>()
		) {
			ai.next = & a.template
				get<is_same_as<vk::memory_allocate_flags_info>.decayed>();
		}

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

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