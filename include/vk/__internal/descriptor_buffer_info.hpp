#pragma once

#include "./memory_offset.hpp"
#include "./memory_size.hpp"
#include "../__buffer/handle.hpp"

#include <type.hpp>
#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct descriptor_buffer_info {
		handle<vk::buffer>::underlying_type buffer;
		vk::memory_offset offset{};
		vk::memory_size size;

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			is_convertible_to<handle<vk::buffer>> == 1,
			is_same_as<vk::memory_size>.decayed == 1,
			is_same_as<vk::memory_offset>.decayed <= 1
		>
		descriptor_buffer_info(Args&&... args) {
			tuple a { args... };

			buffer = ((handle<vk::buffer>) a.template
				get<is_convertible_to<handle<vk::buffer>>>()
			).underlying();

			size = a.template get<is_same_as<vk::memory_size>.decayed>();

			if constexpr (
				(is_same_as<vk::memory_offset> > 0).for_types<Args...>()
			) {
				offset = a.template
					get<is_same_as<vk::memory_offset>.decayed>();
			}
		}
	};

} // vk