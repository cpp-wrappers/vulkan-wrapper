#pragma once

#include "handle.hpp"
#include "create_info.hpp"
#include "layout/handle.hpp"
#include "../device/handle.hpp"
#include "../../object/create_or_allocate.hpp"
#include "../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../types/are_may_contain_one_possibly_guarded_handle_of.hpp"
#include "../../shared/subpass.hpp"

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/elements/pass_not_satisfying_type_predicate.hpp>

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
			types::are_contain_one_range_of_value_type<vk::pipeline_shader_stage_create_info>,
			types::are_may_contain_decayed_same_as<vk::pipeline_create_flag>,
			types::are_may_contain_one_decayed_same_as<vk::pipeline_vertex_input_state_create_info>,
			types::are_may_contain_one_decayed_same_as<vk::pipeline_input_assembly_state_create_info>,
			types::are_may_contain_one_decayed_same_as<vk::pipeline_tesselation_state_create_info>,
			types::are_may_contain_one_decayed_same_as<vk::pipeline_viewport_state_create_info>,
			types::are_contain_one_decayed_same_as<vk::pipeline_rasterization_state_create_info>,
			types::are_may_contain_one_decayed_same_as<vk::pipeline_multisample_state_create_info>,
			types::are_may_contain_one_decayed_same_as<vk::pipeline_depth_stencil_state_create_info>,
			types::are_may_contain_one_decayed_same_as<vk::pipeline_color_blend_state_create_info>,
			types::are_may_contain_one_decayed_same_as<vk::pipeline_dynamic_state_create_info>,
			types::are_contain_one_decayed_same_as<vk::subpass>,
			types::are_may_contain_one_decayed_same_as<vk::base_pipeline_index>
		>::for_types<Args...>
		vk::expected<vk::handle<vk::pipeline>>
		operator () (Args&&... args) const {
			vk::pipeline_rasterization_state_create_info prsci = elements::decayed_same_as<vk::pipeline_rasterization_state_create_info>(args...);

			auto& render_pass = elements::vk::possibly_guarded_handle_of<vk::render_pass>(args...);
			auto& layout = elements::vk::possibly_guarded_handle_of<vk::pipeline_layout>(args...);

			vk::subpass subpass = elements::decayed_same_as<vk::subpass>(args...);

			vk::graphics_pipeline_create_info ci {
				.rasterization_state = &prsci,
				.layout = vk::get_handle(layout),
				.render_pass = vk::get_handle(render_pass),
				.subpass = subpass
			};

			elements::for_each_decayed_same_as<vk::pipeline_create_flag>(args...)(
				[&](auto f) { ci.flags.set(f); }
			);

			auto& stages = elements::range_of_value_type<vk::pipeline_shader_stage_create_info>(args...);
			ci.stages = stages.data();
			ci.stage_count = (uint32)stages.size();

			if constexpr(types::are_contain_decayed_same_as<vk::pipeline_vertex_input_state_create_info>::for_types<Args...>)
				ci.vertex_input_state = & elements::decayed_same_as<vk::pipeline_vertex_input_state_create_info>(args...);

			if constexpr(types::are_contain_decayed_same_as<vk::pipeline_input_assembly_state_create_info>::for_types<Args...>)
				ci.input_assembly_state = & elements::decayed_same_as<vk::pipeline_input_assembly_state_create_info>(args...);

			if constexpr(types::are_contain_decayed_same_as<vk::pipeline_tesselation_state_create_info>::for_types<Args...>)
				ci.tesselation_state = & elements::decayed_same_as<vk::pipeline_tesselation_state_create_info>(args...);

			if constexpr(types::are_contain_decayed_same_as<vk::pipeline_viewport_state_create_info>::for_types<Args...>)
				ci.viewport_state = & elements::decayed_same_as<vk::pipeline_viewport_state_create_info>(args...);

			if constexpr(types::are_contain_decayed_same_as<vk::pipeline_multisample_state_create_info>::for_types<Args...>)
				ci.multisample_state = & elements::decayed_same_as<vk::pipeline_multisample_state_create_info>(args...);

			if constexpr(types::are_contain_decayed_same_as<vk::pipeline_depth_stencil_state_create_info>::for_types<Args...>)
				ci.depth_stencil_state = & elements::decayed_same_as<vk::pipeline_depth_stencil_state_create_info>(args...);

			if constexpr(types::are_contain_decayed_same_as<vk::pipeline_color_blend_state_create_info>::for_types<Args...>)
				ci.color_blend_state = & elements::decayed_same_as<vk::pipeline_color_blend_state_create_info>(args...);

			if constexpr(types::are_contain_decayed_same_as<vk::pipeline_dynamic_state_create_info>::for_types<Args...>)
				ci.dynamic_state = & elements::decayed_same_as<vk::pipeline_dynamic_state_create_info>(args...);

			if constexpr(types::are_contain_decayed_same_as<vk::base_pipeline_index>::for_types<Args...>)
				ci.base_pipeline_index = elements::decayed_same_as<vk::base_pipeline_index>(args...);

			if constexpr(types::vk::are_contain_one_possibly_guarded_handle_of<vk::pipeline>::for_types<Args...>)
				ci.base_pipeline = vk::get_handle(elements::vk::possibly_guarded_handle_of<vk::pipeline>(args...));

			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);
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
		requires types::are_contain_one_decayed_same_as<vk::primitive_topology>::for_types<Args...>
		vk::expected<vk::handle<vk::pipeline>>
		operator () (Args&&... args) const {
			vk::primitive_topology topology = elements::decayed_same_as<vk::primitive_topology>(args...);

			return elements::pass_not_satisfying_type_predicate<type::is_same_as<vk::primitive_topology>>(
				vk::pipeline_input_assembly_state_create_info{ .topology = topology },
				forward<Args>(args)...
			)(
				[]<typename... Others>(Others&&... others) {
					return vk::create_t<vk::pipeline>{}(forward<Others>(others)...);
				}
			);
		}

	};

} // vk