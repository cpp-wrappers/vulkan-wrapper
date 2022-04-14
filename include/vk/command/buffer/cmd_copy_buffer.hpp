#pragma once

#include "handle.hpp"

#include "../../memory_size.hpp"
#include "../../memory_offset.hpp"
#include "../../buffer/handle.hpp"
#include "../../function.hpp"

#include <core/wrapper/of.hpp>
#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

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

} // vk

VK_ATTR void VK_CALL vkCmdCopyBuffer(
	handle<vk::command_buffer> command_buffer,
	vk::src_buffer src_buffer,
	vk::dst_buffer dst_buffer,
	uint32 region_count,
	const vk::buffer_copy* regions
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::command_buffer>>,
		types::are_contain_one_decayed<vk::src_buffer>,
		types::are_contain_one_decayed<vk::dst_buffer>,
		types::are_contain_range_of<vk::buffer_copy>
	>::for_types<Args...>
	void cmd_copy_buffer(Args&&... args) {

		auto command_buffer = elements::decayed<handle<vk::command_buffer>>(args...);
		vk::src_buffer src = elements::decayed<vk::src_buffer>(args...);
		vk::dst_buffer dst = elements::decayed<vk::dst_buffer>(args...);
		auto& regions = elements::range_of<vk::buffer_copy>(args...);

		vkCmdCopyBuffer(
			command_buffer,
			src,
			dst,
			(uint32) regions.size(),
			regions.data()
		);
	}

}

template<typename... Args>
auto& handle<vk::command_buffer>::cmd_copy_buffer(Args&&... args) const {
	vk::cmd_copy_buffer(*this, forward<Args>(args)...);
	return *this;
}