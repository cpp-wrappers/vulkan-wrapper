#pragma once

#include "../../buffer/handle.hpp"
#include "../../queue_family_index.hpp"
#include "../../access.hpp"
#include "../../memory_offset.hpp"
#include "../../memory_size.hpp"

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

namespace vk {

	struct buffer_memory_barrier {
		uint32 structure_type = 44;
		const void* next = nullptr;
		vk::src_access src_acccess;
		vk::dst_access dst_acccess;
		vk::src_queue_family_index src_queue_family_index {
			vk::queue_family_ignored
		};
		vk::dst_queue_family_index dst_queue_family_index {
			vk::queue_family_ignored
		};
		handle<vk::buffer> buffer;
		vk::memory_offset offset{ 0 };
		vk::memory_size size;

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<vk::src_access>,
			types::are_contain_one_decayed<vk::dst_access>,
			types::are_may_contain_one_decayed<vk::src_queue_family_index>,
			types::are_may_contain_one_decayed<vk::dst_queue_family_index>,
			// TODO
			types::are_contain_one_decayed<handle<vk::buffer>>,
			types::are_may_contain_one_decayed<vk::memory_offset>,
			types::are_contain_one_decayed<vk::memory_size>
		>::for_types<Args...>
		buffer_memory_barrier(Args&&... args) :
			src_acccess{ elements::decayed<vk::src_access>(args...) },
			dst_acccess{ elements::decayed<vk::dst_access>(args...) },
			buffer { elements::decayed<handle<vk::buffer>>(args...) },
			size{ elements::decayed<vk::memory_size>(args...) }
		{
			if constexpr (
				types::are_contain_decayed<
					vk::src_queue_family_index
				>::for_types<Args...>
			) {
				src_queue_family_index = elements::decayed<
					vk::src_queue_family_index
				>(args...);
			}

			if constexpr (
				types::are_contain_decayed<
					vk::dst_queue_family_index
				>::for_types<Args...>
			) {
				dst_queue_family_index = {
					elements::decayed<vk::dst_queue_family_index>(args...)
				};
			}

			if constexpr (
				types::are_contain_decayed<
					vk::memory_offset
				>::for_types<Args...>) {
				offset = elements::decayed<vk::memory_offset>(args...);
			}

		} // constructor

	}; // buffer_memory_barrier

} // vk