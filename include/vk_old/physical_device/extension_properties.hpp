#pragma once

#include <core/meta/type/is_reference.hpp>
#include <core/meta/type/remove_reference.hpp>
#include <core/meta/type/is_base.hpp>
#include <core/meta/type/predicate.hpp>

namespace vk {

	struct extension_properties_marker {};

	struct is_extension_properties_reference : type::predicate_marker {

		template<typename Type>
		static constexpr bool for_type =
			type::is_reference::for_type<Type> &&
			type::is_base<vk::extension_properties_marker>::for_type<
				remove_reference<Type>
			>;

	};

} // vk