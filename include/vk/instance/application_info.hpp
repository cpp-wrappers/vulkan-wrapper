#pragma once

#include <core/null_terminated_string_view.hpp>
#include <core/integer.hpp>
#include <core/types/count_of_type.hpp>
#include <core/types/are_contain_type.hpp>
#include <core/types/are_contain_only_types.hpp>
#include <core/elements/at_index.hpp>
#include <core/elements/of_type.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>

#include "api_version.hpp"
#include "../headers.hpp"

namespace vk {

struct application_name : null_terminated_string_view<size_is::undefined> {};
struct application_version : uint32 {};
struct engine_name : null_terminated_string_view<size_is::undefined> {};
struct engine_version : uint32 {};

struct application_info {
	unsigned_integer_of_size_of<VkStructureType> m_type {
		(primitive::uint32) VK_STRUCTURE_TYPE_APPLICATION_INFO
	};
	const void* next = nullptr;
	vk::application_name app_name;
	vk::application_version app_version;
	vk::engine_name engine_name;
	vk::engine_version engine_version;
	vk::api_version api_version;

	application_info(const application_info&) = default;
	application_info(application_info&) = default;
	application_info(application_info&&) = default;

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::application_name>::less_or_equals<1u>,
			types::count_of_type<vk::application_version>::less_or_equals<1u>,
			types::count_of_type<vk::engine_name>::less_or_equals<1u>,
			types::count_of_type<vk::engine_version>::less_or_equals<1u>,
			types::count_of_type<vk::api_version>::equals<1u>
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

static_assert(sizeof(VkApplicationInfo) == sizeof(vk::application_info));