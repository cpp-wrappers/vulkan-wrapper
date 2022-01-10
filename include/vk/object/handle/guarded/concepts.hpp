#pragma once

#include <core/type/is_base.hpp>
#include "base.hpp"

namespace vk {
	template<typename>
	struct guarded_handle;

	template<typename Type>
	concept some_guarded_handle =
		type::is_base<
			vk::guarded_handle_base<typename type::remove_const::for_type<type::remove_reference::for_type<Type>>::object_type>
		>::ignore_const::ignore_reference::template for_type<Type>;

	template<typename Type, typename ObjectType>
	concept guarded_handle_of =
		some_guarded_handle<Type> &&
		type::is_same_as<ObjectType>::template
		for_type<typename type::remove_const::for_type<type::remove_reference::for_type<Type>>::object_type>;
}