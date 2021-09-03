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

class device_queue_create_info {
	int_with_size_of<VkStructureType> type = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	const void* next = nullptr;
	flag_enum<device_queue_create_flag> flags{};
	vk::queue_family_index queue_family_index;
	vk::queue_count queue_count;
	vk::queue_priorities queue_priorities;

public:

	device_queue_create_info(const device_queue_create_info&) = default;
	device_queue_create_info(device_queue_create_info&) = default;
	device_queue_create_info(device_queue_create_info&&) = default;
	device_queue_create_info& operator = (const device_queue_create_info&) = default;

	template<typename... Args>
	requires(
		types::of<Args...>::template count_of_same_as_type<vk::queue_family_index> == 1 &&
		types::of<Args...>::template count_of_same_as_type<vk::queue_count> == 1 &&
		types::of<Args...>::template count_of_same_as_type<vk::queue_priorities> == 1 &&
		types::of<Args...>::size == 3
	)
	device_queue_create_info(Args... args) {
		tuple{ args... }
			.get([&](vk::queue_family_index i) {
				queue_family_index = i;
			})
			.get([&](vk::queue_count c) {
				queue_count = c;
			})
			.get([&](vk::queue_priorities p) {
				queue_priorities = p;
			});
	}
}; // device_queue_create_info
	
} // vk

static_assert(sizeof(vk::device_queue_create_info) == sizeof(VkDeviceQueueCreateInfo));