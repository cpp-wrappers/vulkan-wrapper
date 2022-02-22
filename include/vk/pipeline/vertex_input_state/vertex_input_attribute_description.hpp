#pragma once

#include "vk/location.hpp"
#include "vk/binding.hpp"
#include "vk/offset.hpp"
#include "vk/format.hpp"

namespace vk {

	struct vertex_input_attribute_description {
		vk::location location;
		vk::binding binding;
		vk::format format;
		vk::offset<1> offset;
	};

} // vk

static_assert(sizeof(vk::vertex_input_attribute_description) == sizeof(VkVertexInputAttributeDescription));