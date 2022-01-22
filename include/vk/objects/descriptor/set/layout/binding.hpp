#pragma once

#include "../../count.hpp"
#include "../../type.hpp"
#include "../../binding.hpp"
#include "../../../shader/stage.hpp"
#include "../../../../shared/headers.hpp"

#include <core/flag_enum.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/meta/types/are_contain_decayed_same_as.hpp>
#include <core/meta/elements/decayed_same_as.hpp>
#include <core/meta/elements/for_each_decayed_same_as.hpp>

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
				types::are_contain_one_decayed_same_as<vk::descriptor_binding>,
				types::are_contain_one_decayed_same_as<vk::descriptor_type>,
				types::are_contain_one_decayed_same_as<vk::descriptor_count>,
				types::are_contain_one_decayed_same_as<vk::shader_stages>
			>::for_types<Args...>
		)
		descriptor_set_layout_binding(Args... args) {
			descriptor_binding = elements::decayed_same_as<vk::descriptor_binding>(args...);
			descriptor_type = elements::decayed_same_as<vk::descriptor_type>(args...);
			descriptor_count = elements::decayed_same_as<vk::descriptor_count>(args...);
			stage_flags = elements::decayed_same_as<vk::shader_stages>(args...);
		}

	};

} // vk

static_assert(sizeof(vk::descriptor_set_layout_binding) == sizeof(VkDescriptorSetLayoutBinding));