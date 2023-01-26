#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/memory_offset.hpp"
#include "../__internal/memory_size.hpp"
#include "../__buffer/handle.hpp"
#include "../__device/handle.hpp"
#include "../__instance/handle.hpp"

namespace vk {

	struct src_offset : vk::memory_offset {};
	struct dst_offset : vk::memory_offset {};

	struct buffer_copy {
		src_offset src_offset;
		dst_offset dst_offset;
		vk::memory_size size;
	};

	struct src_buffer : handle<vk::buffer> {};
	struct dst_buffer : handle<vk::buffer> {};

} // vk

namespace vk {

	struct cmd_copy_buffer_function : vk::function<void(*)(
		handle<vk::command_buffer>::underlying_type command_buffer,
		vk::src_buffer::underlying_type src_buffer,
		vk::dst_buffer::underlying_type dst_buffer,
		uint32 region_count,
		const vk::buffer_copy* regions
	)> {
		static constexpr auto name = "vkCmdCopyBuffer";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::command_buffer>> == 1,
		count_of_decayed_same_as<vk::src_buffer> == 1,
		count_of_decayed_same_as<vk::dst_buffer> == 1,
		count_of_range_of_decayed<vk::buffer_copy> == 1
	>
	void cmd_copy_buffer(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();

		vk::src_buffer src = a.template
			get_decayed_same_as<vk::src_buffer>();

		vk::dst_buffer dst = a.template
			get_decayed_same_as<vk::dst_buffer>();

		auto& regions = a.template get_range_of_decayed<vk::buffer_copy>();

		vk::get_device_function<vk::cmd_copy_buffer_function>(
			instance, device
		)(
			command_buffer.underlying(),
			src.underlying(),
			dst.underlying(),
			(uint32) regions.size(),
			regions.iterator()
		);
	}

}