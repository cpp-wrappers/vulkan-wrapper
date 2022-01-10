#pragma once

#include <core/integer.hpp>

#include "declaration.hpp"
#include "type.hpp"

namespace vk {

	template<vk::handle_type>
	struct handle_base;

	template<>
	struct vk::handle_base<vk::dispatchable> {
		void* value;
	};

	template<>
	struct vk::handle_base<vk::non_dispatchable> {
		uint64 value;
	};
}