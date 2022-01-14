#pragma once

#include "../../shared/subpass.hpp"
#include "../../object/create_or_allocate.hpp"
#include "../device/handle.hpp"
#include "layout/handle.hpp"
#include "handle.hpp"
#include "create_info.hpp"

namespace vk {

	struct base_pipeline_index : wrapper::of_integer<uint32> {};

	template<>
	struct vk::create_t<vk::pipeline> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::pipeline_layout>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::render_pass>,
			types::vk::are_may_contain_one_possibly_guarded_handle_of<vk::pipeline>,
			types::count_of_ranges_of_value_type<vk::pipeline_shader_stage_create_info>::equals<1>,
			types::count_of_type<vk::pipeline_create_flag>::greater_or_equals<0>::ignore_const::ignore_reference,
			types::count_of_type<vk::pipeline_vertex_input_state_create_info>::less_or_equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::pipeline_input_assembly_state_create_info>::less_or_equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::pipeline_tesselation_state_create_info>::less_or_equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::pipeline_viewport_state_create_info>::less_or_equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::pipeline_rasterization_state_create_info>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::pipeline_multisample_state_create_info>::less_or_equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::pipeline_depth_stencil_state_create_info>::less_or_equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::pipeline_color_blend_state_create_info>::less_or_equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::pipeline_dynamic_state_create_info>::less_or_equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::subpass>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::base_pipeline_index>::less_or_equals<1>::ignore_const::ignore_reference
		>::for_types_of<Args...>
		vk::expected<vk::handle<vk::pipeline>>
		operator () (Args&&... args) const {
			vk::pipeline_rasterization_state_create_info prsci = elements::of_type<vk::pipeline_rasterization_state_create_info>::ignore_const::ignore_reference::for_elements_of(args...);

			auto& render_pass = elements::vk::possibly_guarded_handle_of<vk::render_pass>::for_elements_of(args...);
			auto& layout = elements::vk::possibly_guarded_handle_of<vk::pipeline_layout>::for_elements_of(args...);

			vk::subpass subpass = elements::of_type<vk::subpass>::ignore_const::ignore_reference::for_elements_of(args...);

			vk::graphics_pipeline_create_info ci {
				.rasterization_state = &prsci,
				.layout = vk::get_handle(layout),
				.render_pass = vk::get_handle(render_pass),
				.subpass = subpass
			};

			elements::for_each_of_type<vk::pipeline_create_flag>::ignore_const::ignore_reference::function {
				[&](auto f) { ci.flags.set(f); }
			}.for_elements_of(args...);

			auto& stages = elements::range_of_value_type<vk::pipeline_shader_stage_create_info>::for_elements_of(args...);
			ci.stages = stages.data();
			ci.stage_count = (uint32)stages.size();

			if constexpr(types::are_contain_type<vk::pipeline_vertex_input_state_create_info>::ignore_const::ignore_reference::for_types_of<Args...>)
				ci.vertex_input_state = & elements::of_type<vk::pipeline_vertex_input_state_create_info>::ignore_const::ignore_reference::for_elements_of(args...);

			if constexpr(types::are_contain_type<vk::pipeline_input_assembly_state_create_info>::ignore_const::ignore_reference::for_types_of<Args...>)
				ci.input_assembly_state = & elements::of_type<vk::pipeline_input_assembly_state_create_info>::ignore_const::ignore_reference::for_elements_of(args...);

			if constexpr(types::are_contain_type<vk::pipeline_tesselation_state_create_info>::ignore_const::ignore_reference::for_types_of<Args...>)
				ci.tesselation_state = & elements::of_type<vk::pipeline_tesselation_state_create_info>::ignore_const::ignore_reference::for_elements_of(args...);

			if constexpr(types::are_contain_type<vk::pipeline_viewport_state_create_info>::ignore_const::ignore_reference::for_types_of<Args...>)
				ci.viewport_state = & elements::of_type<vk::pipeline_viewport_state_create_info>::ignore_const::ignore_reference::for_elements_of(args...);

			if constexpr(types::are_contain_type<vk::pipeline_multisample_state_create_info>::ignore_const::ignore_reference::for_types_of<Args...>)
				ci.multisample_state = & elements::of_type<vk::pipeline_multisample_state_create_info>::ignore_const::ignore_reference::for_elements_of(args...);

			if constexpr(types::are_contain_type<vk::pipeline_depth_stencil_state_create_info>::ignore_const::ignore_reference::for_types_of<Args...>)
				ci.depth_stencil_state = & elements::of_type<vk::pipeline_depth_stencil_state_create_info>::ignore_const::ignore_reference::for_elements_of(args...);

			if constexpr(types::are_contain_type<vk::pipeline_color_blend_state_create_info>::ignore_const::ignore_reference::for_types_of<Args...>)
				ci.color_blend_state = & elements::of_type<vk::pipeline_color_blend_state_create_info>::ignore_const::ignore_reference::for_elements_of(args...);

			if constexpr(types::are_contain_type<vk::pipeline_dynamic_state_create_info>::ignore_const::ignore_reference::for_types_of<Args...>)
				ci.dynamic_state = & elements::of_type<vk::pipeline_dynamic_state_create_info>::ignore_const::ignore_reference::for_elements_of(args...);

			if constexpr(types::are_contain_type<vk::base_pipeline_index>::ignore_const::ignore_reference::for_types_of<Args...>)
				ci.base_pipeline_index = elements::of_type<vk::base_pipeline_index>::ignore_const::ignore_reference::for_elements_of(args...);

			if constexpr(types::vk::are_contain_one_possibly_guarded_handle_of<vk::pipeline>::for_types_of<Args...>)
				ci.base_pipeline = vk::get_handle(elements::vk::possibly_guarded_handle_of<vk::pipeline>::for_elements_of(args...));

			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);
			VkPipeline pipeline;

			vk::result result {
				(int32) vkCreateGraphicsPipelines(
					(VkDevice) vk::get_handle_value(device),
					(VkPipelineCache) nullptr,
					(uint32) 1,
					(VkGraphicsPipelineCreateInfo*) & ci,
					(VkAllocationCallbacks*) nullptr,
					(VkPipeline*) &pipeline
				)
			};

			if(result.error()) return result;

			return vk::handle<vk::pipeline>{ pipeline };
		}

		template<typename... Args>
		requires types::count_of_type<vk::primitive_topology>::equals<1>::ignore_const::ignore_reference::for_types_of<Args...>
		vk::expected<vk::handle<vk::pipeline>>
		operator () (Args&&... args) const {
			vk::primitive_topology topology = elements::of_type<vk::primitive_topology>::ignore_const::ignore_reference::for_elements_of(args...);

			return elements::pass_satisfying_type_predicate<type::is_same_as<vk::primitive_topology>::negate>::to_function {
				[&,this]<typename... Others>(Others&&... v) {
					return this->operator () (
						vk::pipeline_input_assembly_state_create_info{ .topology = topology },
						forward<Others>(v)...
					); }
			}.for_elements_of(forward<Args>(args)...);
		}

	};

} // vk