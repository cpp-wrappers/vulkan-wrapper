#pragma once

#include "headers.hpp"
#include <cstdint>
#include <optional>
#include <compare>
#include "result.hpp"
#include "instance_physical_devices_view.hpp"
#include "instance_create_info.hpp"
#include "application_info.hpp"
#include "physical_device.hpp"
#include <core/tuple.hpp>

namespace vk {

struct instance {
	VkInstance m_instance;

	~instance() {
		vkDestroyInstance(m_instance, nullptr);
	}

	template<typename... Args>
	requires(
		types::of<Args...>::template count<vk::application_info> <= 1 &&
		types::of<Args...>::template erase_types<
			vk::application_info,
			vk::enabled_layer_name,
			vk::enabled_extension_name
		>::empty
	)
	instance(Args&&... args) noexcept(false) {
		instance_create_info ici{};
		std::optional<vk::application_info> ai;

		ici.enabled_layer_count = types::of<Args...>::template count<vk::enabled_layer_name>;
		ici.enabled_extension_count = types::of<Args...>::template count<vk::enabled_extension_name>;

		vk::enabled_layer_name layers_names[ici.enabled_layer_count];
		vk::enabled_extension_name extensions_names[ici.enabled_extension_count];
		uint32_t current_layer = 0;
		uint32_t current_extension = 0;

		tuple{ std::forward<Args>(args)... }
			.consume([&](vk::application_info ai0) {
				ai.emplace(ai0);
			})
			.consume([&](vk::enabled_layer_name eln) {
				layers_names[current_layer++] = eln;
			})
			.consume([&](vk::enabled_extension_name eln) {
				extensions_names[current_extension++] = eln;
			});

		if(ai.has_value()) {
			ici.application_info = &ai.value();
		}
		ici.enabled_layer_names = layers_names;
		ici.enabled_extension_names = extensions_names;

		vk::throw_if_error(
			vkCreateInstance(
				(VkInstanceCreateInfo*)&ici,
				nullptr,
				&m_instance
			)
		);
	}

	uint32_t physical_devices_count() const {
		uint32_t count;
		vk::throw_if_error(
			vkEnumeratePhysicalDevices(
				m_instance,
				&count,
				nullptr
			)
		);
		return count;
	}

	template<typename F>
	void view_physical_devices(uint32_t count, F&& f) const {
		view_instance_physical_devices(
			count,
			m_instance,
			std::forward<F>(f)
		);
	}

	template<typename F>
	void view_physical_devices(F&& f) const {
		view_physical_devices(
			physical_devices_count(),
			std::forward<F>(f)
		);
	}

	vk::physical_device first_physical_device() {
		vk::physical_device d;
		view_physical_devices(1, [&](auto& devs) { d = devs.front(); });
		return d;
	}

	void for_each_physical_device(auto&& f) {
		view_physical_devices([&](auto& view) {
			for(auto& device : view) f(device);
		});
	}

}; // instance

} // vk