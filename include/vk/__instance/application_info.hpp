#pragma once

#include "./api_version.hpp"

#include <c_string.hpp>
#include <types.hpp>

namespace vk {

	struct application_name : c_string_of_unknown_size {};
	enum application_version : uint32 {};
	struct engine_name : c_string_of_unknown_size {};
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
			count_of_decayed_same_as<vk::application_name> <= 1,
			count_of_decayed_same_as<vk::application_version> <= 1,
			count_of_decayed_same_as<vk::engine_name> <= 1,
			count_of_decayed_same_as<vk::engine_version> <= 1,
			count_of_decayed_same_as<vk::api_version> == 1
		>
		application_info(Args... args) :
			api_version {
				tuple{ args... }.template get_decayed_same_as<vk::api_version>()
			}
		{
			if constexpr(types<Args...>::template
				count_of_decayed_same_as<vk::application_name> > 0
			) {
				app_name = tuple{ args... }.template
					get_decayed_same_as<vk::application_name>();
			}

			if constexpr(types<Args...>::template
				count_of_decayed_same_as<vk::application_version> > 0
			) {
				app_version = tuple{ args... }.template
					get_decayed_same_as<vk::application_version>();
			}

			if constexpr(types<Args...>::template
				count_of_decayed_same_as<vk::engine_name> > 0
			) {
				engine_name = tuple{ args... }.template
					get_decayed_same_as<vk::engine_name>();
			}

			if constexpr(types<Args...>::template
				count_of_decayed_same_as<vk::engine_version> > 0
			) {
				engine_version = tuple{ args... }.template
					get_decayed_same_as<vk::engine_version>();
			}

		} // constructor

	}; // application_info

} // vk