#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/at_index.hpp>
#include <core/elements/of_type.hpp>
#include <core/types/indices_of_type.hpp>
#include <core/elements/for_each_of_type.hpp>

#include "create_info.hpp"
#include "command_pool.hpp"
#include "../../shared/queue_family_index.hpp"
#include "../../shared/result.hpp"

namespace vk {

	struct device;

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::command_pool_create_flag>::less_or_equals<0u>,
			types::count_of_type<vk::queue_family_index>::equals<1u>,
			types::count_of_type<vk::device>::equals<1u>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::command_pool> try_create_command_pool(const Args&... args) {
		vk::command_pool_create_info ci{};

		const vk::device& device = elements::of_type<const vk::device&>::for_elements_of(args...);
		ci.queue_family_index = elements::of_type<vk::queue_family_index>::remove_reference::for_elements_of(args...);
		elements::for_each_of_type<const vk::command_pool_create_flag&>([&](auto f){ ci.flags.set(f); }, args...);

		VkCommandPool command_pool;

		vk::result result {
			vkCreateCommandPool(
				*(VkDevice*) &device,
				(VkCommandPoolCreateInfo*) &ci,
				nullptr,
				&command_pool
			)
		};

		if(result.success()) return (uint64) command_pool;

		return result;
	}
}