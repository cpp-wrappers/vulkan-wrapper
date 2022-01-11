#pragma once

#include <core/flag_enum.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/for_each_of_type.hpp>

#include "../../../../shared/headers.hpp"
#include "../../../shader/stage.hpp"
#include "../../count.hpp"
#include "../../type.hpp"
#include "../../binding.hpp"

namespace vk {

	struct descriptor_set_layout_binding {
		vk::descriptor_binding descriptor_binding;
		vk::descriptor_type descriptor_type;
		vk::descriptor_count descriptor_count;
		vk::shader_stages stage_flags;
		const void* immutable_samplers{};

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::count_of_type<vk::descriptor_binding>::equals<1>,
				types::count_of_type<vk::descriptor_type>::equals<1>,
				types::count_of_type<vk::descriptor_count>::equals<1>,
				types::count_of_type<vk::shader_stages>::equals<1>
			>::for_types_of<Args...>
		)
		descriptor_set_layout_binding(Args... args) {
			descriptor_binding = elements::of_type<vk::descriptor_binding&>::for_elements_of(args...);
			descriptor_type = elements::of_type<vk::descriptor_type&>::for_elements_of(args...);
			descriptor_count = elements::of_type<vk::descriptor_count&>::for_elements_of(args...);
			stage_flags = elements::of_type<vk::shader_stages&>::for_elements_of(args...);
		}
	}; // descriptor_set_layout_binding

} // vk

static_assert(sizeof(vk::descriptor_set_layout_binding) == sizeof(VkDescriptorSetLayoutBinding));