#pragma once

#include "../../../shader/stage.hpp"
#include "../../../descriptor/count.hpp"
#include "../../../descriptor/type.hpp"
#include "../../../descriptor/binding.hpp"

#include <core/flag_enum.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

namespace vk {

	struct descriptor_set_layout_binding {
		vk::descriptor_binding descriptor_binding;
		vk::descriptor_type descriptor_type;
		vk::descriptor_count descriptor_count{ 1 };
		vk::shader_stages stage_flags;
		const void* immutable_samplers = nullptr;

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<vk::descriptor_binding>,
			types::are_contain_one_decayed<vk::descriptor_type>,
			types::are_may_contain_one_decayed<vk::descriptor_count>,
			types::are_contain_one_decayed<vk::shader_stages>
		>::for_types<Args...>
		descriptor_set_layout_binding(Args&&... args) {
			descriptor_binding = elements::decayed<vk::descriptor_binding>(args...);
			descriptor_type = elements::decayed<vk::descriptor_type>(args...);
			stage_flags = elements::decayed<vk::shader_stages>(args...);
			
			if constexpr(
				types::are_contain_decayed<
					vk::descriptor_count
				>::for_types<Args...>
			) {
				descriptor_count = {
					elements::decayed<vk::descriptor_count>(args...)
				};
			}

		} // constructor

	}; // descriptor_set_layout_binding

} // vk