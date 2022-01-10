#pragma once

#include <core/integer.hpp>
#include <core/flag_enum.hpp>

#include "../../../shared/headers.hpp"
#include "binding.hpp"

namespace vk {

	enum class descriptor_set_layout_create_flag {
		update_after_bind_pool = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT,
		push_descriptor = VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR,
		host_only_pool = VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_VALVE
	};

	using descriptor_set_layout_create_flags = flag_enum<vk::descriptor_set_layout_create_flag>;

	struct descriptor_set_layout_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		const void * const next;
		vk::descriptor_set_layout_create_flags flags;
		uint32 binding_count;
		vk::descriptor_set_layout_binding* bindings;
	};
}

static_assert(sizeof(vk::descriptor_set_layout_create_info) == sizeof(VkDescriptorSetLayoutCreateInfo));