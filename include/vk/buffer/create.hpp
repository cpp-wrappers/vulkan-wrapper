#pragma once

#include "handle.hpp"
#include "create_info.hpp"
#include "../create_or_allocate.hpp"
#include "../device/handle.hpp"

#include <core/range/of_value_type.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

namespace vk {

	template<>
	struct vk::create_t<vk::buffer> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_may_contain_one_decayed_same_as<vk::buffer_create_flags>,
			types::are_contain_one_decayed_same_as<vk::buffer_size>,
			types::are_contain_one_decayed_same_as<vk::buffer_usages>,
			types::are_contain_one_decayed_same_as<vk::sharing_mode>,
			types::are_may_contain_one_range_of_value_type<vk::queue_family_index>
		>::for_types<Args...>
		vk::expected<vk::handle<vk::buffer>>
		operator () (Args&&... args) const {
			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);

			vk::buffer_create_info ci {
				.size = elements::decayed_same_as<vk::buffer_size>(args...),
				.usage = elements::decayed_same_as<vk::buffer_usages>(args...),
				.sharing_mode = elements::decayed_same_as<vk::sharing_mode>(args...)
			};

			if constexpr (types::are_contain_decayed_same_as<vk::buffer_create_flags>::for_types<Args...>) {
				ci.flags = elements::decayed_same_as<vk::buffer_create_flags>(args...);
			}

			if constexpr (types::are_contain_range_of_value_type<vk::queue_family_index>::for_types<Args...>) {
				auto& queue_fanily_indices = elements::range_of_value_type<vk::queue_family_index>(args...);
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

			if(result.error()) return result;

			return vk::handle<vk::buffer>{ buffer };
		}

	};

} // vk