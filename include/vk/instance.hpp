#pragma once

#include "headers.hpp"
#include <cstdint>
#include <string>
#include <iostream>
#include <optional>
#include <compare>
#include <system_error>
#include <cxx_util/parameter_pack/for_each.hpp>
#include "result.hpp"
#include "application_info.hpp"
#include "physical_device.hpp"

namespace vk {

template<typename F>
void view_instance_physical_devices(VkInstance instance, F&& f);

class physical_devices_view {
	VkInstance m_instance;
	vk::physical_device* m_physical_devices;
	uint32_t m_count;

	physical_devices_view(
		VkInstance p_instance,
		vk::physical_device* p_physical_devices,
		uint32_t p_count
	)
		: m_instance{ p_instance }, m_physical_devices{ p_physical_devices }, m_count{ p_count }
	{}

	template<typename F>
	friend void vk::view_instance_physical_devices(VkInstance instance, F&& f);
public:

	auto begin() const {
		return m_physical_devices;
	}

	auto end() const {
		return m_physical_devices + m_count;
	}

	uint32_t size() const {
		return m_count;
	}

	vk::physical_device front() const {
		return *begin();
	}
}; // physical_devices_view

template<typename F>
void view_instance_physical_devices(VkInstance instance, F&& f) {
	uint32_t count;
	vk::throw_if_error(
		vkEnumeratePhysicalDevices(
			instance,
			&count,
			nullptr
		)
	);

	vk::physical_device devices[count];

	vk::throw_if_error(
		vkEnumeratePhysicalDevices(
			instance,
			&count,
			(VkPhysicalDevice*)devices
		)
	);

	physical_devices_view v{instance, devices, count};
	f(v);
}

struct instance_create_info {
	u::int_with_size<sizeof(VkStructureType)> m_type = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	const void* m_next;
	uint32_t m_flags;
	vk::application_info* m_application_info;
	uint32_t enabled_layer_count;
	const char* const* pp_enabled_layer_names;
	uint32_t enabled_extension_count;
	const char* const* enabled_extension_names;
};

struct instance {
	VkInstance m_instance;

	~instance() {
		vkDestroyInstance(m_instance, nullptr);
	}

	template<typename... Args>
	instance(Args&&... args) noexcept(false) {
		std::optional<vk::application_info> l_application_info;

		u::for_each(
			std::forward<Args>(args)...,
			u::do_one_of {
				[&](application_info&& i) {
					l_application_info.emplace(std::forward<decltype(i)>(i));
				},
				[&](auto) {}
			}
		);

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

static_assert(sizeof(vk::instance_create_info) == sizeof(VkInstanceCreateInfo));