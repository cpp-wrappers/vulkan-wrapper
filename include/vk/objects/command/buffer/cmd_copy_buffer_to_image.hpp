#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/types/are_contain_one_type.hpp>
#include <core/elements/range_of_value_type.hpp>

#include "../../buffer/handle.hpp"
#include "../../image/handle.hpp"
#include "buffer_image_copy.hpp"
#include "handle.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::buffer>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::image>,
		types::are_contain_one_type<vk::image_layout>::decay,
		types::count_of_ranges_of_value_type<vk::buffer_image_copy>::equals<1>
	>::for_types_of<Args...>
	void cmd_copy_buffer_to_image(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>::for_elements_of(args...);
		auto& buffer = elements::vk::possibly_guarded_handle_of<vk::buffer>::for_elements_of(args...);
		auto& image = elements::vk::possibly_guarded_handle_of<vk::image>::for_elements_of(args...);
		vk::image_layout dst_layout = elements::of_type<vk::image_layout>::decay::for_elements_of(args...);
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