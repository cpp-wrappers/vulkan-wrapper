#pragma once

#include "../../shared/location.hpp"
#include "../../shared/binding.hpp"
#include "../../image/format.hpp"
#include "../../shared/offset.hpp"

namespace vk {

	struct vertex_input_attribute_description {
		vk::location location;
		vk::binding binding;
		vk::format format;
		vk::offset<1u> offset;
	};

}