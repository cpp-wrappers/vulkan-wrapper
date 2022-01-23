#pragma once

#include <core/meta/type/predicate.hpp>
#include "guarded_handle_of.hpp"
#include "handle_of.hpp"

namespace type::vk {

	template<typename ObjectType>
	struct is_possibly_guarded_handle_of : ::type::predicate_marker {

		template<typename Type>
		static constexpr bool for_type =
			type::vk::is_handle_of<ObjectType>::template for_type<Type> ||
			type::vk::is_guarded_handle_of<ObjectType>::template for_type<Type>;

	};
}

#include <core/meta/types/are_contain_satisfying_predicate.hpp>

namespace types::vk {

	template<typename ObjectType>
	struct are_contain_one_possibly_guarded_handle_of : ::types::are_contain_one_satisfying_predicate<type::vk::is_possibly_guarded_handle_of<ObjectType>> {};


	template<typename ObjectType>
	struct are_may_contain_one_possibly_guarded_handle_of : ::types::are_may_contain_one_satisfying_predicate<type::vk::is_possibly_guarded_handle_of<ObjectType>> {};

}

#include <core/meta/elements/satisfying_predicate.hpp>

namespace elements::vk {

	template<typename ObjectType>
	inline constexpr auto possibly_guarded_handle_of = ::elements::satisfying_predicate<type::vk::is_possibly_guarded_handle_of<ObjectType>>;

}

namespace vk {

	template<typename Type, typename ObjectType>
	concept possibly_guarded_handle_of = type::vk::is_possibly_guarded_handle_of<ObjectType>::template for_type<Type>;

}