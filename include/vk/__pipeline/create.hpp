#pragma once

#include "handle.hpp"
#include "create_info.hpp"
#include "../__pipeline_layout/handle.hpp"
#include "../__device/handle.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__internal/subpass.hpp"
#include "../__internal/function.hpp"
#include "../__internal/result.hpp"

#include <type.hpp>
#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct create_graphics_pipelines_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		void* pipeline_cache,
		uint32 create_info_count,
		const vk::graphics_pipeline_create_info* create_infos,
		const void* allocator,
		handle<vk::pipeline>::underlying_type* pipelines
	)> {
		static constexpr auto name = "vkCreateGraphicsPipelines";
	};

	struct base_pipeline_index { uint32 _; };

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::pipeline_layout>> == 1,
		count_of_decayed_same_as<handle<vk::render_pass>> == 1,
		count_of_decayed_same_as<handle<vk::pipeline>> <= 1,
		count_of_range_of_decayed<vk::pipeline_shader_stage_create_info> == 1,
		count_of_decayed_same_as<vk::pipeline_create_flag> >= 0,
		count_of_decayed_same_as<
			vk::pipeline_vertex_input_state_create_info
		> <= 1,
		count_of_decayed_same_as<
			vk::pipeline_input_assembly_state_create_info
		> <= 1,
		count_of_decayed_same_as<
			vk::pipeline_tesselation_state_create_info
		> <= 1,
		count_of_decayed_same_as<
			vk::pipeline_viewport_state_create_info
		> <= 1,
		count_of_decayed_same_as<
			vk::pipeline_rasterization_state_create_info
		> == 1,
		count_of_decayed_same_as<
			vk::pipeline_multisample_state_create_info
		> == 1,
		count_of_decayed_same_as<
			vk::pipeline_depth_stencil_state_create_info
		> <= 1,
		count_of_satisfying_predicate<
			is_derived_from<vk::_pipeline_color_blend_state_create_info_mark>.while_decayed
		> <= 1,
		count_of_decayed_same_as<
			vk::pipeline_dynamic_state_create_info
		> <= 1,
		count_of_decayed_same_as<vk::subpass> == 1,
		count_of_decayed_same_as<vk::base_pipeline_index> <= 1
	>
	vk::expected<handle<vk::pipeline>>
	try_create_graphics_pipelines(Args&&... args) {
		tuple a { args... };

		vk::pipeline_rasterization_state_create_info prsci = a.template
			get_decayed_same_as<vk::pipeline_rasterization_state_create_info>();

		handle<vk::render_pass> render_pass = a.template
			get_decayed_same_as<handle<vk::render_pass>>();

		handle<vk::pipeline_layout> layout = a.template
			get_decayed_same_as<handle<vk::pipeline_layout>>();

		vk::subpass subpass = a.template
			get_decayed_same_as<vk::subpass>();

		vk::graphics_pipeline_create_info ci {
			.rasterization_state = &prsci,
			.layout = layout.underlying(),
			.render_pass = render_pass.underlying(),
			.subpass = subpass
		};

		a.template for_each([&]<typename Type>(Type& arg) {
			if constexpr(
				is_same_as<vk::pipeline_create_flag>
				.while_decayed
				.for_type<Type>()
			) {
				ci.flags.set(arg);
			}
		});

		auto& stages = a.template
			get_range_of_decayed<vk::pipeline_shader_stage_create_info>();

		ci.stages = stages.iterator();
		ci.stage_count = (uint32)stages.size();

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<
				vk::pipeline_vertex_input_state_create_info
			> > 0
		) {
			ci.vertex_input_state = & a.template
				get_decayed_same_as<
					vk::pipeline_vertex_input_state_create_info
				>();
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<
				vk::pipeline_input_assembly_state_create_info
			> > 0
		) {
			ci.input_assembly_state = & a.template
				get_decayed_same_as<
					vk::pipeline_input_assembly_state_create_info
				>();
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<
				vk::pipeline_tesselation_state_create_info
			> > 0
		) {
			ci.tesselation_state = & a.template
				get_decayed_same_as<
					vk::pipeline_tesselation_state_create_info
				>();
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<
				vk::pipeline_viewport_state_create_info
			> > 0
		) {
			ci.viewport_state = & a.template
				get_decayed_same_as<
					vk::pipeline_viewport_state_create_info
				>();
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<
				vk::pipeline_multisample_state_create_info
			> > 0
		) {
			ci.multisample_state = & a.template
				get_decayed_same_as<
					vk::pipeline_multisample_state_create_info
				>();
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<
				vk::pipeline_depth_stencil_state_create_info
			> > 0
		) {
			ci.depth_stencil_state = & a.template
				get_decayed_same_as<
					vk::pipeline_depth_stencil_state_create_info
				>();
		}

		vk::_pipeline_color_blend_state_create_info cbs_ci{};

		if constexpr (types<Args...>::template
			count_of_satisfying_predicate<
				is_derived_from<vk::_pipeline_color_blend_state_create_info_mark>.while_decayed
			> > 0
		) {
			cbs_ci = a.template
				get_satisfying_predicate<
					is_derived_from<vk::_pipeline_color_blend_state_create_info_mark>.while_decayed
				>();
			ci.color_blend_state = &cbs_ci;
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::pipeline_dynamic_state_create_info> > 0
		) {
			ci.dynamic_state = & a.template
				get_decayed_same_as<
					vk::pipeline_dynamic_state_create_info
				>();
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::base_pipeline_index> > 0
		) {
			ci.base_pipeline_index = a.template
				get_decayed_same_as<vk::base_pipeline_index>();
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<handle<vk::pipeline>> > 0
		) {
			ci.base_pipeline = a.template
				get_decayed_same_as<handle<vk::pipeline>>();
		}

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::pipeline> pipeline;

		vk::result result {
			vk::get_device_function<vk::create_graphics_pipelines_function>(
				instance, device
			)(
				device.underlying(),
				nullptr,
				(uint32) 1,
				&ci,
				nullptr,
				&pipeline.underlying()
			)
		};

		if(result.error()) return result;

		return handle<vk::pipeline>{ pipeline };
	}

	template<typename... Args>
	handle<vk::pipeline>
	create_graphics_pipelines(Args&&... args) {
		vk::expected<handle<vk::pipeline>> result
			= vk::try_create_graphics_pipelines(forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk