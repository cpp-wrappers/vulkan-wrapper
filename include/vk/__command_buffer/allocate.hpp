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
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::command_pool>>.decayed == 1,
		is_same_as<vk::command_buffer_level>.decayed == 1,
		is_range_of_element_type_satisfying_predicate<
			is_same_as<handle<vk::command_buffer>>.decayed
		> == 1
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

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::command_pool>>.decayed == 1,
		is_same_as<vk::command_buffer_level>.decayed == 1
	>
	handle<vk::command_buffer> allocate_command_buffer(Args&&... args) {
		handle<vk::command_buffer> command_buffer;
		vk::allocate_command_buffers(
			forward<Args>(args)..., span{ &command_buffer }
		);
		return command_buffer;
	}

} // vk