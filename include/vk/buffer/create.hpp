#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include "../create_or_allocate.hpp"
#include "../device/handle.hpp"
#include "../function.hpp"

#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

namespace vk {

	template<>
	struct vk::create_t<vk::buffer> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<vk::device>,
			types::are_may_contain_one_decayed<vk::buffer_create_flags>,
			types::are_contain_one_decayed<vk::buffer_size>,
			types::are_contain_one_decayed<vk::buffer_usages>,
			types::are_may_contain_one_decayed<vk::sharing_mode>,
			types::are_may_contain_range_of<vk::queue_family_index>
		>::for_types<Args...>
		vk::expected<handle<vk::buffer>>
		operator () (Args&&... args) const {
			auto device {
				elements::decayed<handle<vk::device>>(args...)
			};

			vk::buffer_create_info ci {
				.size = elements::decayed<vk::buffer_size>(args...),
				.usage = elements::decayed<vk::buffer_usages>(args...)
			};

			if constexpr (
				types::are_contain_decayed<
					vk::sharing_mode
				>::for_types<Args...>
			) {
				ci.sharing_mode = elements::decayed<vk::sharing_mode>(args...);
			}

			if constexpr (
				types::are_contain_decayed<
					vk::buffer_create_flags
				>::for_types<Args...>
			) {
				ci.flags = elements::decayed<vk::buffer_create_flags>(args...);
			}

			if constexpr (
				types::are_contain_range_of<
					vk::queue_family_index
				>::for_types<Args...>
			) {
				auto& queue_fanily_indices = elements::range_of<
					vk::queue_family_index
				>(args...);

				ci.queue_family_index_count = queue_fanily_indices.size();
				ci.queue_fanily_indices = queue_fanily_indices.data();
			}

			handle<vk::buffer> buffer;

			vk::result result {
				vkCreateBuffer(
					device,
					(vk::buffer_create_info*) &ci ,
					(void*) nullptr,
					(handle<vk::buffer>*) &buffer
				)
			};

			if(result.error()) return result;

			return handle<vk::buffer>{ buffer };

		} // operator ()

	}; // create_t<buffer>

} // vk