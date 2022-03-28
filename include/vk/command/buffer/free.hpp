#pragma once

#include "handle.hpp"

#include "../../device/handle.hpp"
#include "../../destroy_or_free.hpp"
#include "../../function.hpp"

#include <core/range/of_value_type_same_as.hpp>

extern "C" VK_ATTR void VK_CALL vkFreeCommandBuffers(
	handle<vk::device> device,
	handle<vk::command_pool> command_pool,
	uint32 command_buffer_count,
	const handle<vk::command_buffer>* command_buffers
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_one_possibly_guarded_handle_of<vk::command_pool>,
		types::are_contain_range_of<handle<vk::command_buffer>>
	>::for_types<Args...>
	void free_command_buffers(Args&&... args) {
		auto& device = elements::possibly_guarded_handle_of<vk::device>(args...);
		auto& pool = elements::possibly_guarded_handle_of<vk::command_pool>(args...);
		auto& buffers = elements::range_of<handle<vk::command_buffer>>(args...);

		vkFreeCommandBuffers(
			vk::get_handle(device),
			vk::get_handle(pool),
			(uint32) buffers.size(),
			buffers.data()
		);
	}

	template<>
	struct vk::free_t<vk::command_buffer> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_contain_one_possibly_guarded_handle_of<vk::command_pool>,
			types::are_contain_one_decayed<handle<vk::command_buffer>>
		>::for_types<Args...>
		void operator() (Args&&... args) const {
			auto& device = elements::possibly_guarded_handle_of<vk::device>(args...);
			auto& pool = elements::possibly_guarded_handle_of<vk::command_pool>(args...);
			auto buffer = elements::decayed<handle<vk::command_buffer>>(args...);

			vk::free_command_buffers(device, pool, array{ buffer });
		}

	};

} // vk