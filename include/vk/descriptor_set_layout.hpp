#pragma once

#include "cxx_util/bitmask_from_enum.hpp"
#include "cxx_util/params.hpp"
#include "descriptor_set_layout_binding.hpp"
#include "vk/result.hpp"
#include <cstdint>
#include "device.hpp"

namespace vk {

enum class descriptor_set_layout_create_flag {
	update_after_bind_pool = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT,
	push_descriptor = VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR,
	host_only_pool = VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_VALVE
};

struct descriptor_set_layout {
	VkDescriptorSetLayout m_descriptor_set_layout;

	template<typename... Ps>
	descriptor_set_layout(Ps&&... params) {
		VkDescriptorSetLayoutCreateInfo ci {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0
		};

		VkDevice device;

		u::params<Ps&...> ps{ params... };
		ci.bindingCount = ps.template count<vk::descriptor_set_layout_binding&>;

		vk::descriptor_set_layout_binding bindings[ci.bindingCount];
		uint32_t current_binding = 0;

		ps
			.template handle<u::required>([&](vk::device& d){ device = d.m_device; })
			.template handle<u::any>([&](vk::descriptor_set_layout_create_flag f){ ci.flags |= (uint32_t)f; })
			.template handle<u::several>([&](vk::descriptor_set_layout_binding b){ bindings[current_binding++] = b; })
			.check_for_emptiness();

		vk::throw_if_error(
			vkCreateDescriptorSetLayout(
				device,
				&ci,
				nullptr,
				&m_descriptor_set_layout
			)
		);
	}
}; // descriptor_set_layout

} // vk