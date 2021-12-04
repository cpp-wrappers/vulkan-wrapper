#pragma once

#include <core/integer.hpp>

#include "../shared/headers.hpp"

namespace vk {

	enum class primitive_topology {
		point_list = VK_PRIMITIVE_TOPOLOGY_POINT_LIST,
		line_list = VK_PRIMITIVE_TOPOLOGY_LINE_LIST,
		line_strip = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP,
		triangle_list = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
		triangle_strip = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP,
		triangle_fan = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN,
		line_list_with_adjacency = VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY,
		line_strip_with_adjacency = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY,
		triangle_list_with_adjacency = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY,
		triangle_strip_with_adjacency = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY,
		patch_list  = VK_PRIMITIVE_TOPOLOGY_PATCH_LIST ,
	};

	struct pipeline_input_assembly_state_create_info {
		const uint32 type = (uint32) VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		const void* next;
		uint32 flags;
		vk::primitive_topology topology;
		uint32 enable_primitive_restart;
	};
}

static_assert(sizeof(vk::primitive_topology) == sizeof(VkPrimitiveTopology));