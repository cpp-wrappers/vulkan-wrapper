#pragma once

#include "headers.hpp"
#include "queue_family_index.hpp"
#include <cxx_util/params.hpp>
#include <vulkan/vulkan_core.h>
#include "device.hpp"
#include "result.hpp"

enum class command_pool_create_flag {
	transient = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT,
	reset_command_buffer = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
	рrotected = VK_COMMAND_POOL_CREATE_PROTECTED_BIT
};

namespace vk {

struct command_pool {
	VkDevice m_device;
	VkCommandPool m_command_pool{nullptr};

	~command_pool() {
		vkDestroyCommandPool(m_device, m_command_pool, nullptr);
	}

	template<typename... Ps>
	command_pool(const Ps&... params) noexcept(false) {
		VkCommandPoolCreateInfo ci {
			VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
			nullptr,
			0,
			0
		};

		u::params<const Ps&...>{ params... }
			.template handle<u::required<const vk::device&>>([&](auto& d) {
				m_device = d.m_device;
			})
			.template handle<u::required<const vk::queue_family_index&>>([&](auto i) {
				ci.queueFamilyIndex = i.value;
			})
			.template handle<u::any<const command_pool_create_flag&>>([&](auto f) {
				ci.flags |= (uint32_t)f;
			})
			.check_for_emptiness();

		vk::throw_if_error(
			(int)vkCreateCommandPool(
				m_device,
				&ci,
				nullptr,
				&m_command_pool
			)
		);
	}
};

}