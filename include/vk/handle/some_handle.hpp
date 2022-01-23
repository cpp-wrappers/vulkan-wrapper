#pragma once

#include "declaration.hpp"

#include <core/meta/type/predicate.hpp>
#include <core/meta/type/decay.hpp>

namespace type::vk {

	class is_some_handle : ::type::predicate_marker {
		template<typename Type>
		static constexpr bool for_decayed_type = false;

		template<typename Type>
		static constexpr bool for_decayed_type<::vk::handle<Type>> = true;
			
	public:

		template<typename Type>
		static constexpr bool for_type = for_decayed_type<::decay<Type>>;

	};

	template<typename Type>
	concept some_handle = type::vk::is_some_handle::for_type<Type>;

}