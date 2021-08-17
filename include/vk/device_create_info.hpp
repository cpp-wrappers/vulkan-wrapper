#pragma once

#include "cxx_util/parameter_pack/for_each.hpp"
#include "headers.hpp"
#include <cxx_util/int.hpp>
#include <cxx_util/parameter_pack/parameter_pack.hpp>
#include "device_queue_create_info.hpp"
#include "physical_device_features.hpp"
#include "vk/physical_device.hpp"
#include <cassert>

namespace vk {

template<std::size_t Count>
struct device_queue_create_infos : std::array<vk::device_queue_create_info, Count> {
};

template<typename...Qs>
device_queue_create_infos(Qs&&...) -> device_queue_create_infos<sizeof...(Qs)>;

class device_create_info {
	u::int_with_size<sizeof(VkStructureType)> type = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	const void* m_next = nullptr;
	int m_flags = 0;
	uint32_t m_queue_create_info_count;
	const vk::device_queue_create_info* m_queue_create_infos;
	uint32_t m_enabled_layer_count = 0;
	const char* const* m_enabled_layer_names = nullptr;
	uint32_t m_enabled_extension_count = 0;
	const char* const* m_enabled_extension_names = 0;
	const vk::physical_device_features* m_enabled_features = 0;

public:

	template<typename... Args>
	device_create_info(const Args&... args) {
		//using PP = typename u::parameter_pack<Args...>;

		u::for_each(
			args...,
			u::do_one_of {
				[&]<std::size_t Count>(const vk::device_queue_create_infos<Count>& v) {
					m_queue_create_info_count = Count;
					m_queue_create_infos = v.data();
				},
				//[&](vk::physical_device){},
				[&](auto){
					//assert(false);
				}
			}
		);

	}
}; // device_create_info

} // vk