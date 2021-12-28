#pragma once

#include <core/elements/one_of.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>

#include "handle.hpp"
#include "create_info.hpp"
#include "../device/handle.hpp"
#include "../shared/result.hpp"
#include "../shared/guarded_handle.hpp"

namespace vk {

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::vk::contain_one<vk::device>,
			types::count_of_type<vk::buffer_create_flags>::less_or_equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::buffer_size>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::buffer_usages>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::sharing_mode>::equals<1>::ignore_const::ignore_reference,
			types::count_of_ranges_of_value_type<vk::queue_family_index>::less_or_equals<1>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::handle<vk::buffer>>
	try_create_buffer(Args&&... args) {
		auto& device = elements::vk::of_type<vk::device>::for_elements_of(args...);

		vk::buffer_create_info ci {
			.size = elements::of_type<vk::buffer_size>::ignore_const::ignore_reference::for_elements_of(args...),
			.usage = elements::of_type<vk::buffer_usages>::ignore_const::ignore_reference::for_elements_of(args...),
			.sharing_mode = elements::of_type<vk::sharing_mode>::ignore_const::ignore_reference::for_elements_of(args...)
		};

		if constexpr (types::are_contain_type<vk::buffer_create_flags>::ignore_const::ignore_reference::for_types_of<Args...>) {
			ci.flags = elements::of_type<vk::buffer_create_flags>::ignore_const::ignore_reference::for_elements_of(args...);
		}

		if constexpr (types::are_contain_range_of_value_type<vk::queue_family_index>::for_types_of<Args...>) {
			auto& queue_fanily_indices = elements::range_of_value_type<vk::queue_family_index>::for_elements_of(args...);
			ci.queue_family_index_count = queue_fanily_indices.size();
			ci.queue_fanily_indices = queue_fanily_indices.data();
		}

		VkBuffer buffer;

		vk::result result {
			(int32) vkCreateBuffer(
				(VkDevice) vk::get_handle_value(device),
				(VkBufferCreateInfo*) &ci ,
				(VkAllocationCallbacks*) nullptr,
				(VkBuffer*) &buffer
			)
		};

		if(!result.success()) return result;

		return vk::handle<vk::buffer>{ buffer };
	}

	template<typename... Args>
	vk::handle<vk::buffer> create_buffer(Args&&... args) {
		auto result = vk::try_create_buffer(forward<Args>(args)...);
		if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
		return result.template get<vk::handle<vk::buffer>>();
	}
}