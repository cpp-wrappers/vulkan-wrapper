#pragma once

#include <core/types/count_of_satisfying_predicate.hpp>

namespace vk {
	
	template<typename Type>
	struct required {
		Type value;
	};

	template<typename Type>
	required(Type&&) -> required<Type>;

	template<typename Type>
	required(Type&) -> required<Type>;

	template<typename Type>
	struct desired {
		Type value;
	};

	template<typename Type>
	desired(Type&&) -> desired<Type>;

	template<typename Type>
	desired(Type&) -> desired<Type>;

}

namespace type::vk {

	struct is_required : type::predicate_marker {
		template<typename Type>
		static constexpr bool for_type = false;

		template<typename Type>
		static constexpr bool for_type<::vk::required<Type>> = true;
	};

	struct is_desired : type::predicate_marker {
		template<typename Type>
		static constexpr bool for_type = false;

		template<typename Type>
		static constexpr bool for_type<::vk::desired<Type>> = true;
	};

}

namespace types::vk {

	using count_of_required = types::count_of_satisfying_predicate<type::vk::is_required>;
	using count_of_desired = types::count_of_satisfying_predicate<type::vk::is_desired>;

}