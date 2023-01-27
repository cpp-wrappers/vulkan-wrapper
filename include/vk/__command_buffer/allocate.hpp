#pragma once

#include "./handle.hpp"
#include "./allocate_info.hpp"
#include "../__internal/function.hpp"
#include "../__internal/result.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"

namespace vk {

	struct allocate_command_buffers_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		const vk::command_buffer_allocate_info* allocate_info,
		handle<vk::command_buffer>::underlying_type* command_buffers
	)> {
		static constexpr auto name = "vkAllocateCommandBuffers";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::command_pool>> == 1,
		count_of_decayed_same_as<vk::command_buffer_level> == 1,
		count_of_range_of_decayed<handle<vk::command_buffer>> == 1
	>
	vk::result try_allocate_command_buffers(Args&&... args) {
		vk::command_buffer_allocate_info ai {};

		auto& command_buffers = tuple{ args... }.template
			get_range_of_decayed<handle<vk::command_buffer>>();

		ai.command_pool = tuple{ args... }.template
			get_decayed_same_as<handle<vk::command_pool>>().underlying();

		ai.level = tuple{ args... }.template
			get_decayed_same_as<vk::command_buffer_level>();

		ai.count = (uint32) command_buffers.size();

		handle<vk::instance> instance = tuple{ args... }.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = tuple{ args... }.template
			get_decayed_same_as<handle<vk::device>>();

		return {
			vk::get_device_function<vk::allocate_command_buffers_function>(
				instance, device
			)(
				device.underlying(),
				&ai,
				(handle<vk::command_buffer>::underlying_type*)
					command_buffers.iterator()
			)
		};
	} // try_allocate_command_buffers

	template<typename... Args>
	void allocate_command_buffers(Args&&... args) {
		vk::result result {
			vk::try_allocate_command_buffers(forward<Args>(args)...)
		};

		if(result.error()) vk::unexpected_handler(result);
	}

} // vk