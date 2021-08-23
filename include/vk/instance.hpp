#pragma once

#include "headers.hpp"
#include <optional>
#include <compare>
#include <cxx_util/tuple/for_each.hpp>
#include "result.hpp"
#include "instance_physical_devices_view.hpp"
#include "instance_create_info.hpp"

namespace vk {

struct instance {
	VkInstance m_instance;

	~instance() {
		vkDestroyInstance(m_instance, nullptr);
	}

	template<typename... Ps>
	instance(const Ps&... ps) noexcept(false) {
		std::optional<vk::application_info> l_application_info;

		u::params{ ps... }
			.template handle<u::optional<vk::application_info>>([&](auto ai) {
				l_application_info.emplace(ai);
			})
			.check_for_emptiness();

		instance_create_info l_instance_crate_info{};
		if(l_application_info.has_value()) {
			l_instance_crate_info.m_application_info = &l_application_info.value();
		}

		vk::throw_if_error(
			(int)vkCreateInstance(
				(VkInstanceCreateInfo*)&l_instance_crate_info,
				nullptr,
				&m_instance
			)
		);
	}

	template<typename F>
	void view_physical_devices(F&& f) const {
		view_instance_physical_devices(
			m_instance,
			std::forward<F>(f)
		);
	}

}; // instance

} // vk