#pragma once

#include "cxx_util/parameter_pack/parameter_pack.hpp"
#include "headers.hpp"
#include "queue_family_index.hpp"
#include <cinttypes>
#include <cstdint>
#include <cxx_util/bitmask_from_enum.hpp>
#include <cxx_util/tuple/for_each.hpp>
#include <cxx_util/int_with_size.hpp>
#include <cxx_util/params.hpp>
#include <cxx_util/named.hpp>

namespace vk {

enum device_queue_create_flag {
	рrotected
};

//struct queue_count : u::named<uint32_t>{};

enum class queue_count : uint32_t {
	undefined = 0
};

template<queue_count Count>
struct queue_priorities : std::array<float, (std::size_t)Count> {};

template<typename...Ts>
requires(std::is_same_v<Ts, float> && ...)
queue_priorities(Ts&&...) -> queue_priorities<(queue_count)sizeof...(Ts)>;

template<>
struct queue_priorities<queue_count::undefined> : u::named<const float*>{};

struct device_queue_create_info {
	u::int_with_size_of<VkStructureType> m_type = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	const void* m_next = nullptr;
	u::bitmask_from_enum<device_queue_create_flag> m_flags{};
	uint32_t m_queue_family_index;
	uint32_t m_queue_count;
	const float* m_queue_priorities;

	device_queue_create_info() = default;
	device_queue_create_info(const device_queue_create_info&) = default;
	device_queue_create_info(device_queue_create_info&) = default;
	device_queue_create_info(device_queue_create_info&&) = default;
	device_queue_create_info& operator = (const device_queue_create_info&) = default;

	template<typename... Ps>
	device_queue_create_info(Ps&&... params) {
		u::params ps{ std::tie(params...) };
		auto ps0 = ps.template handle<u::required>([&](queue_family_index i) {
			m_queue_family_index = i.value;
		});

		if constexpr(ps.template contains<queue_priorities<queue_count::undefined>&>) {
			ps0.template handle<u::required>([&](queue_count c) {
				m_queue_count = (uint32_t)c;
			})
			.template handle<u::required>([&](queue_priorities<queue_count::undefined> p) {
				m_queue_priorities = p.value;
			})
			.check_for_emptiness();
		}
		else {
			ps0.template handle<u::required>([&]<queue_count C>(queue_priorities<C>& p) {
				m_queue_count = (uint32_t)C;
				m_queue_priorities = p.data();
			})
			.check_for_emptiness();
		}
	}
}; // device_queue_create_info
	
} // vk

static_assert(sizeof(vk::device_queue_create_info) == sizeof(VkDeviceQueueCreateInfo));