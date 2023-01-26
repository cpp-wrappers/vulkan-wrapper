#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/memory_offset.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"
#include "../__device_memory/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct bind_buffer_memory_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::buffer>::underlying_type buffer,
		handle<vk::device_memory>::underlying_type memory,
		vk::memory_offset memory_offset
	)> {
		static constexpr auto name = "vkBindBufferMemory";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::buffer>> == 1,
		count_of_decayed_same_as<handle<vk::device_memory>> == 1,
		count_of_decayed_same_as<vk::memory_offset> <= 1
	>
	vk::result try_bind_buffer_memory(Args&&... args) {
		handle<vk::instance> instance = tuple{ args... }.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = tuple{ args... }.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::buffer> buffer = tuple{ args... }.template
			get_decayed_same_as<handle<vk::buffer>>();

		handle<vk::device_memory> device_memory = tuple{ args... }.template
			get_decayed_same_as<handle<vk::device_memory>>();

		vk::memory_offset offset{ 0 };
		
		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::memory_offset> > 0
		) {
			offset = tuple{ args... }.template
				get_decayed_same_as<vk::memory_offset>();
		}

		return {
			vk::get_device_function<vk::bind_buffer_memory_function>(
				instance, device
			)(
				device.underlying(),
				buffer.underlying(),
				device_memory.underlying(),
				offset
			)
		};
	}

	template<typename... Args>
	void bind_buffer_memory(Args&&... args) {
		vk::result result = vk::try_bind_buffer_memory(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk