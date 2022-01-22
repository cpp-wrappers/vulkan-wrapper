#pragma once

#include "../type/is_possibly_guarded_handle_of.hpp"

#include <core/meta/types/count_of_satisfying_predicate.hpp>

namespace types::vk {

	template<typename ObjectType>
	struct are_may_contain_one_possibly_guarded_handle_of : types::predicate_marker {

		template<typename... Types>
		static constexpr bool for_types = types::count_of_satisfying_predicate<type::vk::is_possibly_guarded_handle_of<ObjectType>>::template for_types<Types...> <= 1;

		template<typename... Types>
		using indices_of_affected_types = typename types::indices_of_satisfying_predicate<type::vk::is_possibly_guarded_handle_of<ObjectType>>::template for_types<Types...>;
	};

} // types::vk
