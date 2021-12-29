#pragma once

#include "../../shared/queue_family_index.hpp"
#include "../../shared/create_or_allocate.hpp"
#include "create_info.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::try_create_t<vk::command_pool> {

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::vk::contain_one<vk::device>,
				types::count_of_type<vk::command_pool_create_flag>::greater_or_equals<0>::ignore_const::ignore_reference,
				types::count_of_type<vk::queue_family_index>::equals<1>::ignore_const::ignore_reference
			>::for_types_of<Args...>
		)
		elements::one_of<vk::result, vk::handle<vk::command_pool>>
		operator () (Args&&... args) const {
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
	};

} // vk