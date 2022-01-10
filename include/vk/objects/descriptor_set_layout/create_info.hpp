#pragma once

#include <core/integer.hpp>
#include <core/flag_enum.hpp>

#include "../headers.hpp"
#include "binding.hpp"

namespace vk {

	
	enum class descriptor_set_layout_create_flag {
		update_after_bind_pool = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT,
		push_descriptor = VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR,
		host_only_pool = VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_VALVE
	};

	struct descriptor_set_layout_create_info {
		const uint32 type = (primitive::uint32) VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		const void* next{};
		flag_enum<descriptor_set_layout_create_flag> flags;
		uint32 binding_count;
		vk::descriptor_set_layout_binding* bindings;
	};
}

static_assert(sizeof(vk::descriptor_set_layout_create_info) == sizeof(VkDescriptorSetLayoutCreateInfo));