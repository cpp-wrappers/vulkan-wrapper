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
		vk::shader_stages stage_flags;
		const void* immutable_samplers = nullptr;

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			count_of_decayed_same_as<vk::descriptor_binding> == 1,
			count_of_decayed_same_as<vk::descriptor_type> == 1,
			count_of_decayed_same_as<vk::descriptor_count> <= 1,
			count_of_decayed_same_as<vk::shader_stages> == 1
		>
		descriptor_set_layout_binding(Args&&... args) {
			tuple a{ args... };

			descriptor_binding = a.template
				get_decayed_same_as<vk::descriptor_binding>();
			descriptor_type = a.template
				get_decayed_same_as<vk::descriptor_type>();
			stage_flags = a.template
				get_decayed_same_as<vk::shader_stages>();
			
			if constexpr(types<Args...>::template
				count_of_decayed_same_as<vk::descriptor_count> > 0
			) {
				descriptor_count = a.template
					get_decayed_same_as<vk::descriptor_count>();
			}

		} // constructor

	}; // descriptor_set_layout_binding

} // vk