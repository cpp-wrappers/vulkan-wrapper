#pragma once

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

#include "vk/buffer/handle.hpp"
#include "vk/queue_family_index.hpp"
#include "vk/access.hpp"
#include "vk/memory_offset.hpp"
#include "vk/memory_size.hpp"
#include "vk/handle/get.hpp"
#include "vk/handle/possibly_guarded_handle_of.hpp"

namespace vk {

	struct buffer_memory_barrier {
		uint32 type = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
		const void * const next = nullptr;
		vk::src_access src_acccess;
		vk::dst_access dst_acccess;
		vk::src_queue_family_index src_queue_family_index{ VK_QUEUE_FAMILY_IGNORED };
		vk::dst_queue_family_index dst_queue_family_index{ VK_QUEUE_FAMILY_IGNORED };
		vk::handle<vk::buffer> buffer;
		vk::memory_offset offset{ 0 };
		vk::memory_size size;

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::are_contain_one_decayed<vk::src_access>,
			types::are_contain_one_decayed<vk::dst_access>,
			types::are_may_contain_one_decayed<vk::src_queue_family_index>,
			types::are_may_contain_one_decayed<vk::dst_queue_family_index>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::buffer>, // TODO
			types::are_may_contain_one_decayed<vk::memory_offset>,
			types::are_contain_one_decayed<vk::memory_size>
		>::for_types<Args...>
		buffer_memory_barrier(Args&&... args)
		:
			src_acccess{ elements::decayed<vk::src_access>(args...) },
			dst_acccess{ elements::decayed<vk::dst_access>(args...) },
			buffer{ vk::get_handle(elements::vk::possibly_guarded_handle_of<vk::buffer>(args...)) },
			size{ elements::decayed<vk::memory_size>(args...) }
		{
			if constexpr (types::are_contain_decayed<vk::src_queue_family_index>::for_types<Args...>) {
				src_queue_family_index = elements::decayed<vk::src_queue_family_index>(args...);
			}

			if constexpr (types::are_contain_decayed<vk::dst_queue_family_index>::for_types<Args...>) {
				dst_queue_family_index = elements::decayed<vk::dst_queue_family_index>(args...);
			}

			if constexpr (types::are_contain_decayed<vk::memory_offset>::for_types<Args...>) {
				offset = elements::decayed<vk::memory_offset>(args...);
			}
		}
	};

} // vk

static_assert(sizeof(vk::buffer_memory_barrier) == sizeof(VkBufferMemoryBarrier));