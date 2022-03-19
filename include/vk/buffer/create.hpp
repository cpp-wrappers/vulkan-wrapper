#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

#include "vk/create_or_allocate.hpp"
#include "vk/device/handle.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::buffer> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_may_contain_one_decayed<vk::buffer_create_flags>,
			types::are_contain_one_decayed<vk::buffer_size>,
			types::are_contain_one_decayed<vk::buffer_usages>,
			types::are_may_contain_one_decayed<vk::sharing_mode>,
			types::are_may_contain_one_range_of<vk::queue_family_index>
		>::for_types<Args...>
		vk::expected<handle<vk::buffer>>
		operator () (Args&&... args) const {
			auto& device = elements::possibly_guarded_handle_of<vk::device>(args...);

			vk::buffer_create_info ci {
				.size = elements::decayed<vk::buffer_size>(args...),
				.usage = elements::decayed<vk::buffer_usages>(args...)
			};

			if constexpr (types::are_contain_decayed<vk::sharing_mode>::for_types<Args...>) {
				ci.sharing_mode = elements::decayed<vk::sharing_mode>(args...);
			}

			if constexpr (types::are_contain_decayed<vk::buffer_create_flags>::for_types<Args...>) {
				ci.flags = elements::decayed<vk::buffer_create_flags>(args...);
			}

			if constexpr (types::are_contain_range_of<vk::queue_family_index>::for_types<Args...>) {
				auto& queue_fanily_indices = elements::range_of<vk::queue_family_index>(args...);
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

			return handle<vk::buffer>{ buffer };
		}

	};

} // vk