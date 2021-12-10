#pragma once

#include <core/c_string.hpp>
#include <core/integer.hpp>
#include <core/types/count_of_type.hpp>
#include <core/types/are_contain_type.hpp>
#include <core/types/are_contain_only_types.hpp>
#include <core/elements/at_index.hpp>
#include <core/elements/of_type.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>

#include "api_version.hpp"
#include "../shared/headers.hpp"

namespace vk {

	struct application_name : c_string {};
	struct application_version : wrapper::of_integer<uint32> {};
	struct engine_name : c_string {};
	struct engine_version : wrapper::of_integer<uint32> {};

	struct application_info {
		const uint32 m_type = (uint32) VK_STRUCTURE_TYPE_APPLICATION_INFO;
		const void* next;
		vk::application_name app_name;
		vk::application_version app_version;
		vk::engine_name engine_name;
		vk::engine_version engine_version;
		vk::api_version api_version;

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::count_of_type<vk::application_name>::less_or_equals<1>,
				types::count_of_type<vk::application_version>::less_or_equals<1>,
				types::count_of_type<vk::engine_name>::less_or_equals<1>,
				types::count_of_type<vk::engine_version>::less_or_equals<1>,
				types::count_of_type<vk::api_version>::equals<1>
			>::for_types_of<Args...>
		)
		application_info(Args... args)
			: api_version{ elements::of_type<vk::api_version&>::for_elements_of(args...) }
		{
			if constexpr(types::are_contain_type<vk::application_name>::for_types_of<Args...>)
				app_name = elements::of_type<vk::application_name&>::for_elements_of(args...);
			if constexpr(types::are_contain_type<vk::application_version>::for_types_of<Args...>)
				app_version = elements::of_type<vk::application_version&>::for_elements_of(args...);
			if constexpr(types::are_contain_type<vk::engine_name>::for_types_of<Args...>)
				engine_name = elements::of_type<vk::engine_name&>::for_elements_of(args...);
			if constexpr(types::are_contain_type<vk::engine_version>::for_types_of<Args...>)
				engine_version = elements::of_type<vk::engine_version&>::for_elements_of(args...);
		}
	}; // application_info

} // vk

static_assert(sizeof(vk::application_info) == sizeof(VkApplicationInfo));