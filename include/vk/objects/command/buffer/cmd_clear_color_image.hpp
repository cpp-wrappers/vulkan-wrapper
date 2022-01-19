#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/elements/range_of_value_type.hpp>

#include "../../image/handle.hpp"
#include "../../image/layout.hpp"
#include "../../image/subresource_range.hpp"
#include "clear.hpp"
#include "handle.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::image>,
		types::count_of_type<vk::image_layout>::equals<1>,
		types::count_of_type<vk::clear_color_value>::equals<1>,
		types::count_of_ranges_of_value_type<vk::image_subresource_range>::equals<1>
	>::for_types_of<decay<Args>...>
	void cmd_clear_color_image(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>(args...);
		auto& image = elements::vk::possibly_guarded_handle_of<vk::image>(args...);
		vk::image_layout layout = elements::of_type<vk::image_layout>(args...);
		vk::clear_color_value clear_color = elements::of_type<vk::clear_color_value>(args...);
		auto& ranges = elements::range_of_value_type<vk::image_subresource_range>(args...);

		vkCmdClearColorImage(
			(VkCommandBuffer) vk::get_handle_value(command_buffer),
			(VkImage) vk::get_handle_value(image),
			(VkImageLayout) layout,
			(VkClearColorValue*) &clear_color,
			(uint32) ranges.size(),
			(VkImageSubresourceRange*) ranges.data()
		);
	}

} // vk