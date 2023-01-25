#pragma once

#include "./memory_offset.hpp"
#include "./memory_size.hpp"
#include "../__buffer/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct descriptor_buffer_info {
		handle<vk::buffer>::underlying_type buffer;
		vk::memory_offset offset{};
		vk::memory_size size;

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			count_of_decayed_same_as<handle<vk::buffer>> == 1,
			count_of_decayed_same_as<vk::memory_size> == 1,
			count_of_decayed_same_as<vk::memory_offset> <= 1
		>
		descriptor_buffer_info(Args&&... args) {
			tuple a { args... };
			buffer = a.template get_decayed_same_as<handle<vk::buffer>>();

			buffer = a.template get_decayed_same_as<vk::memory_size>();

			if constexpr (types<Args...>::template
				count_of_decayed_same_as<vk::memory_offset> > 0
			) {
				offset = a.template get_decayed_same_as<vk::memory_offset>();
			}
		}
	};

} // vk