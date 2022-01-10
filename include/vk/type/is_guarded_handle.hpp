#pragma once

#include "guarded_handle.hpp"

namespace type::vk {

	struct is_guarded_handle {
		static constexpr bool is_type_predicate = true;

		template<typename Type>
		static constexpr bool for_type = ::vk::some_guarded_handle<Type>;
	};

	template<typename ObjectType>
	struct is_guarded_handle_of {
		static constexpr bool is_type_predicate = true;

		template<typename Type>
		static constexpr bool for_type = ::vk::guarded_handle_of<Type, ObjectType>;
	};
}
