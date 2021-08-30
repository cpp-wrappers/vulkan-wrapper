#pragma once

#include "headers.hpp"
#include <cstdint>
#include <string_view>
#include "api_version.hpp"
#include <core/null_terminated_string_view.hpp>
#include <core/named.hpp>
#include <core/integer.hpp>
#include <type_traits>

namespace vk {

struct application_name : null_terminated_string_view<size_is::undefined> {};
struct application_version : named<uint32_t> {};
struct engine_name : null_terminated_string_view<size_is::undefined> {};
struct engine_version : named<uint32_t> {};

struct application_info {
	int_with_size_of<VkStructureType> m_type = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	const void* m_next = nullptr;
	const char* m_app_name = nullptr;
	uint32_t m_app_version = 0;
	const char* m_engine_name = nullptr;
	uint32_t m_engine_version = 0;
	uint32_t m_api_version = 0;

	application_info(const application_info&) = default;
	application_info(application_info&) = default;
	application_info(application_info&&) = default;

	template<typename... Args>
	requires(
		types::of<Args...>::template count<vk::application_name> <= 1 &&
		types::of<Args...>::template count<vk::application_version> <= 1 && 
		types::of<Args...>::template count<vk::engine_name> <= 1 &&
		types::of<Args...>::template count<vk::engine_version> <= 1 &&
		types::of<Args...>::template count<vk::api_version> == 1 &&
		types::of<Args...>::template erase_types<
			vk::application_name,
			vk::application_version,
			vk::engine_name,
			vk::engine_version,
			vk::api_version
		>::empty
	)
	application_info(Args&&... args) {
		using Ts = types::of<Args...>;
		tuple { std::forward<Args>(args)... }
			.consume([&](vk::application_name v) {
				m_app_name = v.data();
			})
			.consume([&](vk::application_version v) {
				m_app_version = v.value;
			})
			.consume([&](vk::engine_name v) {
				m_engine_name = v.data();
			})
			.consume([&](vk::engine_version v) {
				m_engine_version = v.value;
			})
			.consume([&](vk::api_version v) {
				m_api_version = v.value;
			});
	}
}; // application_info

} // vk

static_assert(sizeof(VkApplicationInfo) == sizeof(vk::application_info));