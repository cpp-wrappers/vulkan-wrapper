#pragma once

#include "headers.hpp"
#include <cxx_util/parameter_pack/parameter_pack.hpp>
#include <cxx_util/tuple/for_each.hpp>
#include <cxx_util/bitmask_from_enum.hpp>
#include <vulkan/vulkan_core.h>
#include "physical_device.hpp"
#include "device_create_info.hpp"
#include "result.hpp"

namespace vk {

struct device {
	VkDevice m_device{};

	~device() {
		vkDestroyDevice(m_device, nullptr);
	}

	template<typename... Ps>
	device(const Ps&... params) noexcept(false) {
		vk::device_create_info ci{};

		u::params ps { params... };
		ci.m_queue_create_info_count = ps.template count<const vk::device_queue_create_info&>();

		vk::device_queue_create_info dqcis[ci.m_queue_create_info_count];
		int current = 0;

		vk::physical_device physical_device;

		ps
			.template handle<u::several<const vk::device_queue_create_info&>>([&](auto dqci) {
				dqcis[current++] = dqci;
			})
			.template handle<u::required<const vk::physical_device&>>([&](auto pd) {
				physical_device = pd;
			})
			.check_for_emptiness();

		ci.m_queue_create_infos = dqcis;

		vk::throw_if_error(
			(int) vkCreateDevice(
				physical_device.m_physical_device,
				(VkDeviceCreateInfo*)&ci,
				nullptr,
				&m_device
			)
		);
	}

};

}