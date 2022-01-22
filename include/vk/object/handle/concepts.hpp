#pragma once

#include "declaration.hpp"
#include "base.hpp"
#include "guarded/concepts.hpp"

#include <core/integer.hpp>
#include <core/meta/type/is_base.hpp>
#include <core/meta/type/is_same_as.hpp>

namespace vk {

	template<typename Type>
	concept some_handle =
		type::is_base<vk::handle_base<::vk::non_dispatchable>>::for_type<decay<Type>> ||
		type::is_base<vk::handle_base<::vk::dispatchable>>::for_type<decay<Type>>;

	template<typename Type, typename ObjectType>
	concept handle_of =
		some_handle<Type> &&
		type::is_same_as<vk::handle<ObjectType>>::template for_type<decay<Type>>;

	template<typename Type>
	concept some_possibly_guarded_handle =
		vk::some_handle<Type> ||
		vk::some_guarded_handle<Type>;

	template<typename Type, typename ObjectType>
	concept possibly_guarded_handle_of =
		vk::handle_of<Type, ObjectType> ||
		vk::guarded_handle_of<Type, ObjectType>;

} // vk