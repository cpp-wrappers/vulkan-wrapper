#pragma once

#include "handle.hpp"

namespace type::vk {

	struct is_handle {
		static constexpr bool is_type_predicate = true;

		template<typename Type>
		static constexpr bool for_type = ::vk::some_handle<Type>;
	};

	template<typename ObjectType>
	struct is_handle_of {
		static constexpr bool is_type_predicate = true;

		template<typename Type>
		static constexpr bool for_type = ::vk::handle_of<Type, ObjectType>;
	};
}