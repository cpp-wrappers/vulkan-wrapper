#pragma once

#include "../polygon_mode.hpp"
#include "../cull_mode.hpp"
#include "../front_face.hpp"

#include <core/wrapper/of_integer.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

namespace vk {

	struct enable_depth_clamp :
		wrapper::of_integer<uint32, struct enable_depth_clamp_t>
	{};

	struct enable_rasterizer_discard :
		wrapper::of_integer<uint32, struct enable_rasterizer_discard_t>
	{};

	struct enable_depth_bias :
		wrapper::of_integer<uint32, struct enable_depth_bias_t>
	{};

	struct depth_bias_constant_factor :
		wrapper::of<float, struct depth_bias_constant_factor_t>
	{};

	struct depth_bias_clamp :
		wrapper::of<float, struct depth_bias_clamp_t>
	{};

	struct depth_bias_slope_factor :
		wrapper::of<float, struct depth_bias_slope_factor_t>
	{};

	struct line_width : wrapper::of<float, struct line_width_t> {};

	struct pipeline_rasterization_state_create_info {
		uint32 structure_type = 23;
		const void* next = nullptr;
		uint32 flags{};
		vk::enable_depth_clamp enable_depth_clamp{};
		vk::enable_rasterizer_discard enable_rasterizer_discard{};
		vk::polygon_mode polygon_mode;
		vk::cull_mode cull_mode;
		vk::front_face front_face;
		vk::enable_depth_bias enable_depth_bias{};
		vk::depth_bias_constant_factor depth_bias_constant_factor{};
		vk::depth_bias_clamp depth_bias_clamp{};
		vk::depth_bias_slope_factor depth_bias_slope_factor{};
		vk::line_width line_width{ 1.0 };


		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_may_contain_decayed<vk::enable_depth_clamp>,
			types::are_may_contain_decayed<vk::enable_rasterizer_discard>,
			types::are_contain_one_decayed<vk::polygon_mode>,
			types::are_contain_one_decayed<vk::cull_mode>,
			types::are_contain_one_decayed<vk::front_face>,
			types::are_may_contain_one_decayed<vk::enable_depth_bias>,
			types::are_may_contain_one_decayed<vk::depth_bias_constant_factor>,
			types::are_may_contain_one_decayed<vk::depth_bias_clamp>,
			types::are_may_contain_one_decayed<vk::depth_bias_slope_factor>,
			types::are_may_contain_one_decayed<vk::line_width>
		>::for_types<Args...>
		pipeline_rasterization_state_create_info(Args&&... args) {
			polygon_mode = elements::decayed<vk::polygon_mode>(args...);
			cull_mode = elements::decayed<vk::cull_mode>(args...);
			front_face = elements::decayed<vk::front_face>(args...);

			if constexpr (
				types::are_contain_decayed<
					vk::enable_depth_clamp
				>::for_types<Args...>
			) {
				enable_depth_clamp = elements::decayed<
					vk::enable_depth_clamp
				>(args...);
			}

			if constexpr (
				types::are_contain_decayed<
					vk::enable_rasterizer_discard
				>::for_types<Args...>
			) {
				enable_rasterizer_discard = elements::decayed<
					vk::enable_rasterizer_discard
				>(args...);
			}

			if constexpr (
				types::are_contain_decayed<
					vk::enable_depth_bias
				>::for_types<Args...>
			) {
				enable_depth_bias = elements::decayed<
					vk::enable_depth_bias
				>(args...);
			}

			if constexpr (
				types::are_contain_decayed<
					vk::depth_bias_constant_factor
				>::for_types<Args...>
			) {
				depth_bias_constant_factor = elements::decayed<
					vk::depth_bias_constant_factor
				>(args...);
			}

			if constexpr (
				types::are_contain_decayed<
					vk::depth_bias_clamp
				>::for_types<Args...>
			) {
				depth_bias_clamp = elements::decayed<
					vk::depth_bias_clamp
				>(args...);
			}

			if constexpr (
				types::are_contain_decayed<
					vk::depth_bias_slope_factor
				>::for_types<Args...>
			) {
				depth_bias_slope_factor = elements::decayed<
					vk::depth_bias_slope_factor
				>(args...);
			}

			if constexpr (
				types::are_contain_decayed<vk::line_width>::for_types<Args...>
			) { line_width = elements::decayed<vk::line_width>(args...); }

		} // constructor

	}; // pipeline_rasterization_state_create_info

} // vk