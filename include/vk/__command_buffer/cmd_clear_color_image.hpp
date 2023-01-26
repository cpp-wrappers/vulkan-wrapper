#pragma once

#include "./handle.hpp"
#include "./clear.hpp"
#include "../__internal/function.hpp"
#include "../__image/handle.hpp"
#include "../__image/layout.hpp"
#include "../__image/subresource_range.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"

namespace vk {

	struct cmd_clear_color_image_function : vk::function<void(*)(
		handle<vk::command_buffer>::underlying_type command_buffer,
		handle<vk::image>::underlying_type image,
		vk::image_layout image_layout,
		const vk::clear_color_value* color,
		uint32 range_count,
		const vk::image_subresource_range* ranges
	)> {
		static constexpr auto name = "vkCmdClearColorImage";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::command_buffer>> == 1,
		count_of_decayed_same_as<handle<vk::image>> == 1,
		count_of_decayed_same_as<vk::image_layout> == 1,
		count_of_decayed_same_as<vk::clear_color_value> == 1,
		count_of_range_of_decayed<vk::image_subresource_range> == 1
	>
	void cmd_clear_color_image(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();

		handle<vk::image> image = a.template
			get_decayed_same_as<handle<vk::image>>();

		vk::image_layout layout = a.template
			get_decayed_same_as<vk::image_layout>();

		vk::clear_color_value clear_color = a.template
			get_decayed_same_as<vk::clear_color_value>();
	
		auto& ranges = a.template
			get_range_of_decayed<vk::image_subresource_range>();

		vk::get_device_function<vk::cmd_clear_color_image_function>(
			instance, device
		)(
			command_buffer.underlying(),
			image.underlying(),
			layout,
			&clear_color,
			(uint32) ranges.size(),
			ranges.iterator()
		);
	} // cmd_clear_color_image

} // vk