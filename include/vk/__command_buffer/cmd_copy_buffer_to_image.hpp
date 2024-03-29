#pragma once

#include "./handle.hpp"
#include "./buffer_image_copy.hpp"
#include "../__internal/function.hpp"
#include "../__buffer/handle.hpp"
#include "../__image/handle.hpp"
#include "../__image/layout.hpp"
#include "../__device/handle.hpp"
#include "../__instance/handle.hpp"

namespace vk {

	struct cmd_copy_buffer_to_image_function : vk::function<void(*)(
		handle<vk::command_buffer>::underlying_type command_buffer,
		handle<vk::buffer>::underlying_type src_buffer,
		handle<vk::image>::underlying_type dst_image,
		vk::image_layout dst_image_layout,
		uint32 region_count,
		const vk::buffer_image_copy* regions
	)> {
		static constexpr auto name = "vkCmdCopyBufferToImage";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::command_buffer>> == 1,
		count_of_decayed_same_as<handle<vk::buffer>> == 1,
		count_of_decayed_same_as<handle<vk::image>> == 1,
		count_of_decayed_same_as<vk::image_layout> == 1,
		count_of_range_of_decayed<vk::buffer_image_copy> == 1
	>
	void cmd_copy_buffer_to_image(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();

		handle<vk::buffer> buffer = a.template
			get_decayed_same_as<handle<vk::buffer>>();

		handle<vk::image> image = a.template
			get_decayed_same_as<handle<vk::image>>();

		vk::image_layout dst_layout = a.template
			get_decayed_same_as<vk::image_layout>();

		auto& regions = a.template
			get_range_of_decayed<vk::buffer_image_copy>();

		vk::get_device_function<vk::cmd_copy_buffer_to_image_function>(
			instance, device
		)(
			command_buffer.underlying(),
			buffer.underlying(),
			image.underlying(),
			dst_layout,
			(uint32) regions.size(),
			regions.iterator()
		);
	} // cmd_copy_buffer_to_image

} // vk