#pragma once

#include "./api_version.hpp"

#include <c_string.hpp>
#include <types.hpp>
#include <tuple.hpp>

#include <unicode/utf8.hpp>

namespace vk {

	struct application_name : c_string<utf8::unit> {
		using c_string::c_string;
	};
	enum application_version : uint32 {};
	struct engine_name : c_string<utf8::unit> {
		using c_string::c_string;
	};
	enum engine_version : uint32 {};

	struct application_info {
		uint32                  structure_type = 0;
		const void*             next = nullptr;
		vk::application_name    app_name{ nullptr };
		vk::application_version app_version{};
		vk::engine_name         engine_name{ nullptr };
		vk::engine_version      engine_version{};
		vk::api_version         api_version{};

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			is_same_as<vk::application_name>.decayed <= 1,
			is_same_as<vk::application_version>.decayed <= 1,
			is_same_as<vk::engine_name>.decayed <= 1,
			is_same_as<vk::engine_version>.decayed <= 1,
			is_same_as<vk::api_version>.decayed == 1
		>
		application_info(Args... args) :
			api_version {
				tuple{ args... }.template get<is_same_as<vk::api_version>.decayed>()
			}
		{
			if constexpr(
				(is_same_as<vk::application_name>.decayed > 0)
				.for_types<Args...>()
			) {
				app_name = tuple{ args... }.template
					get<is_same_as<vk::application_name>.decayed>();
			}

			if constexpr(
				(is_same_as<vk::application_version>.decayed > 0)
				.for_types<Args...>()
			) {
				app_version = tuple{ args... }.template
					get<is_same_as<vk::application_version>.decayed>();
			}

			if constexpr(
				(is_same_as<vk::engine_name>.decayed > 0)
				.for_types<Args...>()
			) {
				engine_name = tuple{ args... }.template
					get<is_same_as<vk::engine_name>.decayed>();
			}

			if constexpr(
				(is_same_as<vk::engine_version>.decayed > 0)
				.for_types<Args...>()
			) {
				engine_version = tuple{ args... }.template
					get<is_same_as<vk::engine_version>.decayed>();
			}

		} // constructor

	}; // application_info

} // vk