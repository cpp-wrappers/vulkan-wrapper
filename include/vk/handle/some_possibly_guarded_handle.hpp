#pragma once

#include "some_handle.hpp"
#include "some_guarded_handle.hpp"

namespace type::vk {

	struct is_some_possibly_guarded_handle : ::type::predicate_marker {

		template<typename Type>
		static constexpr bool for_type =
			type::vk::is_some_handle::for_type<Type> ||
			type::vk::is_some_guarded_handle::for_type<Type>;

	};

	template<typename Type>
	concept some_possibly_guarded_handle = type::vk::is_some_possibly_guarded_handle::for_type<Type>;

}