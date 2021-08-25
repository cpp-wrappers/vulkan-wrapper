#pragma once

#include "headers.hpp"
#include "queue_family_index.hpp"
#include <cxx_util/params.hpp>
#include <vulkan/vulkan_core.h>
#include "device.hpp"
#include "command_buffer.hpp"
#include "result.hpp"
#include "command_buffer_level.hpp"
#include "command_buffer.hpp"

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
	command_pool(Ps&&... params) noexcept(false) {
		VkCommandPoolCreateInfo ci {
			VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
			nullptr,
			0,
			0
		};

		u::params{ std::tie(params...) }
			.template handle<u::required>([&](vk::device& d) {
				m_device = d.m_device;
			})
			.template handle<u::required>([&](vk::queue_family_index i) {
				ci.queueFamilyIndex = i.value;
			})
			.template handle<u::any>([&](command_pool_create_flag f) {
				ci.flags |= (uint32_t)f;
			})
			.check_for_emptiness();

		vk::throw_if_error(
			vkCreateCommandPool(
				m_device,
				&ci,
				nullptr,
				&m_command_pool
			)
		);
	}

	template<std::size_t Count>
	auto allocate_command_buffers(vk::command_buffer_level l) const {
		std::array<vk::command_buffer, Count> bufs;

		VkCommandBufferAllocateInfo cbai {
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
			.pNext = nullptr,
			.commandPool = m_command_pool,
			.level = (VkCommandBufferLevel) l,
			.commandBufferCount = Count
		};

		vk::throw_if_error(
			vkAllocateCommandBuffers(
				m_device,
				&cbai,
				(VkCommandBuffer*)bufs.data()
			)
		);

		return bufs;
	}

	auto allocate_command_buffer(vk::command_buffer_level l) const {
		return allocate_command_buffers<1>(l)[0];
	}

}; // command_pool

} // vk