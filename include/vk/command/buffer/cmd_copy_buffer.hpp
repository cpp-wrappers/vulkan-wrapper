#pragma once

#include "handle.hpp"

#include <core/wrapper/of.hpp>
#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

#include "vk/memory_size.hpp"
#include "vk/memory_offset.hpp"
#include <core/handle/possibly_guarded_of.hpp>
#include "vk/buffer/handle.hpp"

namespace vk {

	struct src_offset : vk::memory_offset {};
	struct dst_offset : vk::memory_offset {};

	struct buffer_copy {
		src_offset src_offset;
		dst_offset dst_offset;
		vk::memory_size size;
	};

	struct src_buffer : handle<vk::buffer> {};
	struct dst_buffer : handle<vk::buffer> {};

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_contain_one_decayed<vk::src_buffer>,
		types::are_contain_one_decayed<vk::dst_buffer>,
		types::are_contain_one_range_of<vk::buffer_copy>
	>::for_types<Args...>
	void cmd_copy_buffer(Args&&... args) {

		auto& command_buffer = elements::possibly_guarded_handle_of<vk::command_buffer>(args...);
		vk::src_buffer src = elements::decayed<vk::src_buffer>(args...);
		vk::dst_buffer dst = elements::decayed<vk::dst_buffer>(args...);
		auto& regions = elements::range_of<vk::buffer_copy>(args...);

		vkCmdCopyBuffer(
			(VkCommandBuffer) vk::get_handle_value(command_buffer),
			(VkBuffer) src.value,
			(VkBuffer) dst.value,
			(uint32) regions.size(),
			(VkBufferCopy*) regions.data()
		);
	}

}

template<typename... Args>
auto& handle<vk::command_buffer>::cmd_copy_buffer(Args&&... args) const {
	vk::cmd_copy_buffer(*this, forward<Args>(args)...);
	return *this;
}