#pragma once

#include <core/integer.hpp>
#include <core/named.hpp>
#include "headers.hpp"
#include "vertex_input_binding_description.hpp"

namespace vk {

struct vertex_binding_description_count : named<uint32_t> {};
struct vertex_binding_descriptions : named<const vk::vertex_input_binding_description*> {};
struct vertex_attribute_description : named<uint32_t> {};

struct pipeline_vertex_input_state_create_info {
	uint_with_size_of<VkStructureType> type
		= VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	
	const void* next = nullptr;
	uint32_t flags = 0;


};

}