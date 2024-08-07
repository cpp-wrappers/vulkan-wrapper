#pragma once

#include "../__shader_module/stage.hpp"
#include "../__internal/descriptor_count.hpp"
#include "../__internal/descriptor_type.hpp"
#include "../__internal/descriptor_binding.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct descriptor_set_layout_binding {
		vk::descriptor_binding descriptor_binding;
		vk::descriptor_type descriptor_type;
		vk::descriptor_count descriptor_count{ 1 };
		vk::shader_stages stage_flags{};
		const void* immutable_samplers = nullptr;

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			is_same_as<vk::descriptor_binding>.decayed == 1,
			is_same_as<vk::descriptor_type>.decayed == 1,
			is_same_as<vk::descriptor_count>.decayed <= 1,
			(
				is_same_as<vk::shader_stages>.decayed == 1 ||
				is_same_as<vk::shader_stage>.decayed >= 1
			)
		>
		descriptor_set_layout_binding(Args&&... args) {
			tuple a{ args... };

			descriptor_binding = a.template
				get<is_same_as<vk::descriptor_binding>.decayed>();
			descriptor_type = a.template
				get<is_same_as<vk::descriptor_type>.decayed>();
			
			if constexpr(
				(is_same_as<vk::descriptor_count> > 0).for_types<Args...>()
			) {
				descriptor_count = a.template
					get<is_same_as<vk::descriptor_count>.decayed>();
			}

			if constexpr(
				(is_same_as<vk::shader_stages>.decayed > 0)
				.for_types<Args...>()
			) {
				stage_flags = a.template
					get<is_same_as<vk::shader_stages>.decayed>();
			}

			if constexpr(
				(is_same_as<vk::shader_stage>.decayed > 0).for_types<Args...>()
			) {
				a.template pass<is_same_as<vk::shader_stage>.decayed>(
					[&](auto... stage) {
						(stage_flags.set(stage), ...);
					}
				);
			}

		} // constructor

	}; // descriptor_set_layout_binding

} // vk