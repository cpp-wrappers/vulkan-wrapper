#pragma once

#include "size.hpp"

#include <core/wrapper/of_integer.hpp>
#include <core/flag_enum.hpp>

#include "vk/headers.hpp"

namespace vk {

	enum class descriptor_pool_create_flag {
		free_descriptor_set_bit = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
		update_after_bind_bit = VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT,
		//host_only_bit_valve = VK_DESCRIPTOR_POOL_CREATE_HOST_ONLY_BIT_VALVE,
		update_after_bind_bit_ext = VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT_EXT,
	};

	using descriptor_pool_create_flags = flag_enum<vk::descriptor_pool_create_flag>;

	struct max_sets : wrapper::of_integer<uint32, struct max_sets_t> {};

	struct descriptor_pool_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		const void* const next;
		vk::descriptor_pool_create_flags flags;
		vk::max_sets max_sets;
		uint32 pool_size_count;
		const vk::descriptor_pool_size* pool_sizes;
	};

} // vk

static_assert(sizeof(vk::descriptor_pool_create_info) == sizeof(VkDescriptorPoolCreateInfo));