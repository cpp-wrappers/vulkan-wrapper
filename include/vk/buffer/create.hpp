#pragma once

#include <core/elements/one_of.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>

#include "handle.hpp"
#include "create_info.hpp"
#include "../device/handle.hpp"
#include "../shared/result.hpp"
#include "../shared/guarded.hpp"

namespace vk {

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::vk::contain_one<vk::device>,
			types::count_of_type<vk::buffer_create_flags>::equals<1>::ignore_reference,
			types::count_of_type<vk::buffer_size>::equals<1>::ignore_reference,
			types::count_of_type<vk::buffer_usages>::equals<1>::ignore_reference,
			types::count_of_type<vk::sharing_mode>::equals<1>::ignore_reference,
			types::count_of_ranges_of_value_type<vk::queue_family_index>::equals<1>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::buffer>
	try_create_buffer(Args&&... args) {
		auto& device = elements::vk::of_type<vk::device>::for_elements_of(args...);

		auto& queue_fanily_indices = elements::range_of_value_type<vk::queue_family_index>::for_elements_of(args...);

		vk::buffer_create_info ci {
			.flags = elements::of_type<vk::buffer_create_flags>::ignore_reference::for_elements_of(args...),
			.size = elements::of_type<vk::buffer_size>::ignore_reference::for_elements_of(args...),
			.usage = elements::of_type<vk::buffer_usages>::ignore_reference::for_elements_of(args...),
			.sharing_mode = elements::of_type<vk::sharing_mode>::ignore_reference::for_elements_of(args...),
			.queue_family_index_count = queue_fanily_indices.size(),
			.queue_fanily_indices = queue_fanily_indices.data()
		};

		VkBuffer buffer;

		vk::result result {
			(int32) vkCreateBuffer(
				(VkDevice) vk::get_raw_handle<vk::device>(device),
				(VkBufferCreateInfo*) &ci ,
				(VkAllocationCallbacks*) nullptr,
				(VkBuffer*) &buffer
			)
		};

		if(!result.success()) return result;

		return vk::buffer{ buffer };
	}

	template<typename... Args>
	vk::buffer create_buffer(Args&&... args) {
		auto result = vk::try_create_buffer(forward<Args>(args)...);
		if(result.template get_current<vk::result>()) throw result.template get<vk::result>();
		return result.template get<vk::buffer>();
	}
}