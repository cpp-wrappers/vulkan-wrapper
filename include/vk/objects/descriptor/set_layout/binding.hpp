#pragma once

#include <core/wrapper/of_integer.hpp>
#include <core/flag_enum.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/for_each_of_type.hpp>

#include "../../../shared/headers.hpp"
#include "../../shader/stage.hpp"
#include "../count.hpp"
#include "../type.hpp"

namespace vk {

	struct descriptor_binding : wrapper::of_integer<uint32> {};

	struct descriptor_set_layout_binding {
		vk::descriptor_binding descriptor_binding;
		vk::descriptor_type descriptor_type;
		vk::shader_stages stage_flags;
		const void* immutable_samplers{};

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::count_of_type<vk::descriptor_binding>::equals<1>,
				types::count_of_type<vk::descriptor_type>::equals<1>,
				types::count_of_type<vk::shader_stage>::greater_or_equals<1>
			>::for_types_of<Args...>
		)
		descriptor_set_layout_binding(Args... args) {
			descriptor_binding = elements::of_type<vk::descriptor_binding&>::for_elements_of(args...);
			descriptor_type = elements::of_type<vk::descriptor_type&>::for_elements_of(args...);
			elements::for_each_of_type<vk::shader_stage&>(
				[&](auto s) { stage_flags.set(s); },
				args...
			);
		}
	}; // descriptor_set_layout_binding

} // vk

static_assert(sizeof(vk::descriptor_set_layout_binding) == sizeof(VkDescriptorSetLayoutBinding));