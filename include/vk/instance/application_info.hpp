#pragma once

#include <cstdint>

#include <core/null_terminated_string_view.hpp>
#include <core/named.hpp>
#include <core/integer.hpp>

#include "../headers.hpp"
#include "../api_version.hpp"

namespace vk {

struct application_name : null_terminated_string_view<size_is::undefined> {};
struct application_version : named<uint32_t> {};
struct engine_name : null_terminated_string_view<size_is::undefined> {};
struct engine_version : named<uint32_t> {};

struct application_info {
	int_with_size_of<VkStructureType> m_type = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	const void* next = nullptr;
	vk::application_name app_name{ nullptr };
	vk::application_version app_version{ 0 };
	vk::engine_name engine_name{ nullptr };
	vk::engine_version engine_version{ 0 };
	vk::api_version api_version{};

	application_info(const application_info&) = default;
	application_info(application_info&) = default;
	application_info(application_info&&) = default;

	template<typename... Args>
	requires(
		types::of<Args...>::template count_of_same_as_type<vk::application_name> <= 1 &&
		types::of<Args...>::template count_of_same_as_type<vk::application_version> <= 1 && 
		types::of<Args...>::template count_of_same_as_type<vk::engine_name> <= 1 &&
		types::of<Args...>::template count_of_same_as_type<vk::engine_version> <= 1 &&
		types::of<Args...>::template count_of_same_as_type<vk::api_version> == 1 &&
		types::of<Args...>::template erase_same_as_one_of_types<
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
			.get([&](vk::application_name v) {
				app_name = v;
			})
			.get([&](vk::application_version v) {
				app_version = v;
			})
			.get([&](vk::engine_name v) {
				engine_name = v;
			})
			.get([&](vk::engine_version v) {
				engine_version = v;
			})
			.get([&](vk::api_version v) {
				api_version = v;
			});
	}
}; // application_info

} // vk

static_assert(sizeof(VkApplicationInfo) == sizeof(vk::application_info));