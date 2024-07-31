#pragma once

#include "../__shader_module/stage.hpp"
#include "../__internal/size.hpp"
#include "../__internal/offset.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct push_constant_range {
		vk::shader_stages stages{};
		vk::offset<1> offset{};
		vk::size size;

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			is_same_as<vk::offset<1>> <= 1,
			is_same_as<vk::size> == 1,
			(
				is_same_as<vk::shader_stages> == 1 ||
				is_same_as<vk::shader_stage> > 0
			)
		>
		push_constant_range(Args... args) {
			tuple<Args...> a{args...};

			size = a.template get<is_same_as<vk::size>>();

			if constexpr(
				(is_same_as<vk::shader_stages> > 0).for_types<Args...>()
			) {
				stages = a.template get<is_same_as<vk::shader_stages>>();
			}
			
			if constexpr(
				(is_same_as<vk::shader_stage> > 0).for_types<Args...>()
			) {
				a.template pass<is_same_as<vk::shader_stage>>(
					[&](auto... stage) { (stages.set(stage), ...); }
				);
			}

			if constexpr(
				(is_same_as<vk::offset<1>> > 0).for_types<Args...>()
			) {
				offset = a.template get<is_same_as<vk::offset<1>>>();
			}
		}
	};

} // vk