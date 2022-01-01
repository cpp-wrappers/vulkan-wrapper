#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/elements/range_of_value_type.hpp>

#include "../../buffer/handle.hpp"
#include "../../image/handle.hpp"
#include "buffer_image_copy.hpp"
#include "handle.hpp"

namespace vk {

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::vk::contain_one<vk::command_buffer>,
			types::vk::contain_one<vk::buffer>,
			types::vk::contain_one<vk::image>,
			types::count_of_type<vk::image_layout>::equals<1>::ignore_const::ignore_reference,
			types::count_of_ranges_of_value_type<vk::buffer_image_copy>::equals<1>
		>::for_types_of<Args...>
	)
	void cmd_copy_buffer_to_image(Args&&... args) {
		auto& command_buffer = elements::vk::of_type<vk::command_buffer>::for_elements_of(args...);
		auto& buffer = elements::vk::of_type<vk::buffer>::for_elements_of(args...);
		auto& image = elements::vk::of_type<vk::image>::for_elements_of(args...);
		vk::image_layout dst_layout = elements::of_type<vk::image_layout>::ignore_const::ignore_reference::for_elements_of(args...);
		auto& regions = elements::range_of_value_type<vk::buffer_image_copy>::for_elements_of(args...);

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