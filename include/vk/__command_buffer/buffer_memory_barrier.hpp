#pragma once

#include "../__internal/access.hpp"
#include "../__internal/queue_family_index.hpp"
#include "../__internal/memory_offset.hpp"
#include "../__internal/memory_size.hpp"
#include "../__buffer/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

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
		handle<vk::buffer>::underlying_type buffer;
		vk::memory_offset offset{ 0 };
		vk::memory_size size;

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			is_same_as<vk::src_access>.decayed == 1,
			is_same_as<vk::dst_access>.decayed == 1,
			is_same_as<vk::src_queue_family_index>.decayed <= 1,
			is_same_as<vk::dst_queue_family_index>.decayed <= 1,
			is_same_as<handle<vk::buffer>>.decayed == 1,
			is_same_as<vk::memory_offset>.decayed <= 1,
			is_same_as<vk::memory_size>.decayed == 1
		>
		buffer_memory_barrier(Args&&... args) {
			tuple a { args... };

			src_acccess = a.template get_decayed_same_as<vk::src_access>();
			dst_acccess = a.template get_decayed_same_as<vk::dst_access>();
			buffer = a.template get_decayed_same_as<handle<vk::buffer>>();
			size = a.template get_decayed_same_as<vk::memory_size>();

			if constexpr (
				(is_same_as<vk::src_queue_family_index>.decayed > 0)
				.for_types<Args...>()
			) {
				src_queue_family_index = a.template
					get_decayed_same_as<vk::src_queue_family_index>();
			}

			if constexpr (
				(is_same_as<vk::dst_queue_family_index>.decayed > 0)
				.for_types<Args...>()
			) {
				dst_queue_family_index = a.template
					get_decayed_same_as<vk::dst_queue_family_index>();
			}

			if constexpr (
				(is_same_as<vk::memory_offset>.decayed > 0)
				.for_types<Args...>()
			) {
				offset = a.template get_decayed_same_as<vk::memory_offset>();
			}

		} // constructor

	}; // buffer_memory_barrier

} // vk