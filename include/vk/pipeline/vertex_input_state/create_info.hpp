#pragma once

#include "vertex_input_binding_description.hpp"
#include "vertex_input_attribute_description.hpp"

#include <core/range/of_value_type_same_as.hpp>

#include "vk/headers.hpp"

namespace vk {

	struct pipeline_vertex_input_state_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		const void* const next{};
		uint32 flags{};
		uint32 vertex_binding_description_count{};
		const vertex_input_binding_description* vertex_binding_descriptions{};
		uint32 vertex_attribute_description_count{};
		const vertex_input_attribute_description* vertex_attribute_descriptions{};

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_may_contain_range_of<vk::vertex_input_binding_description>,
			types::are_may_contain_range_of<vk::vertex_input_attribute_description>
		>::for_types<Args...>
		pipeline_vertex_input_state_create_info(Args&&... args) {
			if constexpr(types::are_contain_range_of<vk::vertex_input_binding_description>::for_types<Args...>) {
				auto& binding_descriptions = elements::range_of<vk::vertex_input_binding_description>(args...);
				vertex_binding_description_count = (uint32) binding_descriptions.size();
				vertex_binding_descriptions = binding_descriptions.data();
			}

			if constexpr(types::are_contain_range_of<vk::vertex_input_attribute_description>::for_types<Args...>) {
				auto& attribute_descriptions = elements::range_of<vk::vertex_input_attribute_description>(args...);
				vertex_attribute_description_count = (uint32) attribute_descriptions.size();
				vertex_attribute_descriptions = attribute_descriptions.data();
			}
		}
	};

} // vk

static_assert(sizeof(vk::pipeline_vertex_input_state_create_info) == sizeof(VkPipelineVertexInputStateCreateInfo));