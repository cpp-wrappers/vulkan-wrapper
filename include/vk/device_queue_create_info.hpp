#pragma once

#include "cxx_util/parameter_pack/parameter_pack.hpp"
#include "headers.hpp"
#include <cinttypes>
#include <cxx_util/bitmask_from_enum.hpp>
#include <cxx_util/tuple/for_each.hpp>
#include <cxx_util/int_with_size.hpp>
#include <cxx_util/params.hpp>
#include <cxx_util/named.hpp>

namespace vk {

enum device_queue_create_flag {
	рrotected
};

struct queue_family_index : u::named<uint32_t>{};
struct queue_count : u::named<uint32_t>{};
struct queue_priorities : u::named<const void*>{};

struct device_queue_create_info {
	const u::int_with_size_of<VkStructureType> m_type = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	const void* m_next = nullptr;
	u::bitmask_from_enum<device_queue_create_flag> m_flags;
	uint32_t m_queue_family_index;
	uint32_t m_queue_count;
	const float* m_queue_priorities;

	template<typename... Ps>
	device_queue_create_info(const Ps&... ps) {
		device_queue_create_info ci{};

		u::params{ ps... }
			.template handle<u::required_single<queue_family_index>>([&](auto i) {
				ci.m_queue_family_index = i.value;
			})
			.template handle<u::required_single<queue_count>>([&](auto c) {
				ci.m_queue_count = c.value;
			})
			.template handle<u::required_single<queue_priorities>>([&](auto p) {
				ci.m_queue_priorities = p.value;
			})
			.check_for_emptiness();
	}
}; // device_queue_create_info
	
} // vk

static_assert(sizeof(vk::device_queue_create_info) == sizeof(VkDeviceQueueCreateInfo));