#pragma once

#include <integer.hpp>

namespace vk {

	enum class primitive_topology {
		point_list                    = 0,
		line_list                     = 1,
		line_strip                    = 2,
		triangle_list                 = 3,
		triangle_strip                = 4,
		triangle_fan                  = 5,
		line_list_with_adjacency      = 6,
		line_strip_with_adjacency     = 7,
		triangle_list_with_adjacency  = 8,
		triangle_strip_with_adjacency = 9,
		patch_list                    = 10
	};

	struct pipeline_input_assembly_state_create_info {
		uint32                 structure_type = 20;
		const void*            next;
		uint32                 flags;
		vk::primitive_topology topology;
		uint32                 enable_primitive_restart;
	};

} // vk