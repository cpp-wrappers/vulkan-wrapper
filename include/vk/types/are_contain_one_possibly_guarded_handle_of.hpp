#pragma once

#include <core/types/count_of_satisfying_predicate.hpp>
#include "../type/is_possibly_guarded_handle_of.hpp"

namespace types::vk {

	template<typename ObjectType>
	struct are_contain_one_possibly_guarded_handle_of : types::predicate_marker {

		template<typename... Types>
		static constexpr bool for_types_of = types::count_of_satisfying_predicate<type::vk::is_possibly_guarded_handle_of<ObjectType>>::template for_types_of<Types...> == 1;

		template<typename... Types>
		using indices_of_affected_types_of = typename types::indices_of_satisfying_predicate<type::vk::is_possibly_guarded_handle_of<ObjectType>>::template for_types_of<Types...>;
	};

} // types::vk