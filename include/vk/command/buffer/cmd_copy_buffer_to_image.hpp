#pragma once

#include "handle.hpp"
#include "buffer_image_copy.hpp"

#include "../../buffer/handle.hpp"
#include "../../image/handle.hpp"
#include "../../image/layout.hpp"
#include "../../function.hpp"

#include <core/range_of_value_type_same_as.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

extern "C" VK_ATTR void VK_CALL vkCmdCopyBufferToImage(
	handle<vk::command_buffer>   command_buffer,
	handle<vk::buffer>           src_buffer,
	handle<vk::image>            dst_image,
	vk::image_layout             dst_image_layout,
	uint32                       region_count,
	const vk::buffer_image_copy* regions
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::command_buffer>>,
		types::are_contain_one_decayed<handle<vk::buffer>>,
		types::are_contain_one_decayed<handle<vk::image>>,
		types::are_contain_one_decayed<vk::image_layout>,
		types::are_contain_range_of<vk::buffer_image_copy>
	>::for_types<Args...>
	void cmd_copy_buffer_to_image(Args&&... args) {
		auto command_buffer = elements::decayed<
			handle<vk::command_buffer>
		>(args...);

		auto buffer = elements::decayed<handle<vk::buffer>>(args...);

		auto image = elements::decayed<handle<vk::image>>(args...);

		vk::image_layout dst_layout = elements::decayed<
			vk::image_layout
		>(args...);

		auto& regions = elements::range_of<vk::buffer_image_copy>(args...);

		vkCmdCopyBufferToImage(
			command_buffer,
			buffer,
			image,
			dst_layout,
			(uint32) regions.size(),
			regions.data()
		);
	} // cmd_copy_buffer_to_image

} // vk

template<typename... Args>
auto&
handle<vk::command_buffer>::cmd_copy_buffer_to_image(Args&&... args) const {
	vk::cmd_copy_buffer_to_image(*this, forward<Args>(args)...); return *this;
}