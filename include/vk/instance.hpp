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

struct physical_devices_view {
	VkInstance m_instance;

	struct iterator {
		VkInstance m_instance;
		uint32_t m_device = 0;

		vk::physical_device operator * () const {
			uint32_t l_count = m_device + 1;
			VkPhysicalDevice l_devices[l_count];

			vk::throw_if_error(
				vkEnumeratePhysicalDevices(
					m_instance,
					&l_count,
					l_devices
				)
			);

			return { l_devices[m_device] };
		}

		auto& operator ++ () {
			++m_device; return *this;
		}

		auto operator ++ (int) {
			iterator copy{ *this };
			++m_device;
			return copy;
		}

		auto operator <=> (const iterator&) const = default;
	}; // iterator

	iterator begin() const {
		return { m_instance, 0 };
	}

	uint32_t size() const {
		uint32_t l_count;
		vk::throw_if_error(
			vkEnumeratePhysicalDevices(
				m_instance,
				&l_count,
				nullptr
			)
		);
		return l_count;
	}

	iterator end() const {
		return { m_instance, size() };
	}

	vk::physical_device front() const {
		return *begin();
	}
}; // physical_devices_view

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

	physical_devices_view physical_devices() const {
		return { m_instance };
	}

}; // instance

} // vk

static_assert(sizeof(vk::instance_create_info) == sizeof(VkInstanceCreateInfo));