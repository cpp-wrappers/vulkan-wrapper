#pragma once

#include <core/elements/one_of.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>

#include "handle.hpp"
#include "create_info.hpp"
#include "../shared/headers.hpp"
#include "../shared/result.hpp"
#include "../shared/guarded_handle.hpp"
#include "../device/handle.hpp"

namespace vk {

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::vk::contain_one<vk::device>,
			types::count_of_type<vk::fence_create_flags>::less_or_equals<1>::ignore_const::ignore_reference
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::handle<vk::fence>>
	try_create_fence(Args&&... args) {
		vk::fence_create_info ci {};

		if constexpr(types::are_contain_type<vk::fence_create_flags>::ignore_const::ignore_reference::for_types_of<Args...>) {
			ci.flags = elements::of_type<vk::fence_create_flags>::ignore_const::ignore_reference::for_elements_of(args...);
		}

		auto& device = elements::vk::of_type<vk::device>::for_elements_of(args...);
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
	vk::handle<vk::fence> create_fence(Args&&... args) {
		auto result = vk::try_create_fence(forward<Args>(args)...);
		if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
		return result.template get<vk::handle<vk::fence>>();
	}

}