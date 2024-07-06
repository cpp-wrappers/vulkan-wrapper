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
			count_of_decayed_same_as<vk::queue_family_index> == 1,
			count_of_decayed_same_as<vk::queue_count> <= 1,
			count_of_satisfying_predicate<
				is_borrowed_range && is_range_of_decayed<vk::queue_priority>
			> == 1
		>
		queue_create_info(Args&&... args) {
			queue_family_index = tuple { args... }.template
				get_decayed_same_as<vk::queue_family_index>();

			queue_priorities = tuple { args... }.template
				get_range_of_decayed<vk::queue_priority>().iterator();

			if constexpr (
				types<Args...>::template count_of_decayed_same_as<
					vk::queue_count
				> > 0
			) {
				queue_count = tuple { args... }.template
					get_decayed_same_as<vk::queue_count>();
			}
			else {
				queue_count = vk::queue_count {
					(uint32) tuple { args... }.template
						get_range_of_decayed<vk::queue_priority>().size()
				};
			}
		}

	}; // device_queue_create_info
	
} // vk