#pragma once

#include <type.hpp>

namespace vk {

	struct extension_properties_mark {};

	struct is_extension_properties_reference_t :
		type_predicate_extensions<is_extension_properties_reference_t>
	{

		template<typename Type>
		constexpr bool for_type() {
			return
				type_is_reference<Type> &&
				base_of<
					vk::extension_properties_mark,
					remove_reference<Type>
				>;
		}

	};

	static constexpr is_extension_properties_reference_t
		is_extension_properties_reference{}; 

} // vk