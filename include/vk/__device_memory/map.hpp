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
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::device_memory>> == 1,
		count_of_decayed_same_as<vk::memory_offset> <= 1,
		count_of_decayed_same_as<vk::memory_size> == 1,
		count_of_decayed_same_as<void**> == 1
	>
	vk::result try_map_memory(Args&&... args) {
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

		void** data = a.template get_decayed_same_as<void**>();

		return {
			vk::get_device_function<vk::map_memory_function>(
				instance, device
			)(
				device.underlying(),
				device_memory.underlying(),
				offset,
				size,
				0,
				data
			)
		};
	} // try_map_device_memory

	template<typename... Args>
	void map_memory(Args&&... args) {
		vk::result result = vk::try_map_memory(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk