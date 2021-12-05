#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/types/count_of_type.hpp>
#include <core/types/are_contain_range_of_value_type.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/for_each_of_type.hpp>
#include <core/types/are_contain_type.hpp>
#include <core/wrapper/of_integer.hpp>
#include <core/elements/one_of.hpp>
#include <core/exchange.hpp>

#include "graphics_pipeline_create_info.hpp"
#include "../shared/result.hpp"
#include "../device/handle.hpp"
#include "../shared/subpass.hpp"
#include "layout/handle.hpp"

#include "../shared/headers.hpp"

namespace vk {
	struct base_pipeline_index : wrapper::of_integer<uint32> {};

	// vk::device,
	// array<vk::pipeline_shader_stage_create_info, 2>,
	// vk::pipeline_vertex_input_state_create_info,
	// vk::pipeline_input_assembly_state_create_info,
	// vk::pipeline_viewport_state_create_info, 
	// vk::pipeline_rasterization_state_create_info, 
	// vk::pipeline_multisample_state_create_info, 
	// vk::pipeline_color_blend_attachment_state, 
	// vk::pipeline_layout, 
	// vk::render_pass, 
	// vk::subpass>

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::device>::equals<1>,
			types::count_of_type<vk::pipeline_create_flag>::greater_or_equals<0>,
			types::count_of_ranges_of_value_type<vk::pipeline_shader_stage_create_info>::equals<1>,
			types::count_of_type<vk::pipeline_vertex_input_state_create_info>::less_or_equals<1>,
			types::count_of_type<vk::pipeline_input_assembly_state_create_info>::less_or_equals<1>,
			types::count_of_type<vk::pipeline_tesselation_state_create_info>::less_or_equals<1>,
			types::count_of_type<vk::pipeline_viewport_state_create_info>::less_or_equals<1>,
			types::count_of_type<vk::pipeline_rasterization_state_create_info>::equals<1>,
			types::count_of_type<vk::pipeline_multisample_state_create_info>::less_or_equals<1>,
			types::count_of_type<vk::pipeline_depth_stencil_state_create_info>::less_or_equals<1>,
			types::count_of_type<vk::pipeline_color_blend_state_create_info>::less_or_equals<1>,
			types::count_of_type<vk::pipeline_dynamic_state_create_info>::less_or_equals<1>,
			types::count_of_type<vk::pipeline_layout>::equals<1>,
			types::count_of_type<vk::render_pass>::equals<1>,
			types::count_of_type<vk::subpass>::equals<1>,
			types::count_of_type<vk::pipeline>::less_or_equals<1>,
			types::count_of_type<vk::base_pipeline_index>::less_or_equals<1>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::pipeline>
	try_create_graphics_pipeline(const Args&... args) {
		vk::pipeline_rasterization_state_create_info prsci = elements::of_type<const vk::pipeline_rasterization_state_create_info&>::for_elements_of(args...);
		vk::render_pass render_pass = elements::of_type<const vk::render_pass&>::for_elements_of(args...);
		vk::pipeline_layout layout = elements::of_type<const vk::pipeline_layout&>::for_elements_of(args...);
		vk::subpass subpass = elements::of_type<const vk::subpass&>::for_elements_of(args...);

		vk::graphics_pipeline_create_info ci {
			.rasterization_state = &prsci,
			.layout = layout,
			.render_pass = render_pass,
			.subpass = subpass
		};

		elements::for_each_of_type<const vk::pipeline_create_flag&>(
			[&](auto f) { ci.flags.set(f); },
			args...
		);

		auto& stages = elements::range_of_value_type<vk::pipeline_shader_stage_create_info>::for_elements_of(args...);
		ci.stages = stages.data();
		ci.stage_count = (uint32)stages.size();

		if constexpr(types::are_contain_type<vk::pipeline_vertex_input_state_create_info>::for_types_of<Args...>)
			ci.vertex_input_state = & elements::of_type<const vk::pipeline_vertex_input_state_create_info&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::pipeline_input_assembly_state_create_info>::for_types_of<Args...>)
			ci.input_assembly_state = & elements::of_type<const vk::pipeline_input_assembly_state_create_info&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::pipeline_tesselation_state_create_info>::for_types_of<Args...>)
			ci.tesselation_state = & elements::of_type<const vk::pipeline_tesselation_state_create_info&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::pipeline_viewport_state_create_info>::for_types_of<Args...>)
			ci.viewport_state = & elements::of_type<const vk::pipeline_viewport_state_create_info&>::for_elements_of(args...);
		
		if constexpr(types::are_contain_type<vk::pipeline_multisample_state_create_info>::for_types_of<Args...>)
			ci.multisample_state = & elements::of_type<const vk::pipeline_multisample_state_create_info&>::for_elements_of(args...);
		
		if constexpr(types::are_contain_type<vk::pipeline_depth_stencil_state_create_info>::for_types_of<Args...>)
			ci.depth_stencil_state = & elements::of_type<const vk::pipeline_depth_stencil_state_create_info&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::pipeline_color_blend_state_create_info>::for_types_of<Args...>)
			ci.color_blend_state = & elements::of_type<const vk::pipeline_color_blend_state_create_info&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::pipeline_dynamic_state_create_info>::for_types_of<Args...>)
			ci.dynamic_state = & elements::of_type<const vk::pipeline_dynamic_state_create_info&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::pipeline&>::for_types_of<Args...>)
			ci.base_pipeline = elements::of_type<vk::pipeline&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::base_pipeline_index>::for_types_of<Args...>)
			ci.base_pipeline = elements::of_type<const vk::base_pipeline_index&>::for_elements_of(args...);

		vk::device device = elements::of_type<const vk::device&>::for_elements_of(args...);
		VkPipeline pipeline;

		vk::result result {
			(int32) vkCreateGraphicsPipelines(
				(VkDevice) device.handle,
				(VkPipelineCache) nullptr,
				(uint32) 1,
				(VkGraphicsPipelineCreateInfo*) & ci,
				nullptr,
				(VkPipeline*) &pipeline
			)
		};

		if(result.success()) return vk::pipeline{ pipeline };
		return result;
	}

	template<typename... Args>
	vk::pipeline create_graphics_pipeline(Args&&... args) {
		auto result = vk::try_create_graphics_pipeline(forward<Args>(args)...);
		if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
		return result.template get<vk::pipeline>();
	}
}