#pragma once

#include "./vertex_input_binding_description.hpp"
#include "./vertex_input_attribute_description.hpp"

#include <types.hpp>
#include <tuple.hpp>
#include <range.hpp>

namespace vk {

	struct pipeline_vertex_input_state_create_info {
		const uint32 structure_type = 19;
		const void*  next = nullptr;
		uint32       flags{};
		uint32       vertex_binding_description_count{};
		const vertex_input_binding_description*
		             vertex_binding_descriptions{};
		uint32       vertex_attribute_description_count{};
		const vertex_input_attribute_description*
		             vertex_attribute_descriptions{};

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			count_of<is_range_of<
				is_same_as<vk::vertex_input_binding_description>.decayed
			>> <= 1,
			count_of<is_range_of<
				is_same_as<vk::vertex_input_attribute_description>.decayed
			>> <= 1
		>
		pipeline_vertex_input_state_create_info(Args&&... args) {
			if constexpr(types<Args...>::template
				count_of<is_range_of<
					is_same_as<vk::vertex_input_binding_description>.decayed
				>> > 0
			) {
				auto& binding_descriptions = tuple{ args... }.template
					get<is_range_of<
						is_same_as<vk::vertex_input_binding_description>.decayed
					>>();

				vertex_binding_description_count
					= (uint32) binding_descriptions.size();
				vertex_binding_descriptions = binding_descriptions.iterator();
			}

			if constexpr(types<Args...>::template
				count_of<is_range_of<
					is_same_as<vk::vertex_input_attribute_description>.decayed
				>> > 0
			) {
				auto& attribute_descriptions = tuple{ args... }.template
					get<is_range_of<
						is_same_as<vk::vertex_input_attribute_description>.decayed
					>>();

				vertex_attribute_description_count
					= (uint32) attribute_descriptions.size();
				vertex_attribute_descriptions
					= attribute_descriptions.iterator();
			}
		}

	}; // pipeline_vertex_input_state_create_info

} // vk