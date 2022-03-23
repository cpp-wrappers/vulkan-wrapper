#pragma once

#include "handle.hpp"
#include "buffer_image_copy.hpp"

#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

#include "vk/buffer/handle.hpp"
#include "vk/image/handle.hpp"
#include "vk/image/layout.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_contain_one_possibly_guarded_handle_of<vk::buffer>,
		types::are_contain_one_possibly_guarded_handle_of<vk::image>,
		types::are_contain_one_decayed<vk::image_layout>,
		types::are_contain_range_of<vk::buffer_image_copy>
	>::for_types<Args...>
	void cmd_copy_buffer_to_image(Args&&... args) {
		auto& command_buffer = elements::possibly_guarded_handle_of<vk::command_buffer>(args...);
		auto& buffer = elements::possibly_guarded_handle_of<vk::buffer>(args...);
		auto& image = elements::possibly_guarded_handle_of<vk::image>(args...);
		vk::image_layout dst_layout = elements::decayed<vk::image_layout>(args...);
		auto& regions = elements::range_of<vk::buffer_image_copy>(args...);

		vkCmdCopyBufferToImage(
			(VkCommandBuffer) vk::get_handle_value(command_buffer),
			(VkBuffer) vk::get_handle_value(buffer),
			(VkImage) vk::get_handle_value(image),
			(VkImageLayout) dst_layout,
			(uint32) regions.size(),
			(VkBufferImageCopy*) regions.data()
		);
	}

} // vk

template<typename... Args>
auto& handle<vk::command_buffer>::cmd_copy_buffer_to_image(Args&&... args) const {
	vk::cmd_copy_buffer_to_image(*this, forward<Args>(args)...); return *this;
}