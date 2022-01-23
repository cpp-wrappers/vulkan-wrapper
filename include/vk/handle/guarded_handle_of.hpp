#pragma once

#include "guarded/declaration.hpp"

#include <core/meta/type/decay.hpp>
#include <core/meta/type/is_same_as.hpp>
#include <core/meta/type/predicate.hpp>

namespace type::vk {

	template<typename ObjectType>
	struct is_guarded_handle_of : ::type::predicate_marker {

		template<typename Type>
		static constexpr bool for_type
			= type::is_same_as<
				::vk::guarded_handle<ObjectType>
			>::template for_type<::decay<Type>
		>;

	};

}

namespace vk {

	template<typename Type, typename ObjectType>
	concept guarded_handle_of = type::vk::is_guarded_handle_of<ObjectType>::template for_type<Type>;

}