#pragma once

#include "handle.hpp"
#include "create_info.hpp"
#include "layout/handle.hpp"

#include "../device/handle.hpp"
#include "../subpass.hpp"
#include "../create_or_allocate.hpp"
#include "../function.hpp"

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/elements/pass_not_satisfying_type_predicate.hpp>

extern "C" VK_ATTR int32 VK_CALL vkCreateGraphicsPipelines(
	handle<vk::device> device,
	void* pipeline_cache,
	uint32 create_info_count,
	const vk::graphics_pipeline_create_info* create_infos,
	const void* allocator,
	handle<vk::pipeline>* pipelines
);

namespace vk {

	struct base_pipeline_index { uint32 _; };

	template<>
	struct vk::create_t<vk::pipeline> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<handle<vk::device>>,
			types::are_contain_one_decayed<handle<vk::pipeline_layout>>,
			types::are_contain_one_decayed<handle<vk::render_pass>>,
			types::are_may_contain_one_decayed<handle<vk::pipeline>>,
			types::are_contain_range_of<vk::pipeline_shader_stage_create_info>,
			types::are_may_contain_decayed<vk::pipeline_create_flag>,
			types::are_may_contain_one_decayed<
				vk::pipeline_vertex_input_state_create_info
			>,
			types::are_may_contain_one_decayed<
				vk::pipeline_input_assembly_state_create_info
			>,
			types::are_may_contain_one_decayed<
				vk::pipeline_tesselation_state_create_info
			>,
			types::are_may_contain_one_decayed<
				vk::pipeline_viewport_state_create_info
			>,
			types::are_contain_one_decayed<
				vk::pipeline_rasterization_state_create_info
			>,
			types::are_may_contain_one_decayed<
				vk::pipeline_multisample_state_create_info
			>,
			types::are_may_contain_one_decayed<
				vk::pipeline_depth_stencil_state_create_info
			>,
			types::are_may_contain_one_decayed<
				vk::pipeline_color_blend_state_create_info
			>,
			types::are_may_contain_one_decayed<
				vk::pipeline_dynamic_state_create_info
			>,
			types::are_contain_one_decayed<vk::subpass>,
			types::are_may_contain_one_decayed<vk::base_pipeline_index>
		>::for_types<Args...>
		vk::expected<handle<vk::pipeline>>
		operator () (Args&&... args) const {
			vk::pipeline_rasterization_state_create_info prsci {
				elements::decayed<
					vk::pipeline_rasterization_state_create_info
				>(args...)
			};

			auto render_pass {
				elements::decayed<handle<vk::render_pass>>(args...)
			};

			auto layout {
				elements::decayed<handle<vk::pipeline_layout>>(args...)
			};

			vk::subpass subpass = elements::decayed<vk::subpass>(args...);

			vk::graphics_pipeline_create_info ci {
				.rasterization_state = &prsci,
				.layout = layout,
				.render_pass = render_pass,
				.subpass = subpass
			};

			elements::for_each_decayed<vk::pipeline_create_flag>(args...)(
				[&](auto f) { ci.flags.set(f); }
			);

			auto& stages = elements::range_of<
				vk::pipeline_shader_stage_create_info
			>(args...);

			ci.stages = stages.data();
			ci.stage_count = (uint32)stages.size();

			if constexpr (
				types::are_contain_decayed<
					vk::pipeline_vertex_input_state_create_info
				>::for_types<Args...>
			) {
				ci.vertex_input_state = & elements::decayed<
					vk::pipeline_vertex_input_state_create_info
				>(args...);
			}

			if constexpr (
				types::are_contain_decayed<
					vk::pipeline_input_assembly_state_create_info
				>::for_types<Args...>
			) {
				ci.input_assembly_state = & elements::decayed<
					vk::pipeline_input_assembly_state_create_info
				>(args...);
			}

			if constexpr (
				types::are_contain_decayed<
					vk::pipeline_tesselation_state_create_info
				>::for_types<Args...>
			) {
				ci.tesselation_state = & elements::decayed<
					vk::pipeline_tesselation_state_create_info
				>(args...);
			}

			if constexpr (
				types::are_contain_decayed<
					vk::pipeline_viewport_state_create_info
				>::for_types<Args...>
			) {
				ci.viewport_state = & elements::decayed<
					vk::pipeline_viewport_state_create_info
				>(args...);
			}

			if constexpr (
				types::are_contain_decayed<
					vk::pipeline_multisample_state_create_info
				>::for_types<Args...>
			) {
				ci.multisample_state = & elements::decayed<
					vk::pipeline_multisample_state_create_info
				>(args...);
			}

			if constexpr (
				types::are_contain_decayed<
					vk::pipeline_depth_stencil_state_create_info
				>::for_types<Args...>
			) {
				ci.depth_stencil_state = & elements::decayed<
					vk::pipeline_depth_stencil_state_create_info
				>(args...);
			}

			if constexpr (
				types::are_contain_decayed<
					vk::pipeline_color_blend_state_create_info
				>::for_types<Args...>
			) {
				ci.color_blend_state = & elements::decayed<
					vk::pipeline_color_blend_state_create_info
				>(args...);
			}

			if constexpr (
				types::are_contain_decayed<
					vk::pipeline_dynamic_state_create_info
				>::for_types<Args...>
			) {
				ci.dynamic_state = & elements::decayed<
					vk::pipeline_dynamic_state_create_info
				>(args...);
			}

			if constexpr (
				types::are_contain_decayed<
					vk::base_pipeline_index
				>::for_types<Args...>
			) {
				ci.base_pipeline_index = elements::decayed<
					vk::base_pipeline_index
				>(args...);
			}

			if constexpr (
				types::are_contain_one_decayed<
					handle<vk::pipeline>
				>::for_types<Args...>
			) {
				ci.base_pipeline = {
					elements::decayed<handle<vk::pipeline>>(args...)
				};
			}

			auto device = elements::decayed<handle<vk::device>>(args...);

			handle<vk::pipeline> pipeline;

			vk::result result {
				vkCreateGraphicsPipelines(
					device,
					nullptr,
					(uint32) 1,
					&ci,
					nullptr,
					&pipeline
				)
			};

			if(result.error()) return result;

			return handle<vk::pipeline>{ pipeline };
		}

		template<typename... Args>
		requires types::are_contain_decayed<
			vk::primitive_topology
		>::for_types<Args...>
		vk::expected<handle<vk::pipeline>>
		operator () (Args&&... args) const {
			vk::primitive_topology topology = elements::decayed<
				vk::primitive_topology
			>(args...);

			return elements::pass_not_satisfying_type_predicate<
				type::is_same_as<vk::primitive_topology>
			>(
				vk::pipeline_input_assembly_state_create_info {
					.topology = topology
				},
				forward<Args>(args)...
			)(vk::create_t<vk::pipeline>{});
		}

	}; // create_t<pipeline>

} // vk