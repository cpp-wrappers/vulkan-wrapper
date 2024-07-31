#pragma once

#include "./handle.hpp"
#include "./clear_value.hpp"
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
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::command_buffer>>.decayed == 1,
		is_same_as<handle<vk::image>>.decayed == 1,
		is_same_as<vk::image_layout>.decayed == 1,
		is_same_as<vk::clear_color_value>.decayed == 1,
		is_range_of_element_type_satisfying_predicate<
			is_same_as<vk::image_subresource_range>.decayed
		> == 1
	>
	void cmd_clear_color_image(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::command_buffer> command_buffer = a.template
			get<is_same_as<handle<vk::command_buffer>>.decayed>();

		handle<vk::image> image = a.template
			get<is_same_as<handle<vk::image>>.decayed>();

		vk::image_layout layout = a.template
			get<is_same_as<vk::image_layout>.decayed>();

		vk::clear_color_value clear_color = a.template
			get<is_same_as<vk::clear_color_value>.decayed>();
	
		auto& ranges = a.template
			get<is_range_of<is_same_as<vk::image_subresource_range>.decayed>>();

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