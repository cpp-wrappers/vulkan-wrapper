#pragma once

#include "../../__internal/location.hpp"
#include "../../__internal/binding.hpp"
#include "../../__internal/offset.hpp"
#include "../../__internal/format.hpp"

namespace vk {

	struct vertex_input_attribute_description {
		vk::location location;
		vk::binding binding;
		vk::format format;
		vk::offset<1> offset;
	};

} // vk