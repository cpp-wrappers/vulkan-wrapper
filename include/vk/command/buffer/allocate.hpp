#pragma once

#include "handle.hpp"
#include "allocate_info.hpp"
#include "../../device/handle.hpp"
#include "../../create_or_allocate.hpp"

#include <core/span.hpp>

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_pool>,
		types::are_contain_one_decayed_same_as<vk::command_buffer_level>,
		types::are_contain_one_range_of_value_type<vk::handle<vk::command_buffer>>
	>::for_types<Args...>
	vk::result try_allocate_command_buffers(Args&&... args) {
		vk::command_buffer_allocate_info ai {};

		auto& command_buffers = elements::range_of_value_type<vk::handle<vk::command_buffer>>(args...);

		ai.command_pool = vk::get_handle(elements::vk::possibly_guarded_handle_of<vk::command_pool>(args...));
		ai.level = elements::decayed_same_as<vk::command_buffer_level>(args...);
		ai.count = (uint32) command_buffers.size();

		auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);

		return {
			(int32) vkAllocateCommandBuffers(
				(VkDevice) vk::get_handle_value(device),
				(VkCommandBufferAllocateInfo*) &ai,
				(VkCommandBuffer*) command_buffers.data()
			)
		};
	}

	template<typename... Args>
	void allocate_command_buffers(Args&&... args) {
		vk::result result = vk::try_allocate_command_buffers(forward<Args>(args)...);
		if(result.error()) default_unexpected_handler();
	}

	template<>
	struct vk::allocate_t<vk::command_buffer> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_pool>,
			types::are_contain_one_decayed_same_as<vk::command_buffer_level>
		>::for_types<Args...>
		vk::expected<vk::handle<vk::command_buffer>>
		operator () (Args&&... args) const {
			vk::handle<vk::command_buffer> command_buffer;

			vk::result result = vk::try_allocate_command_buffers(
				span{ &command_buffer, 1 },
				forward<Args>(args)...
			);

			if(result.error()) return result;

			return command_buffer;
		}

	};

} // vk