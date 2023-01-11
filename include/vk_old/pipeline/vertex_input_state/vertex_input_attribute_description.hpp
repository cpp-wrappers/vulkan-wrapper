#pragma once

#include "../../location.hpp"
#include "../../binding.hpp"
#include "../../offset.hpp"
#include "../../format.hpp"

namespace vk {

	struct vertex_input_attribute_description {
		vk::location location;
		vk::binding binding;
		vk::format format;
		vk::offset<1> offset;
	};

} // vk