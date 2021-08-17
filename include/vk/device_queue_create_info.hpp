#pragma once

#include "cxx_util/parameter_pack/parameter_pack.hpp"
#include "headers.hpp"
#include <cinttypes>
#include <cxx_util/bitmask_from_enum.hpp>
#include <cxx_util/parameter_pack/for_each.hpp>
#include <cxx_util/int.hpp>

namespace vk {

enum device_queue_create_flag { рrotected };

template<std::size_t Count>
struct choosen_queue_family {
	uint32_t index;
	std::array<float, Count> priorities;
};

template<std::size_t Count>
choosen_queue_family(std::size_t, std::array<float, Count>) -> choosen_queue_family<Count>;

class device_queue_create_info {
	const u::int_with_size<sizeof(VkStructureType)> m_type = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	const void* m_next = nullptr;
	u::bitmask_from_enum<device_queue_create_flag> m_flags;
	uint32_t m_queue_family_index;
	uint32_t m_queue_count;
	const float* m_queue_priorities;
public:

	template<typename... Args>
	device_queue_create_info(const Args&... args) {
		u::for_each(
			args...,
			u::do_one_of{
				[&](device_queue_create_flag f) { m_flags.set(f); },
				[&]<std::size_t Count>(const choosen_queue_family<Count>& v) {
					m_queue_family_index = v.index;
					m_queue_count = Count;
					m_queue_priorities = v.priorities.data();
				}
			}
		);
	}
}; // device_queue_create_info

} // vk

static_assert(sizeof(vk::device_queue_create_info) == sizeof(VkDeviceQueueCreateInfo));