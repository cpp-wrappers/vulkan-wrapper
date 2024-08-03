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
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::pipeline_layout>>.decayed == 1,
		is_same_as<handle<vk::render_pass>>.decayed == 1,
		is_same_as<handle<vk::pipeline>>.decayed <= 1,
		is_range_of<
			is_same_as<vk::pipeline_shader_stage_create_info>.decayed
		> == 1,
		is_same_as<vk::pipeline_create_flag>.decayed >= 0,
		vk::is_pipeline_vertex_input_state_create_info.decayed <= 1,
		is_same_as<vk::pipeline_input_assembly_state_create_info>.decayed <= 1,
		is_same_as<vk::pipeline_tesselation_state_create_info>.decayed <= 1,
		is_same_as<vk::pipeline_viewport_state_create_info>.decayed <= 1,
		is_same_as<vk::pipeline_rasterization_state_create_info>.decayed == 1,
		is_same_as<vk::pipeline_multisample_state_create_info>.decayed == 1,
		is_same_as<vk::pipeline_depth_stencil_state_create_info>.decayed <= 1,
		vk::is_pipeline_color_blend_state_create_info.decayed <= 1,
		is_same_as<vk::pipeline_dynamic_state_create_info>.decayed <= 1,
		is_same_as<vk::subpass>.decayed == 1,
		is_same_as<vk::base_pipeline_index>.decayed <= 1
	>
	vk::expected<handle<vk::pipeline>>
	try_create_graphics_pipelines(Args&&... args) {
		tuple a { args... };

		vk::pipeline_rasterization_state_create_info prsci = a.template
			get<is_same_as<vk::pipeline_rasterization_state_create_info>.decayed>();

		handle<vk::render_pass> render_pass = a.template
			get<is_same_as<handle<vk::render_pass>>.decayed>();

		handle<vk::pipeline_layout> layout = a.template
			get<is_same_as<handle<vk::pipeline_layout>>.decayed>();

		vk::subpass subpass = a.template
			get<is_same_as<vk::subpass>.decayed>();

		vk::graphics_pipeline_create_info ci {
			.rasterization_state = &prsci,
			.layout = layout.underlying(),
			.render_pass = render_pass.underlying(),
			.subpass = subpass
		};

		a.template for_each([&]<typename Type>(Type& arg) {
			if constexpr(
				is_same_as<vk::pipeline_create_flag>.decayed.for_type<Type>()
			) {
				ci.flags.set(arg);
			}
		});

		auto& stages = a.template
			get<is_range_of<is_same_as<vk::pipeline_shader_stage_create_info>.decayed>>();

		ci.stages = stages.iterator();
		ci.stage_count = (uint32)stages.size();

		vk::_pipeline_vertex_input_state_create_info visci{};

		if constexpr (
			(vk::is_pipeline_vertex_input_state_create_info.decayed > 0)
			.for_types<Args...>()
		) {
			auto& vis = a.template
				get<vk::is_pipeline_vertex_input_state_create_info.decayed>();

			visci.vertex_binding_description_count
				= vis.binding_descriptions.size();
			visci.vertex_binding_descriptions
				= vis.binding_descriptions.iterator();

			visci.vertex_attribute_description_count
				= vis.attribute_descriptions.size();
			visci.vertex_attribute_descriptions
				= vis.attribute_descriptions.iterator();

			ci.vertex_input_state = &visci;
		}

		if constexpr (
			(is_same_as<
				vk::pipeline_input_assembly_state_create_info
			>.decayed > 0).for_types<Args...>()
		) {
			ci.input_assembly_state = & a.template
				get<is_same_as<
					vk::pipeline_input_assembly_state_create_info
				>.decayed>();
		}

		if constexpr (
			(is_same_as<
				vk::pipeline_tesselation_state_create_info
			>.decayed > 0).for_types<Args...>()
		) {
			ci.tesselation_state = & a.template
				get<is_same_as<
					vk::pipeline_tesselation_state_create_info
				>.decayed>();
		}

		if constexpr (
			(is_same_as<
				vk::pipeline_viewport_state_create_info
			>.decayed > 0).for_types<Args...>()
		) {
			ci.viewport_state = & a.template
				get<is_same_as<
					vk::pipeline_viewport_state_create_info
				>.decayed>();
		}

		if constexpr (
			(is_same_as<
				vk::pipeline_multisample_state_create_info
			>.decayed > 0).for_types<Args...>()
		) {
			ci.multisample_state = & a.template
				get<is_same_as<
					vk::pipeline_multisample_state_create_info
				>.decayed>();
		}

		if constexpr (
			(is_same_as<
				vk::pipeline_depth_stencil_state_create_info
			>.decayed > 0).for_types<Args...>()
		) {
			ci.depth_stencil_state = & a.template
				get<is_same_as<
					vk::pipeline_depth_stencil_state_create_info
				>.decayed>();
		}

		vk::_pipeline_color_blend_state_create_info cbs_ci{};

		if constexpr (
			(vk::is_pipeline_color_blend_state_create_info.decayed > 0)
			.for_types<Args...>()
		) {
			cbs_ci = a.template
				get<vk::is_pipeline_color_blend_state_create_info.decayed>();
			ci.color_blend_state = &cbs_ci;
		}

		if constexpr (
			(is_same_as<vk::pipeline_dynamic_state_create_info>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.dynamic_state = & a.template
				get<is_same_as<
					vk::pipeline_dynamic_state_create_info
				>.decayed>();
		}

		if constexpr (
			(is_same_as<vk::base_pipeline_index>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.base_pipeline_index = a.template
				get<is_same_as<vk::base_pipeline_index>.decayed>();
		}

		if constexpr (
			(is_same_as<handle<vk::pipeline>>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.base_pipeline = a.template
				get<is_same_as<handle<vk::pipeline>>.decayed>();
		}

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

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