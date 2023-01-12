#pragma once

#include "../__internal/queue_family_index.hpp"

#include <enum_flags.hpp>
#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct queue_count { uint32 _; };
	struct queue_priority { float _; };
	struct queue_priorities { const queue_priority* _; };

	enum queue_create_flag {
		_protected
	};

	struct queue_create_info {
		uint32                        type = 2;
		const void*                   next = nullptr;
		enum_flags<queue_create_flag> flags{};
		vk::queue_family_index        queue_family_index;
		vk::queue_count               queue_count;
		vk::queue_priorities          queue_priorities;

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			count_of_decayed_same_as<vk::queue_family_index> == 1,
			count_of_decayed_same_as<vk::queue_count> == 1,
			count_of_decayed_same_as<vk::queue_priorities> == 1
		>
		queue_create_info(Args... args) :
			queue_family_index {
				tuple{ args... }.template
					get_decayed_same_as<vk::queue_family_index>()
			},
			queue_count {
				tuple{ args... }.template
					get_decayed_same_as<vk::queue_count>()
			},
			queue_priorities {
				tuple{ args... }.template
					get_decayed_same_as<vk::queue_priorities>()
			}
		{}

	}; // device_queue_create_info
	
} // vk