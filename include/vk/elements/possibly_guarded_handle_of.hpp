#pragma once

#include <core/elements/satisfying_predicate.hpp>
#include "../type/is_possibly_guarded_handle_of.hpp"

namespace elements::vk {

	template<typename ObjectType>
	struct possibly_guarded_handle_of
		: elements::satisfying_predicate<type::vk::is_possibly_guarded_handle_of<ObjectType>> {};

} // vk