#pragma once

#include <core/type/is_base.hpp>
#include "base.hpp"

namespace vk {

	template<typename>
	struct guarded_handle;

	template<typename>
	inline constexpr bool is_some_guarded_handle = false;

	template<typename Type>
	inline constexpr bool is_some_guarded_handle<vk::guarded_handle<Type>> = true;

	template<typename Type>
	concept some_guarded_handle = is_some_guarded_handle<decay<Type>>;
		//type::is_base<
		//	vk::guarded_handle_base<::decay<Type>>::object_type>
		//>::ignore_const::ignore_reference::template for_type<Type>;

	template<typename Type, typename ObjectType>
	concept guarded_handle_of =
		some_guarded_handle<Type> &&
		type::is_same_as<ObjectType>::template for_type<typename decay<Type>::object_type>;

} // vk