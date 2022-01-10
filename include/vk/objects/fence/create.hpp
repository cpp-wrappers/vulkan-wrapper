#pragma once

#include <core/elements/one_of.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>

#include "../../object/create_or_allocate.hpp"
#include "../device/handle.hpp"
#include "handle.hpp"
#include "create_info.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::fence> {

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
				types::count_of_type<vk::fence_create_flags>::less_or_equals<1>::ignore_const::ignore_reference
			>::for_types_of<Args...>
		)
		vk::expected<vk::handle<vk::fence>>
		operator () (Args&&... args) const {
			vk::fence_create_info ci {};
	
			if constexpr(types::are_contain_type<vk::fence_create_flags>::ignore_const::ignore_reference::for_types_of<Args...>) {
				ci.flags = elements::of_type<vk::fence_create_flags>::ignore_const::ignore_reference::for_elements_of(args...);
			}
	
			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);
			VkFence fence;
	
			vk::result result {
				(int32) vkCreateFence(
					(VkDevice) vk::get_handle_value(device),
					(VkFenceCreateInfo*) &ci,
					(VkAllocationCallbacks*) nullptr,
					(VkFence*) &fence
				)
			};
	
			if(result.success()) return vk::handle<vk::fence>{ fence };
	
			return result;
		}

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
				types::count_of_type<vk::fence_create_flag>::greater_or_equals<0>::ignore_const::ignore_reference
			>::for_types_of<Args...>
		)
		vk::expected<vk::handle<vk::fence>>
		operator () (Args&&... args) const {
			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);

			vk::fence_create_flags create_flags;

			elements::for_each_of_type<vk::fence_create_flag>::ignore_const::ignore_reference::function {
				[&](vk::fence_create_flag flag){ create_flags.set(flag); }
			}.for_elements_of(args...);

			return this-> operator() (device, create_flags);
		}
	};

}