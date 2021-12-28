#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/at_index.hpp>
#include <core/elements/of_type.hpp>
#include <core/types/indices_of_type.hpp>
#include <core/elements/for_each_of_type.hpp>

#include "create_info.hpp"
#include "handle.hpp"
#include "../../shared/queue_family_index.hpp"
#include "../../shared/result.hpp"
#include "../../shared/guarded_handle.hpp"

namespace vk {

	struct device;

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::vk::contain_one<vk::device>,
			types::count_of_type<vk::command_pool_create_flag>::greater_or_equals<0>::ignore_const::ignore_reference,
			types::count_of_type<vk::queue_family_index>::equals<1>::ignore_const::ignore_reference
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::handle<vk::command_pool>>
	try_create_command_pool(Args&&... args) {
		vk::command_pool_create_info ci{};

		ci.queue_family_index = elements::of_type<vk::queue_family_index>::ignore_const::ignore_reference::for_elements_of(args...);

		elements::for_each_of_type<vk::command_pool_create_flag>::ignore_const::ignore_reference::function {
			[&](auto f){ ci.flags.set(f); }
		}.for_elements_of(args...);

		auto& device = elements::vk::of_type<vk::device>::for_elements_of(args...);

		VkCommandPool command_pool;

		vk::result result {
			(int32) vkCreateCommandPool(
				(VkDevice) vk::get_handle_value(device),
				(VkCommandPoolCreateInfo*) &ci,
				nullptr,
				&command_pool
			)
		};

		if(result.success()) return vk::handle<vk::command_pool>{ command_pool };

		return result;
	}

	template<typename... Args>
	vk::handle<vk::command_pool> create_command_pool(Args&&... args) {
		auto result = try_create_command_pool(forward<Args>(args)...);
		if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
		return result.template get<vk::handle<vk::command_pool>>();
	}
}