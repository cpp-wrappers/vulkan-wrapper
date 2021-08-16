#pragma once

#include <string>
#include "headers.hpp"
#include <cxx_util/parameter_pack/for_each.hpp>
#include <cxx_util/parameter_pack/parameter_pack.hpp>
#include <cxx_util/int.hpp>
#include <cxx_util/null_terminated_string_view.hpp>
#include "api_version.hpp"

namespace vk {

struct instance;

struct application_name : u::null_terminated_string_view<u::size_is::undefined> {};
struct application_version : u::integral_like<uint32_t> {};
struct engine_name : u::null_terminated_string_view<u::size_is::undefined> {};
struct engine_version : u::integral_like<uint32_t> {};

class application_info {
	u::int_with_size<sizeof(VkStructureType)> m_type = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	const void* m_next = nullptr;
	const char* m_app_name = nullptr;
	uint32_t m_app_version = 0;
	const char* m_engine_name = nullptr;
	uint32_t m_engine_version = 0;
	uint32_t m_api_version = 0;

	friend instance;

public:

	application_info(const application_info&) = default;
	application_info(application_info&) = default;
	application_info(application_info&&) = default;

	template<typename... Args>
	application_info(Args&&... args) {
		static_assert(
			u::parameter_pack<Args...>::template count<vk::api_version> == 1
		);

		u::for_each(
			std::forward<Args>(args)...,
			u::do_one_of {
				[&](application_name&& v) { m_app_name = v.data(); },
				[&](application_version&& v) { m_app_version = v; },
				[&](engine_name&& v) { m_engine_name = v.data(); },
				[&](engine_version&& v) { m_engine_version = v; },
				[&](api_version&& v) { m_api_version = v; }
			}
		);
	}
}; // application_info

} // vk

static_assert(sizeof(VkApplicationInfo) == sizeof(vk::application_info));