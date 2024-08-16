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
		is_convertible_to<handle<vk::instance>> == 1,
		is_convertible_to<handle<vk::device>> == 1,
		is_convertible_to<handle<vk::command_pool>> == 1,
		is_same_as<vk::command_buffer_level>.decayed == 1,
		is_range_of<is_same_as<handle<vk::command_buffer>>.decayed> == 1
	>
	vk::result try_allocate_command_buffers(Args&&... args) {
		tuple a { args... };

		auto instance = (handle<vk::instance>) a.template
			get<is_convertible_to<handle<vk::instance>>>();

		auto device = (handle<vk::device>) a.template
			get<is_convertible_to<handle<vk::device>>>();

		auto command_pool = (handle<vk::command_pool>) a.template
			get<is_convertible_to<handle<vk::command_pool>>>();

		vk::command_buffer_allocate_info ai {};

		ai.command_pool = command_pool.underlying();

		ai.level = a.template
			get<is_same_as<vk::command_buffer_level>.decayed>();

		auto& command_buffers = a.template
			get<is_range_of<
				is_same_as<handle<vk::command_buffer>>.decayed
			>>();
		ai.count = (uint32) command_buffers.size();

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

		if (result.error()) vk::unexpected_handler(result);
	}

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_convertible_to<handle<vk::instance>> == 1,
		is_convertible_to<handle<vk::device>> == 1,
		is_convertible_to<handle<vk::command_pool>> == 1,
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