#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>

#include "../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../elements/possibly_guarded_handle_of.hpp"
#include "../device/handle.hpp"
#include "handle.hpp"

namespace vk {

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::count_of_ranges_of_value_type<vk::handle<vk::fence>>::equals<1>,
			types::count_of_type<vk::wait_all>::less_or_equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::timeout>::less_or_equals<1>::ignore_const::ignore_reference
		>::for_types_of<Args...>
	)
	vk::result try_wait_for_fences(Args&&... args) {
		auto& fences = elements::range_of_value_type<vk::handle<vk::fence>>::for_elements_of(args...);

		bool wait_all = true;

		if constexpr(types::are_contain_type<vk::wait_all>::ignore_const::ignore_reference::for_types_of<Args...>) {
			wait_all = (bool) elements::of_type<vk::wait_all>::ignore_const::ignore_reference::for_elements_of(args...);
		}

		vk::timeout timeout{ UINT64_MAX };

		if constexpr(types::are_contain_type<vk::timeout>::ignore_const::ignore_reference::for_types_of<Args...>) {
			timeout = elements::of_type<vk::timeout>::ignore_const::ignore_reference::for_elements_of(args...);
		}

		auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);

		return {
			(int32) vkWaitForFences(
				(VkDevice) vk::get_handle_value(device),
				(uint32) fences.size(),
				(VkFence*) fences.data(),
				uint32{ wait_all },
				(uint64) timeout
			)
		};
	}

	template<typename... Args>
	void wait_for_fences(Args&&... args) {
		vk::result result = vk::try_wait_for_fences(forward<Args>(args)...);
		if(!result.success()) throw result;
	}
}