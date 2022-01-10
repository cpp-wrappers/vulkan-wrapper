#pragma once

#include "../object/handle/concepts.hpp"

namespace type::vk {

	template<typename ObjectType>
	struct is_possibly_guarded_handle_of {
		static constexpr bool is_type_predicate = true;

		template<typename Type>
		static constexpr bool for_type = ::vk::possibly_guarded_handle_of<Type, ObjectType>;
	};
}