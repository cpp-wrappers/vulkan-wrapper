#pragma once

#include "handle.hpp"
#include "clear.hpp"
#include "../../image/handle.hpp"
#include "../../image/layout.hpp"
#include "../../image/subresource_range.hpp"

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/meta/types/count_of_ranges_of_value_type.hpp>
#include <core/meta/elements/range_of_value_type.hpp>

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::image>,
		types::are_contain_one_decayed_same_as<vk::image_layout>,
		types::are_contain_one_decayed_same_as<vk::clear_color_value>,
		types::are_contain_one_range_of_value_type<vk::image_subresource_range>
	>::for_types<Args...>
	void cmd_clear_color_image(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>(args...);
		auto& image = elements::vk::possibly_guarded_handle_of<vk::image>(args...);
		vk::image_layout layout = elements::decayed_same_as<vk::image_layout>(args...);
		vk::clear_color_value clear_color = elements::decayed_same_as<vk::clear_color_value>(args...);
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

template<typename... Args>
auto& vk::handle<vk::command_buffer>::cmd_clear_color_image(Args&&... args) const {
	vk::cmd_clear_color_image(*this, forward<Args>(args)...); return *this;
}