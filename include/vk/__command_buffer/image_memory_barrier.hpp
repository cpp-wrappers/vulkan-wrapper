#pragma once

#include "../__image/layout.hpp"
#include "../__image/handle.hpp"
#include "../__image/subresource_range.hpp"
#include "../__internal/access.hpp"
#include "../__internal/queue_family_index.hpp"

#include <enum_flags.hpp>
#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct old_layout : enum_flags<vk::image_layout> {};
	struct new_layout : enum_flags<vk::image_layout> {};

	struct image_memory_barrier {
		uint32 structure_type = 45;
		const void* next = nullptr;
		vk::src_access src_access;
		vk::dst_access dst_access;
		vk::old_layout old_layout;
		vk::new_layout new_layout;
		vk::src_queue_family_index src_queue_family_index;
		vk::dst_queue_family_index dst_queue_family_index;
		handle<vk::image>::underlying_type image;
		vk::image_subresource_range subresource_range;

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			is_same_as<vk::src_access> <= 1,
			is_same_as<vk::dst_access> <= 1,
			is_same_as<vk::old_layout> <= 1,
			is_same_as<vk::new_layout> <= 1,
			is_same_as<vk::src_queue_family_index> <= 1,
			is_same_as<vk::dst_queue_family_index> <= 1,
			is_same_as<handle<vk::image>> == 1,
			is_same_as<vk::image_subresource_range> <= 1
		>
		image_memory_barrier(Args... args) :
			src_access {
				tuple<Args...>{args...}.template get_or<
					is_same_as<vk::src_access>
				>([]{ return vk::src_access{}; })
			},
			dst_access {
				tuple<Args...>{args...}.template get_or<
					is_same_as<vk::dst_access>
				>([]{ return vk::dst_access{}; })
			},
			old_layout {
				tuple<Args...>{args...}.template get_or<
					is_same_as<vk::old_layout>
				>([]{ return vk::old_layout{vk::image_layout::undefined}; })
			},
			new_layout {
				tuple<Args...>{args...}.template get_or<
					is_same_as<vk::new_layout>
				>([]{ return vk::new_layout{vk::image_layout::undefined}; })
			},
			src_queue_family_index {
				tuple<Args...>{args...}.template get_or<
					is_same_as<vk::src_queue_family_index>
				>([]{ return vk::src_queue_family_index{}; })
			},
			dst_queue_family_index {
				tuple<Args...>{args...}.template get_or<
					is_same_as<vk::dst_queue_family_index>
				>([]{ return vk::dst_queue_family_index{}; })
			},
			image {
				tuple<Args...>{args...}.template get<
					is_same_as<handle<vk::image>>
				>().underlying()
			},
			subresource_range {
				tuple<Args...>{args...}.template get_or<
					is_same_as<vk::image_subresource_range>
				>([]{ return vk::image_subresource_range{}; })
			}
		{

		}
	};

} // vk