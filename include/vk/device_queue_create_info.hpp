#pragma once

#include "headers.hpp"
#include "queue_family_index.hpp"
#include <cinttypes>
#include <cstdint>
#include <core/flag_enum.hpp>
#include <array>
#include <core/tuple.hpp>
#include <type_traits>

namespace vk {

enum device_queue_create_flag {
	рrotected
};

struct queue_count : named<uint32_t> {};
struct queue_priorities : named<const float*> {};

class physical_device;
class device;

class device_queue_create_info {
	int_with_size_of<VkStructureType> m_type = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	const void* m_next = nullptr;
	flag_enum<device_queue_create_flag> m_flags{};
	uint32_t m_queue_family_index;
	uint32_t m_queue_count;
	const float* m_queue_priorities;

	device_queue_create_info() = default;
	friend physical_device;

	template<typename... Args>
	friend vk::device& create_device(Args&&...);
public:

	device_queue_create_info(const device_queue_create_info&) = default;
	device_queue_create_info(device_queue_create_info&) = default;
	device_queue_create_info(device_queue_create_info&&) = default;
	device_queue_create_info& operator = (const device_queue_create_info&) = default;

	template<typename... Args>
	requires(
		types::of<Args...>::template count_of_type<vk::queue_family_index> == 1 &&
		types::of<Args...>::template count_of_type<vk::queue_count> == 1 &&
		types::of<Args...>::template count_of_type<vk::queue_priorities> == 1 &&
		types::of<Args...>::size == 3
	)
	device_queue_create_info(Args&&... args) {
		tuple<Args&...>{ args... }
			.get([&](vk::queue_family_index i) {
				m_queue_family_index = i.value;
			})
			.get([&](vk::queue_count c) {
				m_queue_count = c.value;
			})
			.get([&](vk::queue_priorities p) {
				m_queue_priorities = p.value;
			});
	}
}; // device_queue_create_info
	
} // vk

static_assert(sizeof(vk::device_queue_create_info) == sizeof(VkDeviceQueueCreateInfo));