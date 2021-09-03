#pragma once

#include "headers.hpp"
#include <cstdint>
#include <functional>
#include <optional>
#include <compare>
#include "result.hpp"
#include "instance_physical_devices_view.hpp"
#include "instance_create_info.hpp"
#include "application_info.hpp"
#include "physical_device.hpp"
#include <core/tuple.hpp>
#include <vulkan/vulkan_core.h>

namespace vk {

class instance {
	instance() = delete;
	instance(const instance&) = delete;
public:

	uint32_t physical_devices_count() const {
		uint32_t count;
		vk::throw_if_error(
			vkEnumeratePhysicalDevices(
				(VkInstance)this,
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
			(VkInstance)this,
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

	vk::physical_device& first_physical_device() {
		vk::physical_device* ptr;

		view_physical_devices(1, [&](auto& devices) {
			ptr = &devices.front();
		});

		return *ptr;
	}

	void for_each_physical_device(auto&& f) {
		view_physical_devices([&](auto& view) {
			for(vk::physical_device& device : view) f(device);
		});
	}
}; // instance

template<typename... Args>
requires(
	types::of<Args...>::template count_of_same_as_type<vk::application_info> <= 1 &&
	types::of<Args...>::template erase_same_as_one_of_types<
		vk::application_info,
		vk::enabled_layer_name,
		vk::enabled_extension_name
	>::empty
)
vk::instance& create_instance(Args&&... args) {
	instance_create_info ici{};

	ici.enabled_layer_count = types::of<Args...>::template count_of_same_as_type<vk::enabled_layer_name>;
	ici.enabled_extension_count = types::of<Args...>::template count_of_same_as_type<vk::enabled_extension_name>;

	vk::enabled_layer_name layers_names[ici.enabled_layer_count];
	vk::enabled_extension_name extensions_names[ici.enabled_extension_count];
	uint32_t current_layer = 0;
	uint32_t current_extension = 0;

	tuple<Args&...> { args... }
		.get([&](vk::application_info& ai) {
			ici.application_info = &ai;
		})
		.get([&](vk::enabled_layer_name eln) {
			layers_names[current_layer++] = eln;
		})
		.get([&](vk::enabled_extension_name eln) {
			extensions_names[current_extension++] = eln;
		});

	ici.enabled_layer_names = layers_names;	
	ici.enabled_extension_names = extensions_names;

	VkInstance instance;

	vk::throw_if_error(
		vkCreateInstance(
			(VkInstanceCreateInfo*)&ici,
			nullptr,
			&instance
		)
	);

	return *((vk::instance*)instance);
} // create_instance

inline void destroy_instance(vk::instance& instance) {
	vkDestroyInstance(
		(VkInstance)&instance,
		nullptr
	);
}

} // vk