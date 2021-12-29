#pragma once

#include <core/integer.hpp>
#include <core/type/is_base.hpp>
#include <core/type/is_same_as.hpp>

namespace vk {

	enum handle_type {
		dispatchable, non_dispatchable
	};

	template<vk::handle_type>
	struct handle_base;

	template<>
	struct handle_base<vk::dispatchable> {
		void* value;
	};

	template<>
	struct handle_base<vk::non_dispatchable> {
		uint64 value;
	};

	template<typename>
	struct handle;

	template<typename Type>
	concept some_handle =
		type::is_base<vk::handle_base<::vk::non_dispatchable>>::ignore_const::ignore_reference::for_type<Type> ||
		type::is_base<vk::handle_base<::vk::dispatchable>>::ignore_const::ignore_reference::for_type<Type>;

	template<typename Type, typename ObjectType>
	concept handle_of = some_handle<Type> && type::is_same_as<vk::handle<ObjectType>>::ignore_const::ignore_reference::template for_type<Type>;

	template<typename ObjectType>
	inline constexpr bool is_allocatable = false;

	template<typename ObjectType>
	inline constexpr bool is_creatable = !is_allocatable<ObjectType>;
}

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