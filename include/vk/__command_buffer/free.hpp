#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__device/handle.hpp"
#include "../__command_pool/handle.hpp"

#include <handle.hpp>
#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct free_command_buffers_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::command_pool>::underlying_type command_pool,
		uint32 command_buffer_count,
		const handle<vk::command_buffer>::underlying_type* command_buffers
	)> {
		static constexpr auto name = "vkFreeCommandBuffers";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_convertible_to<handle<vk::instance>> == 1,
		is_convertible_to<handle<vk::device>> == 1,
		is_convertible_to<handle<vk::command_pool>> == 1,
		is_range_of<is_same_as<handle<vk::command_buffer>>.decayed> == 1
	>
	void free_command_buffers(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = (handle<vk::instance>) a.template
			get<is_convertible_to<handle<vk::instance>>>();

		handle<vk::device> device = (handle<vk::device>) a.template
			get<is_convertible_to<handle<vk::device>>>();

		handle<vk::command_pool> pool = (handle<vk::command_pool>) a.template
			get<is_convertible_to<handle<vk::command_pool>>>();

		auto& buffers = a.template
			get<is_range_of<is_same_as<handle<vk::command_buffer>>.decayed>>();

		vk::get_device_function<vk::free_command_buffers_function>(
			instance, device
		)(
			device.underlying(),
			pool.underlying(),
			(uint32) buffers.size(),
			(handle<vk::command_buffer>::underlying_type*) buffers.iterator()
		);
	} // free_command_buffers

} // vk