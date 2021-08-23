#pragma once

#include "headers.hpp"
#include <cxx_util/parameter_pack/parameter_pack.hpp>
#include <cxx_util/tuple/for_each.hpp>
#include <cxx_util/bitmask_from_enum.hpp>
#include "physical_device.hpp"
#include "device_create_info.hpp"

namespace vk {

struct device {
	VkDevice m_device;

	template<typename... Args>
	device(const Args&... args) {
		vk::device_create_info create_info{ args... };
		vk::physical_device physical_device;

		u::for_each(
			args...,
			u::do_one_of {
				[&](vk::physical_device v) { physical_device = v; },
				[&](auto) { /* TODO */ }
			}
		);

		vk::throw_if_error(
			(int) vkCreateDevice(
				physical_device.m_physical_device,
				(VkDeviceCreateInfo*)&create_info,
				nullptr,
				&m_device
			)
		);
	}

};

}