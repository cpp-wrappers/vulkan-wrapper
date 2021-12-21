#pragma once

#include <core/type/is_same_as.hpp>
#include <core/type/modifier.hpp>
#include <core/type/remove_const.hpp>
#include <core/types/count_of_satisfying_predicate.hpp>
#include <core/elements/satisfying_predicate.hpp>

namespace vk {
	template<typename VkObjectType>
	class guarded;
}

namespace type::vk {

	template<typename VkObjectType>
	struct is_ordinary {
		static constexpr bool is_type_predicate = true;

		template<typename Type>
		static constexpr bool for_type = type::is_same_as<VkObjectType>::ignore_const::ignore_reference::template for_type<Type>;
	};

	template<typename VkObjectType>
	struct is_guarded {
		static constexpr bool is_type_predicate = true;

		template<typename Type>
		static constexpr bool for_type =
			type::is_same_as<::vk::guarded<VkObjectType>>::ignore_const::ignore_reference::template for_type<Type>;
	};
}

namespace vk {
	template<typename Type, typename VkObjectType>
	concept ordinary_or_guarded = type::vk::is_ordinary<VkObjectType>::template for_type<Type> || type::vk::is_guarded<VkObjectType>::template for_type<Type>;
}

namespace type::vk {

	template<typename VkObjectType>
	struct is_ordinary_or_guarded {
		static constexpr bool is_type_predicate = true;

		template<typename Type>
		static constexpr bool for_type = ::vk::ordinary_or_guarded<Type, VkObjectType>;
	};
}

namespace types::vk {

	template<typename VkObjectType>
	struct contain_one {
		static constexpr bool is_types_predicate = true;

		template<typename... Types>
		static constexpr bool for_types_of = types::count_of_satisfying_predicate<type::vk::is_ordinary_or_guarded<VkObjectType>>::template for_types_of<Types...> == 1;

		template<typename... Types>
		using indices_of_affected_types_of = typename types::indices_of_satisfying_predicate<type::vk::is_ordinary_or_guarded<VkObjectType>>::template for_types_of<Types...>;
	};


	template<typename VkObjectType>
	struct may_contain_one {
		static constexpr bool is_types_predicate = true;

		template<typename... Types>
		static constexpr bool for_types_of = types::count_of_satisfying_predicate<type::vk::is_ordinary_or_guarded<VkObjectType>>::template for_types_of<Types...> <= 1;

		template<typename... Types>
		using indices_of_affected_types_of = typename types::indices_of_satisfying_predicate<type::vk::is_ordinary_or_guarded<VkObjectType>>::template for_types_of<Types...>;
	};
}

namespace elements::vk {

	template<typename VkObjectType>
	struct of_type {
		
		template<typename... Types>
		static auto& for_elements_of(Types&... elements) {
			return elements::satisfying_predicate<type::vk::is_ordinary_or_guarded<VkObjectType>>::for_elements_of(elements...);
		}
	};
}

namespace vk {

	template<typename VkObjectType>
	decltype(auto) get_handle(vk::ordinary_or_guarded<VkObjectType> auto& obj) {
		if constexpr(type::vk::is_guarded<VkObjectType>::template for_type<decltype(obj)>) {
			return obj.object();
		}
		else {
			return obj;
		}
	}

	template<typename VkObjectType>
	decltype(auto) get_raw_handle(vk::ordinary_or_guarded<VkObjectType> auto& obj) {
		return get_handle<VkObjectType>(obj).handle;
	}
}