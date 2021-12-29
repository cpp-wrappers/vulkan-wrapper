#pragma once

#include <core/type/is_same_as.hpp>
#include <core/type/modifier.hpp>
#include <core/type/remove_const.hpp>
#include <core/types/count_of_satisfying_predicate.hpp>
#include <core/elements/satisfying_predicate.hpp>

#include "handle.hpp"
#include "destroy.hpp"

namespace vk {
	template<typename>
	struct guarded_handle;

	template<typename ObjectType>
	class guarded_handle_base {
		vk::handle<ObjectType> m_handle{};

	public:
		using object_type = ObjectType;

		guarded_handle_base() = default;

		guarded_handle_base(vk::handle<ObjectType> handle)
			: m_handle{ handle }
		{}

		guarded_handle_base(guarded_handle_base&& other)
			: m_handle{ exchange(other.m_handle.value, 0) }
		{}

		void destroy() const {
			vk::destroy<ObjectType>(handle());
		}

		void reset(vk::handle<ObjectType> v = {}) {
			if(handle().value) {
				((vk::guarded_handle<ObjectType>*)this)->destroy();
			}
			handle() = v;
		}

		~guarded_handle_base() {
			reset();
		}

		guarded_handle_base& operator = (guarded_handle_base&& other) {
			reset(other.handle());
			other.handle().value = 0;
			return *this;
		}

		const vk::handle<ObjectType>& handle() const {
			return m_handle;
		}

		vk::handle<ObjectType>& handle() {
			return m_handle;
		}
	};

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

namespace type::vk {

	struct is_guarded_handle {
		static constexpr bool is_type_predicate = true;

		template<typename Type>
		static constexpr bool for_type = ::vk::some_guarded_handle<Type>;
	};

	template<typename ObjectType>
	struct is_guarded_handle_of {
		static constexpr bool is_type_predicate = true;

		template<typename Type>
		static constexpr bool for_type = ::vk::guarded_handle_of<Type, ObjectType>;
	};
}

namespace vk {

	template<typename Type>
	concept some_ordinary_or_guarded_handle =
		vk::some_handle<Type> ||
		vk::some_guarded_handle<Type>;

	template<typename Type, typename ObjectType>
	concept ordinary_or_guarded_handle =
		vk::handle_of<Type, ObjectType> ||
		vk::guarded_handle_of<Type, ObjectType>;
}

namespace type::vk {

	template<typename ObjectType>
	struct is_ordinary_or_guarded_handle {
		static constexpr bool is_type_predicate = true;

		template<typename Type>
		static constexpr bool for_type = ::vk::ordinary_or_guarded_handle<Type, ObjectType>;
	};
}

namespace types::vk {

	template<typename ObjectType>
	struct contain_one {
		static constexpr bool is_types_predicate = true;

		template<typename... Types>
		static constexpr bool for_types_of = types::count_of_satisfying_predicate<type::vk::is_ordinary_or_guarded_handle<ObjectType>>::template for_types_of<Types...> == 1;

		template<typename... Types>
		using indices_of_affected_types_of = typename types::indices_of_satisfying_predicate<type::vk::is_ordinary_or_guarded_handle<ObjectType>>::template for_types_of<Types...>;
	};

	template<typename ObjectType>
	struct may_contain_one {
		static constexpr bool is_types_predicate = true;

		template<typename... Types>
		static constexpr bool for_types_of = types::count_of_satisfying_predicate<type::vk::is_ordinary_or_guarded_handle<ObjectType>>::template for_types_of<Types...> <= 1;

		template<typename... Types>
		using indices_of_affected_types_of = typename types::indices_of_satisfying_predicate<type::vk::is_ordinary_or_guarded_handle<ObjectType>>::template for_types_of<Types...>;
	};
}

namespace elements::vk {

	template<typename ObjectType>
	struct of_type {
		
		template<typename... Types>
		static auto& for_elements_of(Types&... elements) {
			return elements::satisfying_predicate<type::vk::is_ordinary_or_guarded_handle<ObjectType>>::for_elements_of(elements...);
		}
	};
}

namespace vk {

	decltype(auto) get_handle(vk::some_ordinary_or_guarded_handle auto& obj) {
		if constexpr(vk::some_guarded_handle<decltype(obj)>)
			return obj.handle();
		else
			return obj;
	}

	decltype(auto) get_handle_value(vk::some_ordinary_or_guarded_handle auto& obj) {
		return get_handle(obj).value;
	}
}