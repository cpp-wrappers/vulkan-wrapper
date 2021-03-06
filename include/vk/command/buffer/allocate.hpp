#pragma once

#include "handle.hpp"
#include "allocate_info.hpp"

#include "../../device/handle.hpp"
#include "../../create_or_allocate.hpp"
#include "../../function.hpp"

#include <core/span.hpp>
#include <core/single.hpp>

extern "C" VK_ATTR int32 VK_CALL vkAllocateCommandBuffers(
	handle<vk::device>                      device,
	const vk::command_buffer_allocate_info* allocate_info,
	handle<vk::command_buffer>*             command_buffers
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::device>>,
		types::are_contain_one_decayed<handle<vk::command_pool>>,
		types::are_contain_one_decayed<vk::command_buffer_level>,
		types::are_contain_range_of<handle<vk::command_buffer>>
	>::for_types<Args...>
	vk::result try_allocate_command_buffers(Args&&... args) {
		vk::command_buffer_allocate_info ai {};

		auto& command_buffers {
			elements::range_of<handle<vk::command_buffer>>(args...)
		};

		ai.command_pool = elements::decayed<handle<vk::command_pool>>(args...);
		ai.level = elements::decayed<vk::command_buffer_level>(args...);
		ai.count = (uint32) command_buffers.size();

		auto device = elements::decayed<handle<vk::device>>(args...);

		return {
			vkAllocateCommandBuffers(
				device,
				&ai,
				command_buffers.data()
			)
		};
	} // try_allocate_command_buffers

	template<typename... Args>
	void allocate_command_buffers(Args&&... args) {
		vk::result result {
			vk::try_allocate_command_buffers(forward<Args>(args)...)
		};

		if(result.error()) vk::unexpected_handler(result);
	}

	template<>
	struct vk::allocate_t<vk::command_buffer> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<handle<vk::device>>,
			types::are_contain_one_decayed<handle<vk::command_pool>>,
			types::are_contain_one_decayed<vk::command_buffer_level>
		>::for_types<Args...>
		vk::expected<handle<vk::command_buffer>>
		operator () (Args&&... args) const {
			handle<vk::command_buffer> command_buffer;

			vk::result result = vk::try_allocate_command_buffers(
				single_view{ command_buffer },
				forward<Args>(args)...
			);

			if(result.error()) return result;

			return command_buffer;
		}

	};

} // vk