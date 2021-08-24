#pragma once

#include "headers.hpp"
#include <cstdint>
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
	instance(const Ps&... params) noexcept(false) {
		u::params ps{ params... };

		instance_create_info l_instance_crate_info{};
		std::optional<vk::application_info> l_application_info;

		l_instance_crate_info.m_enabled_layer_count
			= ps.template count<const vk::enabled_layer_name&>();

		vk::enabled_layer_name layers_names[l_instance_crate_info.m_enabled_layer_count];
		uint32_t current_layer = 0;

		ps
			.template handle<u::optional<const vk::application_info&>>([&](auto ai) {
				l_application_info.emplace(ai);
			})
			.template handle<u::any<const vk::enabled_layer_name&>>([&](auto eln) {
				layers_names[current_layer++] = eln;
			})
			.check_for_emptiness();

		if(l_application_info.has_value()) {
			l_instance_crate_info.m_application_info = &l_application_info.value();
		}
		l_instance_crate_info.m_enabled_layer_names = layers_names;

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