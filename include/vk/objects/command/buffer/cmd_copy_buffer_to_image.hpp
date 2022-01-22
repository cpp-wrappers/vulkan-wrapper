#pragma once

#include "handle.hpp"
#include "buffer_image_copy.hpp"
#include "../../buffer/handle.hpp"
#include "../../image/handle.hpp"
#include "../../image/layout.hpp"

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/meta/types/count_of_ranges_of_value_type.hpp>
#include <core/meta/elements/range_of_value_type.hpp>

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::buffer>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::image>,
		types::are_contain_one_decayed_same_as<vk::image_layout>,
		types::count_of_ranges_of_value_type<vk::buffer_image_copy>::equals<1>
	>::for_types<Args...>
	void cmd_copy_buffer_to_image(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>(args...);
		auto& buffer = elements::vk::possibly_guarded_handle_of<vk::buffer>(args...);
		auto& image = elements::vk::possibly_guarded_handle_of<vk::image>(args...);
		vk::image_layout dst_layout = elements::decayed_same_as<vk::image_layout>(args...);
		auto& regions = elements::range_of_value_type<vk::buffer_image_copy>(args...);

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
auto& vk::handle<vk::command_buffer>::cmd_copy_buffer_to_image(Args&&... args) const {
	vk::cmd_copy_buffer_to_image(*this, forward<Args>(args)...); return *this;
}