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
	device(Ps&&... params) noexcept(false) {
		vk::device_create_info ci{};

		u::params ps { std::tie(params...) };

		auto[ dqcis, ps0 ] = ps.template take_as_array_of<vk::device_queue_create_info&, u::several>();
		ci.set_device_queue_create_infos(dqcis);
		
		vk::physical_device physical_device;

		ps0
			.template handle<u::required>([&](vk::physical_device pd) {
				physical_device = pd;
			})
			.check_for_emptiness();

		vk::throw_if_error(
			vkCreateDevice(
				physical_device.m_physical_device,
				(VkDeviceCreateInfo*)&ci,
				nullptr,
				&m_device
			)
		);
	}

};

}