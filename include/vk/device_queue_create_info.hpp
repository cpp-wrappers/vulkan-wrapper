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

//struct queue_count : u::named<uint32_t>{};

enum class queue_count : uint32_t {
	undefined = 0
};

template<queue_count Count>
struct queue_priorities : std::array<float, (std::size_t)Count> {};

template<typename...Ts>
requires(std::is_same_v<Ts, float> && ...)
queue_priorities(Ts&&...) -> queue_priorities<(queue_count)sizeof...(Ts)>;

queue_priorities(const float* ptr) -> queue_priorities<queue_count::undefined>;

template<>
struct queue_priorities<queue_count::undefined> : named<const float*>{};

namespace internal {
	template<typename T>
	struct is_queue_priorities_with_defined_size : std::false_type {};

	template<queue_count Count>
	requires(Count != queue_count::undefined)
	struct is_queue_priorities_with_defined_size<queue_priorities<Count>> : std::true_type {};
}

class physical_device;

struct device_queue_create_info {
	int_with_size_of<VkStructureType> m_type = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	const void* m_next = nullptr;
	flag_enum<device_queue_create_flag> m_flags{};
	uint32_t m_queue_family_index;
	uint32_t m_queue_count;
	const float* m_queue_priorities;

	device_queue_create_info(const device_queue_create_info&) = default;
	device_queue_create_info(device_queue_create_info&) = default;
	device_queue_create_info(device_queue_create_info&&) = default;
	device_queue_create_info& operator = (const device_queue_create_info&) = default;

	friend physical_device;
private:
	device_queue_create_info() = default;
public:

	template<typename... Args>
	requires(
		types::of<Args...>::template count_of_type<vk::queue_family_index> == 1 &&
		types::of<Args...>::template count_of_type<vk::queue_count> == 1 &&
		types::of<Args...>::template count_of_type<vk::queue_priorities<vk::queue_count::undefined>> == 1 &&
		types::of<Args...>::size == 3
	)
	device_queue_create_info(Args&&... args) {
		tuple<Args&...>{ args... }
			.get([&](vk::queue_family_index i) {
				m_queue_family_index = i.value;
			})
			.get([&](vk::queue_count c) {
				m_queue_count = (uint32_t)c;
			})
			.get([&](vk::queue_priorities<queue_count::undefined> p) {
				m_queue_priorities = p.value;
			});
	}

	template<typename... Args>
	requires(
		types::of<Args...>::template count_of_type<vk::queue_family_index> == 1 &&
		types::of<Args...>::template indices_of_types_that_satisfy<
			internal::is_queue_priorities_with_defined_size
		>::size == 1 &&
		types::of<Args...>::size == 2
	)
	device_queue_create_info(Args&&... args) {
		tuple<Args&...>{ args... }
			.get([&](vk::queue_family_index i) {
				m_queue_family_index = i.value;
			})
			.get([&]<vk::queue_count Count>(vk::queue_priorities<Count> c) {
				m_queue_count = (uint32_t)Count;
				m_queue_priorities = c.data();
			});
	}
}; // device_queue_create_info
	
} // vk

static_assert(sizeof(vk::device_queue_create_info) == sizeof(VkDeviceQueueCreateInfo));