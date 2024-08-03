#pragma once

#include "./vertex_input_binding_description.hpp"
#include "./vertex_input_attribute_description.hpp"

#include <types.hpp>
#include <tuple.hpp>
#include <range.hpp>

namespace vk {

	struct _pipeline_vertex_input_state_create_info {
		const uint32 structure_type = 19;
		const void*  next = nullptr;
		uint32       flags{};
		uint32       vertex_binding_description_count{};
		const vertex_input_binding_description*
		             vertex_binding_descriptions{};
		uint32       vertex_attribute_description_count{};
		const vertex_input_attribute_description*
		             vertex_attribute_descriptions{};
	};

	struct _pipeline_vertex_input_state_create_info_mark{};

	static constexpr auto is_pipeline_vertex_input_state_create_info
		= is_derived_from<_pipeline_vertex_input_state_create_info_mark>;

	template<
		basic_range BindingDescriptions,
		basic_range AttributeDescriptions
	>
	struct pipeline_vertex_input_state_create_info :
		_pipeline_vertex_input_state_create_info_mark
	{
		BindingDescriptions binding_descriptions;
		AttributeDescriptions attribute_descriptions;

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			is_same_as<BindingDescriptions> <= 1,
			is_same_as<AttributeDescriptions> <= 1
		>
		pipeline_vertex_input_state_create_info(Args&&... args):
			binding_descriptions {
				tuple{args...}
				.template get_or<is_same_as<BindingDescriptions>.decayed>(
					[]{ return span<vertex_input_binding_description>{}; }
				)
			},
			attribute_descriptions {
				tuple{args...}
				.template get_or<is_same_as<AttributeDescriptions>.decayed>(
					[]{ return span<vertex_input_attribute_description>{}; }
				)
			}
		{}

	}; // pipeline_vertex_input_state_create_info

	template<typename... Args>
	pipeline_vertex_input_state_create_info(Args&&...) -> 
		pipeline_vertex_input_state_create_info<
			typename types<Args...>::template get_or<
				is_range_of<
					is_same_as<vk::vertex_input_binding_description>.decayed
				>,
				span<vk::vertex_input_binding_description>
			>,
			typename types<Args...>::template get_or<
				is_range_of<
					is_same_as<vk::vertex_input_attribute_description>.decayed
				>,
				span<vk::vertex_input_attribute_description>
			>
		>;

} // vk