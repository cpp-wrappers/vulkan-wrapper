export module vk.application_info;

import <string>;
import vk_headers;
export import <cxx_util/parameter_pack/for_each.hpp>;
export import <cxx_util/parameter_pack/parameter_pack.hpp>;
export import vk.api_version;

namespace vk {

struct instance;

export struct application_name : std::string {};
export struct application_version { uint32_t value; };
export struct engine_name : std::string {};
export struct engine_version { uint32_t value; };

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
	application_info(Args&&... values) {
		static_assert(
			u::parameter_pack<Args...>::template contains<vk::api_version>
		);

		u::for_each(
			u::combined {
				[&](application_name&& v) { m_app_name = v.c_str(); },
				[&](application_version&& v) { m_app_version = v.value; },
				[&](engine_name&& v) { m_engine_name = v.c_str(); },
				[&](engine_version&& v) { m_engine_version = v.value; },
				[&](api_version&& v) { m_api_version = v.value; },
			},
			std::forward<Args>(values)...
		);
	}
};

static_assert(sizeof(VkApplicationInfo) == sizeof(application_info));

}