#pragma once

#include <core/integer.hpp>

#include "../../../shared/headers.hpp"
#include "vertex_input_binding_description.hpp"
#include "vertex_input_attribute_description.hpp"

namespace vk {

	struct pipeline_vertex_input_state_create_info {
		const uint32 type = (uint32) VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		const void* next;
		uint32 flags;

		uint32 vertex_binding_description_count;
		const vertex_input_binding_description* vertex_binding_descriptions;

		uint32 vertex_attribute_description_count;
		const vertex_input_attribute_description* vertex_attribute_descriptions;
	};

}

static_assert(sizeof(vk::pipeline_vertex_input_state_create_info) == sizeof(VkPipelineVertexInputStateCreateInfo));