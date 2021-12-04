#pragma once

#include <core/integer.hpp>
#include <core/flag_enum.hpp>
#include <core/wrapper/of_pointer_to.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/of_type.hpp>

#include "../shared/headers.hpp"
#include "../shared/queue_family_index.hpp"
#include "core/wrapper/of_integer.hpp"

namespace vk {
	struct queue_count : wrapper::of_integer<uint32> {};
	struct queue_priority : wrapper::of<float> {};
	struct queue_priorities : wrapper::of_pointer_to<const queue_priority> {};

	enum queue_create_flag {
		рrotected
	};

	class queue_create_info {
		const uint32 type = (uint32) VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		const void* next = nullptr;
		flag_enum<queue_create_flag> flags;
		vk::queue_family_index queue_family_index;
		vk::queue_count queue_count;
		vk::queue_priorities queue_priorities;

	public:

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::count_of_type<vk::queue_family_index>::equals<1>,
				types::count_of_type<vk::queue_count>::equals<1>,
				types::count_of_type<vk::queue_priorities>::equals<1>
			>::for_types_of<Args...>
		)
		queue_create_info(Args... args) {
			queue_family_index = elements::of_type<vk::queue_family_index&>::for_elements_of(args...);
			queue_count = elements::of_type<vk::queue_count&>::for_elements_of(args...);
			queue_priorities = elements::of_type<vk::queue_priorities&>::for_elements_of(args...);
		}
	}; // device_queue_create_info
	
} // vk

static_assert(sizeof(vk::queue_create_info) == sizeof(VkDeviceQueueCreateInfo));