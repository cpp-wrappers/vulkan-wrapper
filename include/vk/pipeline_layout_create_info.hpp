#pragma once

#include "cxx_util/bitmask_from_enum.hpp"
#include "descriptor_set_layout.hpp"
#include "headers.hpp"
#include <cxx_util/int_with_size.hpp>
#include <cxx_util/named.hpp>
#include "push_constant_range.hpp"

namespace vk {

struct descriptor_set_layout_count : u::named<uint32_t> {};
struct push_constant_range_count : u::named<uint32_t> {};

struct pipeline_layout_create_info {
	u::uint_with_size_of<VkStructureType> m_type = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	const void* m_next = nullptr;
	uint32_t m_flags = 0;
	descriptor_set_layout_count m_descriptor_set_layout_count{0};
	const vk::descriptor_set_layout* m_descriptor_set_layouts = nullptr;
	push_constant_range_count m_push_constant_range_count{0};
	const vk::push_constant_range* m_push_constant_ranges = nullptr;
};

} // vk

static_assert(sizeof(vk::pipeline_layout_create_info) == sizeof(VkPipelineLayoutCreateInfo));