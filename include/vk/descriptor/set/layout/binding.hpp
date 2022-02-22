#pragma once

#include <core/flag_enum.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

#include "vk/headers.hpp"
#include "vk/shader/stage.hpp"
#include "vk/descriptor/count.hpp"
#include "vk/descriptor/type.hpp"
#include "vk/descriptor/binding.hpp"

namespace vk {

	struct descriptor_set_layout_binding {
		vk::descriptor_binding descriptor_binding;
		vk::descriptor_type descriptor_type;
		vk::descriptor_count descriptor_count{ 1 };
		vk::shader_stages stage_flags;
		const void* immutable_samplers{ nullptr };

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::are_contain_one_decayed_same_as<vk::descriptor_binding>,
			types::are_contain_one_decayed_same_as<vk::descriptor_type>,
			types::are_may_contain_one_decayed_same_as<vk::descriptor_count>,
			types::are_contain_one_decayed_same_as<vk::shader_stages>
		>::for_types<Args...>
		descriptor_set_layout_binding(Args&&... args) {
			descriptor_binding = elements::decayed_same_as<vk::descriptor_binding>(args...);
			descriptor_type = elements::decayed_same_as<vk::descriptor_type>(args...);
			stage_flags = elements::decayed_same_as<vk::shader_stages>(args...);
			
			if constexpr(types::are_contain_decayed_same_as<vk::descriptor_count>::for_types<Args...>) {
				descriptor_count = elements::decayed_same_as<vk::descriptor_count>(args...);
			}
		}

	};

} // vk

static_assert(sizeof(vk::descriptor_set_layout_binding) == sizeof(VkDescriptorSetLayoutBinding));