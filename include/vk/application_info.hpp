#pragma once

#include "headers.hpp"
#include <string_view>
#include <cxx_util/tuple/for_each.hpp>
#include <cxx_util/parameter_pack/parameter_pack.hpp>
#include <cxx_util/null_terminated_string_view.hpp>
#include <cxx_util/tuple/erase.hpp>
#include <cxx_util/named.hpp>
#include <cxx_util/int_with_size.hpp>
#include "api_version.hpp"
#include <cxx_util/params.hpp>

namespace vk {

struct application_name : u::null_terminated_string_view<u::size_is::undefined> {};
struct application_version : u::named<uint32_t> {};
struct engine_name : u::null_terminated_string_view<u::size_is::undefined> {};
struct engine_version : u::named<uint32_t> {};

struct application_info {
	u::int_with_size_of<VkStructureType> m_type = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	const void* m_next = nullptr;
	const char* m_app_name = nullptr;
	uint32_t m_app_version = 0;
	const char* m_engine_name = nullptr;
	uint32_t m_engine_version = 0;
	uint32_t m_api_version = 0;

	application_info(const application_info&) = default;
	application_info(application_info&) = default;
	application_info(application_info&&) = default;

	template<typename... Ps>
	application_info(const Ps&... ps) {
		u::params{ ps... }
			.template handle<u::optional<application_name>>([&](auto app_name){
				m_app_name = app_name;
			})
			.template handle<u::optional<application_version>>([&](auto app_ver) {
				m_app_version = app_ver;
			})
			.template handle<u::optional<engine_name>>([&](auto e_name) {
				m_engine_name = e_name;
			})
			.template handle<u::optional<engine_version>>([&](auto e_ver) {
				m_engine_version = e_ver;
			})
			.template handle<u::required_single<api_version>>([&](auto api_ver) {
				m_api_version = api_ver;
			})
			.check_for_emptiness();
	}
}; // application_info

} // vk

static_assert(sizeof(VkApplicationInfo) == sizeof(vk::application_info));