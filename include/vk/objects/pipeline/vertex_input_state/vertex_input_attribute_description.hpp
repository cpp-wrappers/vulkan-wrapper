#pragma once

#include "../../../shared/location.hpp"
#include "../../../shared/binding.hpp"
#include "../../../shared/offset.hpp"
#include "../../image/format.hpp"

namespace vk {

	struct vertex_input_attribute_description {
		vk::location location;
		vk::binding binding;
		vk::format format;
		vk::offset<1> offset;
	};

} // vk

static_assert(sizeof(vk::vertex_input_attribute_description) == sizeof(VkVertexInputAttributeDescription));