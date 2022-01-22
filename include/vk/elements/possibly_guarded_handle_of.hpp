#pragma once

#include "../type/is_possibly_guarded_handle_of.hpp"

#include <core/meta/elements/satisfying_predicate.hpp>

namespace elements::vk {

	template<typename ObjectType>
	inline constexpr auto possibly_guarded_handle_of
		= elements::satisfying_predicate<type::vk::is_possibly_guarded_handle_of<ObjectType>>;

} // vk