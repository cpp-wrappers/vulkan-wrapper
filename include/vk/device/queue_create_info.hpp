#pragma once

#include "../queue_family_index.hpp"

#include <core/flag_enum.hpp>
#include <core/wrapper/of_pointer_to.hpp>
#include <core/wrapper/of_integer.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

namespace vk {

	struct queue_count : wrapper::of_integer<uint32> {};
	struct queue_priority : wrapper::of<float> {};
	struct queue_priorities : wrapper::of_pointer_to<const queue_priority> {};

	enum queue_create_flag {
		_protected
	};

	struct queue_create_info {
		uint32 type = 2;
		const void* next = nullptr;
		flag_enum<queue_create_flag> flags{};
		vk::queue_family_index queue_family_index;
		vk::queue_count queue_count;
		vk::queue_priorities queue_priorities;

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<vk::queue_family_index>,
			types::are_contain_one_decayed<vk::queue_count>,
			types::are_contain_one_decayed<vk::queue_priorities>
		>::for_types<Args...>
		queue_create_info(Args... args) {
			queue_family_index = elements::decayed<vk::queue_family_index>(args...);
			queue_count = elements::decayed<vk::queue_count>(args...);
			queue_priorities = elements::decayed<vk::queue_priorities>(args...);
		}

	}; // device_queue_create_info
	
} // vk