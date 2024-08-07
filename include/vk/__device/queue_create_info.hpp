#pragma once

#include "../__internal/queue_family_index.hpp"

#include <enum_flags.hpp>
#include <types.hpp>
#include <tuple.hpp>
#include <range.hpp>

namespace vk {

	struct queue_count { uint32 _; };
	class queue_priority {
		[[maybe_unused]] float value_;
	public:
		queue_priority(float value) : value_ { value } {}
	};

	enum queue_create_flag {
		_protected
	};

	struct queue_create_info {
		uint32                        type = 2;
		const void*                   next = nullptr;
		enum_flags<queue_create_flag> flags{};
		vk::queue_family_index        queue_family_index;
		vk::queue_count               queue_count;
		const vk::queue_priority*     queue_priorities;

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			is_same_as<vk::queue_family_index>.decayed == 1,
			is_same_as<vk::queue_count>.decayed <= 1,
			(
				is_borrowed_range &&
				is_range_of<is_same_as<vk::queue_priority>.decayed>
			)  == 1
		>
		queue_create_info(Args&&... args) {
			queue_family_index = tuple { args... }.template
				get<is_same_as<vk::queue_family_index>.decayed>();

			auto& queues = tuple { args... }.template
				get<is_range_of<is_same_as<vk::queue_priority>.decayed>>();

			queue_priorities = queues.iterator();

			if constexpr (
				(is_same_as<vk::queue_count>.decayed > 0).for_types<Args...>()
			) {
				queue_count = tuple { args... }.template
					get<is_same_as<vk::queue_count>.decayed>();
			}
			else {
				queue_count = vk::queue_count {
					(uint32) queues.size()
				};
			}
		}

	}; // device_queue_create_info
	
} // vk