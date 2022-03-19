#pragma once

#include <core/integer.hpp>
#include <core/handle/declaration.hpp>

#include "type.hpp"

namespace vk {

	template<handle_type>
	struct handle_base;

	template<>
	struct handle_base<vk::dispatchable> {
		void* value;

		void reset_value() { value = nullptr; }
	};

	template<>
	struct handle_base<vk::non_dispatchable> {
		uint64 value;

		void reset_value() { value = 0; }
	};

} // vk