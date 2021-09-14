#pragma once

#include <cinttypes>
#include <core/named.hpp>
#include "location.hpp"
#include "binding.hpp"
#include "format.hpp"
#include "offset.hpp"

namespace vk {

struct vertex_input_attribute_description {
	vk::location location;
	vk::binding binding;
	vk::format format;
	vk::offset offset;
};

}