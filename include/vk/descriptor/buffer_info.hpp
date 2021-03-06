#pragma once

#include "../memory_offset.hpp"
#include "../memory_size.hpp"
#include "../buffer/handle.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/decayed_same_as.hpp>

namespace vk {

	struct descriptor_buffer_info {
		handle<vk::buffer> buffer;
		vk::memory_offset offset{};
		vk::memory_size size;

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<handle<vk::buffer>>,
			types::are_contain_one_decayed<vk::memory_size>,
			types::are_may_contain_one_decayed<vk::memory_offset>
		>::for_types<Args...>
		descriptor_buffer_info(Args&&... args) {
			buffer = elements::decayed<handle<vk::buffer>>(args...);

			size = elements::decayed<vk::memory_size>(args...);

			if constexpr (
				types::are_contain_decayed<
					vk::memory_offset
				>::for_types<Args...>
			) {
				offset = elements::decayed<vk::memory_offset>(args...);
			}
		}
	};

} // vk