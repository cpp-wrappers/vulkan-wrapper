#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/memory_offset.hpp"
#include "../__internal/memory_size.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"

#include <tuple.hpp>
#include <types.hpp>

namespace vk {

	struct map_memory_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::device_memory>::underlying_type memory,
		vk::memory_offset offset,
		vk::memory_size size,
		int32 flags,
		void** data
	)> {
		static constexpr auto name = "vkMapMemory";
	};


	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_convertible_to<handle<vk::instance>> == 1,
		is_convertible_to<handle<vk::device>> == 1,
		is_convertible_to<handle<vk::device_memory>> == 1,
		is_same_as<vk::memory_offset>.decayed <= 1,
		is_same_as<vk::memory_size>.decayed == 1,
		is_same_as<uint8*&> == 1
	>
	vk::result try_map_memory(Args&&... args) {
		tuple a { args... };

		auto instance = (handle<vk::instance>) a.template
			get<is_convertible_to<handle<vk::instance>>>();

		auto device = (handle<vk::device>) a.template
			get<is_convertible_to<handle<vk::device>>>();

		auto device_memory = (handle<vk::device_memory>) a.template
			get<is_convertible_to<handle<vk::device_memory>>>();

		vk::memory_offset offset{ 0 };

		if constexpr (
			(is_same_as<vk::memory_offset>.decayed > 0).for_types<Args...>()
		) {
			offset = a.template get<is_same_as<vk::memory_offset>.decayed>();
		}

		vk::memory_size size = a.template
			get<is_same_as<vk::memory_size>.decayed>();

		uint8*& data = a.template get<is_same_as<uint8*&>>();

		return {
			vk::get_device_function<vk::map_memory_function>(
				instance, device
			)(
				device.underlying(),
				device_memory.underlying(),
				offset,
				size,
				0,
				(void**) &data
			)
		};
	} // try_map_device_memory

	template<typename... Args>
	uint8* map_memory(Args&&... args) {
		uint8* mem_ptr;
		vk::result result = vk::try_map_memory(
			::forward<Args>(args)...,
			mem_ptr
		);
		if (result.error()) vk::unexpected_handler(result);
		return mem_ptr;
	}

} // vk