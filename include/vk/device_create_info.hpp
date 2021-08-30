#pragma once

#include "cxx_util/tuple/for_each.hpp"
#include "headers.hpp"
#include <cxx_util/int_with_size.hpp>
#include <cxx_util/parameter_pack/parameter_pack.hpp>
#include "device_queue_create_info.hpp"
#include "physical_device_features.hpp"
#include "vk/physical_device.hpp"
#include <cassert>

namespace vk {

struct device_create_info {
	u::int_with_size_of<VkStructureType> type = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	const void* m_next = nullptr;
	int m_flags = 0;
	uint32_t m_queue_create_info_count = 0;
	const vk::device_queue_create_info* m_queue_create_infos = nullptr;
	uint32_t m_enabled_layer_count = 0;
	const char* const* m_enabled_layer_names = nullptr;
	uint32_t m_enabled_extension_count = 0;
	const char* const* m_enabled_extension_names = nullptr;
	const vk::physical_device_features* m_enabled_features = nullptr;

	template<std::size_t Count>
	void set_device_queue_create_infos(vk::device_queue_create_info (&infos) [Count]) {
		m_queue_create_infos = infos;
		m_queue_create_info_count = Count;
	}
}; // device_create_info

} // vk

static_assert(sizeof(vk::device_create_info) == sizeof(VkDeviceCreateInfo));