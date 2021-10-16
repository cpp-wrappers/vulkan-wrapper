#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/at_index.hpp>
#include <core/elements/of_type.hpp>
#include <core/types/indices_of_type.hpp>
#include <core/elements/for_each_of_type.hpp>

#include "create_info.hpp"
#include "command_pool.hpp"
#include "../../queue_family_index.hpp"
#include "../../result.hpp"

namespace vk {

	struct device;

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::command_pool_create_flag>::remove_reference::less_or_equals<0u>,
			types::count_of_type<vk::queue_family_index>::remove_reference::equals<1u>,
			types::count_of_type<vk::device&>::equals<1u>
		>::for_types_of<Args...>
	)
	vk::command_pool& create_command_pool(Args&&... args) {
		vk::command_pool_create_info ci{};

		vk::command_pool* command_pool;
		vk::device& device = elements::of_type<vk::device&>::for_elements_of(args...);
		ci.queue_family_index = elements::of_type<vk::queue_family_index>::remove_reference::for_elements_of(args...);
		elements::for_each_of_type_remove_reference<vk::command_pool_create_flag>([&](auto f){ ci.flags.set(f); }, args...);

		vk::throw_if_error(
			vkCreateCommandPool(
				(VkDevice) &device,
				(VkCommandPoolCreateInfo*) &ci,
				nullptr,
				(VkCommandPool*) &command_pool
			)
		);

		return *command_pool;
	}
}