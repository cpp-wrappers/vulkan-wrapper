#pragma once

#include "api_version.hpp"

#include <core/c_string.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/elements/at_index.hpp>

namespace vk {

	struct application_name : c_string {};
	enum application_version : uint32 {};
	struct engine_name : c_string {};
	enum engine_version : uint32 {};

	struct application_info {
		uint32 structure_type = 0;
		const void* next = nullptr;
		vk::application_name app_name;
		vk::application_version app_version{};
		vk::engine_name engine_name{};
		vk::engine_version engine_version{};
		vk::api_version api_version{};

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_may_contain_one_decayed<vk::application_name>,
			types::are_may_contain_one_decayed<vk::application_version>,
			types::are_may_contain_one_decayed<vk::engine_name>,
			types::are_may_contain_one_decayed<vk::engine_version>,
			types::are_contain_one_decayed<vk::api_version>
		>::for_types<Args...>
		application_info(Args... args) :
			api_version{ elements::decayed<vk::api_version>(args...) }
		{
			if constexpr(
				types::are_contain_decayed<vk::application_name>::
				for_types<Args...>
			) {
				app_name = elements::decayed<vk::application_name>(args...);
			}

			if constexpr(
				types::are_contain_decayed<vk::application_version>::
				for_types<Args...>
			) {
				app_version =
					elements::decayed<vk::application_version>(args...);
			}

			if constexpr(
				types::are_contain_decayed<vk::engine_name>::
				for_types<Args...>
			) {
				engine_name = elements::decayed<vk::engine_name>(args...);
			}

			if constexpr(
				types::are_contain_decayed<vk::engine_version>::
				for_types<Args...>
			) {
				engine_version = elements::decayed<vk::engine_version>(args...);
			}

		} // constructor

	}; // application_info

} // vk