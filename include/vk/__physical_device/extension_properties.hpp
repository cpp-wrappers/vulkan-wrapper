#pragma once

#include <type.hpp>

namespace vk {

	struct extension_properties_marker {};

	struct is_extension_properties_reference_t : type_predicate_marker {

		template<typename Type>
		constexpr bool for_type() {
			return
				type_is_reference<Type> &&
				base_of<
					vk::extension_properties_marker,
					remove_reference<Type>
				>;
		}

	};

	static constexpr is_extension_properties_reference_t
		is_extension_properties_reference{}; 

} // vk