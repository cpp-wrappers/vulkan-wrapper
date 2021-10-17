#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/types/count_of_type.hpp>
#include <core/types/are_contain_range_of_value_type.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/for_each_of_type.hpp>

#include "../headers.hpp"
#include "core/types/are_contain_type.hpp"
#include "graphics_pipeline_create_info.hpp"
#include "../result.hpp"

namespace vk {

	struct device;
	struct pipeline;

	struct subpass : uint32 {};
	struct base_pipeline_index : uint32 {};

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::device&>::equals<1u>,
			types::count_of_type<vk::pipeline_create_flag>::remove_reference::greater_or_equals<0u>,
			types::count_of_ranges_of_value_type<vk::pipeline_shader_stage_create_info>::equals<1u>,
			types::count_of_type<vk::pipeline_vertex_input_state_create_info>::remove_reference::less_or_equals<1u>,
			types::count_of_type<vk::pipeline_input_assembly_state_create_info>::remove_reference::less_or_equals<1u>,
			types::count_of_type<vk::pipeline_tesselation_state_create_info>::remove_reference::less_or_equals<1u>,
			types::count_of_type<vk::pipeline_viewport_state_create_info>::remove_reference::less_or_equals<1u>,
			types::count_of_type<vk::pipeline_rasterization_state_create_info>::remove_reference::equals<1u>,
			types::count_of_type<vk::pipeline_multisample_state_create_info>::remove_reference::less_or_equals<1u>,
			types::count_of_type<vk::pipeline_depth_stencil_state_create_info>::remove_reference::less_or_equals<1u>,
			types::count_of_type<vk::pipeline_color_blend_state_create_info>::remove_reference::less_or_equals<1u>,
			types::count_of_type<vk::pipeline_dynamic_state_create_info>::remove_reference::less_or_equals<1u>,
			types::count_of_type<vk::pipeline_layout&>::equals<1u>,
			types::count_of_type<vk::render_pass&>::equals<1u>,
			types::count_of_type<vk::subpass>::remove_reference::equals<1u>,
			types::count_of_type<vk::pipeline&>::less_or_equals<1u>,
			types::count_of_type<vk::base_pipeline_index>::remove_reference::less_or_equals<1u>
		>::for_types_of<Args...>
	)
	vk::pipeline& create_graphics_pipeline(Args&&... args) {
		vk::graphics_pipeline_create_info ci {
			.rasterization_state = & elements::of_type<vk::pipeline_rasterization_state_create_info&>::for_elements_of(args...),
			.layout = elements::of_type<vk::pipeline_layout&>::for_elements_of(args...),
			.render_pass = elements::of_type<vk::render_pass&>::for_elements_of(args...),
			.subpass = (primitive::uint32) elements::of_type<vk::subpass&>::for_elements_of(args...)
		};

		elements::for_each_of_type_remove_reference<vk::pipeline_create_flag>(
			[&](auto f) { ci.flags.set(f); },
			args...
		);

		auto& stages = elements::range_of_value_type<vk::pipeline_shader_stage_create_info>::for_elements_of(args...);
		ci.stages = stages.data();
		ci.stage_count = (primitive::uint32)(primitive::uint) stages.size();

		if constexpr(types::are_contain_type<vk::pipeline_vertex_input_state_create_info>::remove_reference::for_types_of<Args...>)
			ci.vertex_input_state = & elements::of_type<vk::pipeline_vertex_input_state_create_info&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::pipeline_input_assembly_state_create_info>::remove_reference::for_types_of<Args...>)
			ci.input_assembly_state = & elements::of_type<vk::pipeline_input_assembly_state_create_info&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::pipeline_tesselation_state_create_info>::remove_reference::for_types_of<Args...>)
			ci.tesselation_state = & elements::of_type<vk::pipeline_tesselation_state_create_info&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::pipeline_viewport_state_create_info>::remove_reference::for_types_of<Args...>)
			ci.viewport_state = & elements::of_type<vk::pipeline_viewport_state_create_info&>::for_elements_of(args...);
		
		if constexpr(types::are_contain_type<vk::pipeline_multisample_state_create_info>::remove_reference::for_types_of<Args...>)
			ci.multisample_state = & elements::of_type<vk::pipeline_multisample_state_create_info&>::for_elements_of(args...);
		
		if constexpr(types::are_contain_type<vk::pipeline_depth_stencil_state_create_info>::remove_reference::for_types_of<Args...>)
			ci.depth_stencil_state = & elements::of_type<vk::pipeline_depth_stencil_state_create_info&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::pipeline_color_blend_state_create_info>::remove_reference::for_types_of<Args...>)
			ci.color_blend_state = & elements::of_type<vk::pipeline_color_blend_state_create_info&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::pipeline_dynamic_state_create_info>::remove_reference::for_types_of<Args...>)
			ci.dynamic_state = & elements::of_type<vk::pipeline_dynamic_state_create_info&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::subpass>::remove_reference::for_types_of<Args...>)
			ci.subpass = elements::of_type<vk::subpass&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::pipeline&>::for_types_of<Args...>)
			ci.base_pipeline = elements::of_type<vk::pipeline&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::base_pipeline_index>::remove_reference::for_types_of<Args...>)
			ci.base_pipeline = elements::of_type<vk::base_pipeline_index&>::for_elements_of(args...);

		vk::pipeline* pipeline;

		vk::throw_if_error(
			vkCreateGraphicsPipelines(
				(VkDevice) & elements::of_type<vk::device&>::for_elements_of(args...),
				nullptr,
				(primitive::uint32) 1,
				(VkGraphicsPipelineCreateInfo*) & ci,
				nullptr,
				(VkPipeline*) &pipeline
			)
		);
		
		return *pipeline;
	}
}