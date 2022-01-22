#pragma once

#include "api_version.hpp"
#include "../../shared/headers.hpp"

#include <core/c_string.hpp>
#include <core/meta/types/are_contain_decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/meta/elements/at_index.hpp>
#include <core/meta/elements/decayed_same_as.hpp>

namespace vk {

	struct application_name : c_string {};
	struct application_version : wrapper::of_integer<uint32> {};
	struct engine_name : c_string {};
	struct engine_version : wrapper::of_integer<uint32> {};

	struct application_info {
		const uint32 m_type = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		const void* const next;
		vk::application_name app_name;
		vk::application_version app_version;
		vk::engine_name engine_name;
		vk::engine_version engine_version;
		vk::api_version api_version;

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::are_may_contain_one_decayed_same_as<vk::application_name>,
			types::are_may_contain_one_decayed_same_as<vk::application_version>,
			types::are_may_contain_one_decayed_same_as<vk::engine_name>,
			types::are_may_contain_one_decayed_same_as<vk::engine_version>,
			types::are_contain_one_decayed_same_as<vk::api_version>
		>::for_types<Args...>
		application_info(Args... args)
			: api_version{ elements::decayed_same_as<vk::api_version&>(args...) }
		{
			if constexpr(types::are_contain_decayed_same_as<vk::application_name>::for_types<Args...>)
				app_name = elements::decayed_same_as<vk::application_name&>(args...);
			if constexpr(types::are_contain_decayed_same_as<vk::application_version>::for_types<Args...>)
				app_version = elements::decayed_same_as<vk::application_version&>(args...);
			if constexpr(types::are_contain_decayed_same_as<vk::engine_name>::for_types<Args...>)
				engine_name = elements::decayed_same_as<vk::engine_name&>(args...);
			if constexpr(types::are_contain_decayed_same_as<vk::engine_version>::for_types<Args...>)
				engine_version = elements::decayed_same_as<vk::engine_version&>(args...);
		}
	};

} // vk

static_assert(sizeof(vk::application_info) == sizeof(VkApplicationInfo));