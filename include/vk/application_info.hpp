export module vk.application_info;

import <string>;
import vk_headers;
export import <cxx_util/parameter_pack/for_each.hpp>;
export import <cxx_util/parameter_pack/parameter_pack.hpp>;
export import <cxx_util/int.hpp>;
export import vk.api_version;

namespace vk {

struct instance;

export struct application_name : std::string {};
export struct application_version : u::integral_like<uint32_t> {};
export struct engine_name : std::string {};
export struct engine_version : u::integral_like<uint32_t> {};

export class application_info {
	int m_type;
	const void* m_next;
	const char* m_app_name;
	uint32_t m_app_version;
	const char* m_engine_name;
	uint32_t m_engine_version;
	uint32_t m_api_version;

	friend instance;

public:

	application_info(const application_info&) = default;
	application_info(application_info&) = default;

	template<typename... Args>
	application_info(Args&&... args) {
		static_assert(
			u::parameter_pack<Args...>::template count<vk::api_version> == 1
		);

		u::for_each(
			std::forward<Args>(args)...,
			u::do_one_of {
				[&](application_name&& v) { m_app_name = v.c_str(); },
				[&](application_version&& v) { m_app_version = v; },
				[&](engine_name&& v) { m_engine_name = v.c_str(); },
				[&](engine_version&& v) { m_engine_version = v; },
				[&](api_version&& v) { m_api_version = v; }
			}
		);
	}
};

static_assert(sizeof(VkApplicationInfo) == sizeof(application_info));

}