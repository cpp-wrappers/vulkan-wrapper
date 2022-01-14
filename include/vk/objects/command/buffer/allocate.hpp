#pragma once

#include <core/span.hpp>

#include "../../../object/create_or_allocate.hpp"
#include "../../device/handle.hpp"
#include "allocate_info.hpp"
#include "handle.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_pool>,
		types::count_of_type<vk::command_buffer_level>::equals<1>::ignore_const::ignore_reference,
		types::count_of_ranges_of_value_type<vk::handle<vk::command_buffer>>::equals<1>
	>::for_types_of<Args...>
	vk::result try_allocate_command_buffers(Args&&... args) {
		vk::command_buffer_allocate_info ai {};

		auto& command_buffers = elements::range_of_value_type<vk::handle<vk::command_buffer>>::for_elements_of(args...);

		ai.command_pool = vk::get_handle(elements::vk::possibly_guarded_handle_of<vk::command_pool>::for_elements_of(args...));
		ai.level = elements::of_type<vk::command_buffer_level>::ignore_const::ignore_reference::for_elements_of(args...);
		ai.count = (uint32) command_buffers.size();

		auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);

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
			types::count_of_type<vk::command_buffer_level>::equals<1>::ignore_const::ignore_reference
		>::for_types_of<Args...>
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