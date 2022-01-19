#pragma once

#include <core/range/of_value_type.hpp>

#include "../../../shared/headers.hpp"
#include "../../../object/destroy_or_free.hpp"
#include "../../device/handle.hpp"
#include "handle.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_pool>,
		types::count_of_ranges_of_value_type<vk::handle<vk::command_buffer>>::equals<1>
	>::for_types_of<Args...>
	void free_command_buffers(Args&&... args) {
		auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);
		auto& pool = elements::vk::possibly_guarded_handle_of<vk::command_pool>(args...);
		auto& buffers = elements::range_of_value_type<vk::handle<vk::command_buffer>>(args...);

		vkFreeCommandBuffers(
			(VkDevice) vk::get_handle_value(device),
			(VkCommandPool) vk::get_handle_value(pool),
			(uint32) buffers.size(),
			(VkCommandBuffer*) buffers.data()
		);
	}

	template<>
	struct vk::free_t<vk::command_buffer> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_pool>,
			types::count_of_type<vk::handle<vk::command_buffer>>::equals<1>
		>::for_types_of<decay<Args>...>
		void operator() (Args&&... args) const {
			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);
			auto& pool = elements::vk::possibly_guarded_handle_of<vk::command_pool>(args...);
			auto buffer = elements::of_type<vk::handle<vk::command_buffer>>(args...);

			vk::free_command_buffers(device, pool, array{ buffer });
		}

	};

} // vk