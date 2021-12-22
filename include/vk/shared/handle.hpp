#pragma once

#include <core/integer.hpp>

namespace vk {

	enum handle_type {
		dispatchable, non_dispatchable
	};

	template<vk::handle_type>
	struct handle_base;

	template<>
	struct handle_base<vk::dispatchable> {
		void* value;
	};

	template<>
	struct handle_base<vk::non_dispatchable> {
		uint64 value;
	};

	template<typename>
	struct handle;
}