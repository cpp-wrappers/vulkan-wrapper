#pragma once

#include "handle.hpp"
#include "clear.hpp"

#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/handle/possibly_guarded_of.hpp>

#include "vk/image/handle.hpp"
#include "vk/image/layout.hpp"
#include "vk/image/subresource_range.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_contain_one_possibly_guarded_handle_of<vk::image>,
		types::are_contain_one_decayed<vk::image_layout>,
		types::are_contain_one_decayed<vk::clear_color_value>,
		types::are_contain_range_of<vk::image_subresource_range>
	>::for_types<Args...>
	void cmd_clear_color_image(Args&&... args) {
		auto& command_buffer = elements::possibly_guarded_handle_of<vk::command_buffer>(args...);
		auto& image = elements::possibly_guarded_handle_of<vk::image>(args...);
		vk::image_layout layout = elements::decayed<vk::image_layout>(args...);
		vk::clear_color_value clear_color = elements::decayed<vk::clear_color_value>(args...);
		auto& ranges = elements::range_of<vk::image_subresource_range>(args...);

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
auto& handle<vk::command_buffer>::cmd_clear_color_image(Args&&... args) const {
	vk::cmd_clear_color_image(*this, forward<Args>(args)...); return *this;
}