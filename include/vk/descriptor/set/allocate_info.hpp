#pragma once

#include "layout/handle.hpp"

#include "vk/headers.hpp"
#include "vk/count.hpp"
#include "vk/descriptor/pool/handle.hpp"

namespace vk {

	struct descriptor_set_allocate_info {
		const uint32 type = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		const void* const next;
		vk::handle<vk::descriptor_pool> descriptor_pool;
		vk::count descriptor_set_count;
		const vk::handle<vk::descriptor_set_layout>* descriptor_set_layouts;
	};

} // vk

static_assert(sizeof(vk::descriptor_set_allocate_info) == sizeof(VkDescriptorSetAllocateInfo));
static_assert(
	__builtin_offsetof(vk::descriptor_set_allocate_info, descriptor_set_count) == 
	__builtin_offsetof(VkDescriptorSetAllocateInfo, descriptorSetCount)
);