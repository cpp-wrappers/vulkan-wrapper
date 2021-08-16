#pragma once

#include "headers.hpp"
#include <cxx_util/int.hpp>
#include <cxx_util/parameter_pack/parameter_pack.hpp>
#include "device_queue_create_info.hpp"
#include "physical_device_features.hpp"

namespace vk {

class device_create_info {
	u::int_with_size<sizeof(VkStructureType)> type = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	const void* m_next = nullptr;
	int m_flags = 0;
	uint32_t m_queue_create_info_count;
	const vk::device_queue_create_info* m_queue_create_infos;
	uint32_t m_enabled_layer_count;
	const char* const* m_enabled_layer_names;
	uint32_t m_enabled_extension_count;
	const char* const* m_enabled_extension_names;
	const vk::physical_device_features* m_enabled_features;

public:

	template<typename...Args>
	device_create_info(Args&&... args) {
		using PP = typename u::parameter_pack<Args...>;

		m_queue_create_info_count = PP::template count<device_queue_create_info>;

	}
}; // device_create_info

} // vk