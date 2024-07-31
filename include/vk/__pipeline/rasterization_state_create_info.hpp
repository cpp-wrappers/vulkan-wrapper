#pragma once

#include "../__internal/polygon_mode.hpp"
#include "../__internal/cull_mode.hpp"
#include "../__internal/front_face.hpp"

#include <integer.hpp>
#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct enable_depth_clamp         { uint32 _; };
	struct enable_rasterizer_discard  { uint32 _; };
	struct enable_depth_bias          { uint32 _; };
	struct depth_bias_constant_factor { uint32 _; };
	struct depth_bias_clamp           { uint32 _; };
	struct depth_bias_slope_factor    { uint32 _; };
	struct line_width                 { float _;  };

	struct pipeline_rasterization_state_create_info {
		uint32                         structure_type = 23;
		const void*                    next = nullptr;
		uint32                         flags{};
		vk::enable_depth_clamp         enable_depth_clamp{};
		vk::enable_rasterizer_discard  enable_rasterizer_discard{};
		vk::polygon_mode               polygon_mode;
		vk::cull_mode                  cull_mode;
		vk::front_face                 front_face;
		vk::enable_depth_bias          enable_depth_bias{};
		vk::depth_bias_constant_factor depth_bias_constant_factor{};
		vk::depth_bias_clamp           depth_bias_clamp{};
		vk::depth_bias_slope_factor    depth_bias_slope_factor{};
		vk::line_width                 line_width{ 1.0 };


		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			is_same_as<vk::enable_depth_clamp>.decayed <= 1,
			is_same_as<vk::enable_rasterizer_discard>.decayed <= 1,
			is_same_as<vk::polygon_mode>.decayed == 1,
			is_same_as<vk::cull_mode>.decayed == 1,
			is_same_as<vk::front_face>.decayed == 1,
			is_same_as<vk::enable_depth_bias>.decayed <= 1,
			is_same_as<vk::depth_bias_constant_factor>.decayed <= 1,
			is_same_as<vk::depth_bias_clamp>.decayed <= 1,
			is_same_as<vk::depth_bias_slope_factor>.decayed <= 1,
			is_same_as<vk::line_width>.decayed <= 1
		>
		pipeline_rasterization_state_create_info(Args&&... args) {
			tuple a{ args... };

			polygon_mode = a.template get<is_same_as<vk::polygon_mode>.decayed>();
			cull_mode = a.template get<is_same_as<vk::cull_mode>.decayed>();
			front_face = a.template get<is_same_as<vk::front_face>.decayed>();

			if constexpr (
				(is_same_as<vk::enable_depth_clamp>.decayed > 0)
				.for_types<Args...>()
			) {
				enable_depth_clamp = a.template
					get<is_same_as<vk::enable_depth_clamp>.decayed>();
			}

			if constexpr (
				(is_same_as<vk::enable_rasterizer_discard>.decayed > 0)
				.for_types<Args...>()
			) {
				enable_rasterizer_discard = a.template
					get<is_same_as<vk::enable_rasterizer_discard>.decayed>();
			}

			if constexpr (
				(is_same_as<vk::enable_rasterizer_discard>.decayed > 0)
				.for_types<Args...>()
			) {
				enable_rasterizer_discard = a.template
					get<is_same_as<vk::enable_rasterizer_discard>.decayed>();
			}

			if constexpr (
				(is_same_as<vk::depth_bias_constant_factor>.decayed > 0)
				.for_types<Args...>()
			) {
				enable_depth_clamp = a.template
					get<is_same_as<vk::depth_bias_constant_factor>.decayed>();
			}

			if constexpr (
				(is_same_as<vk::depth_bias_clamp>.decayed > 0)
				.for_types<Args...>()
			) {
				depth_bias_clamp = a.template
					get<is_same_as<vk::depth_bias_clamp>.decayed>();
			}

			if constexpr (
				(is_same_as<vk::depth_bias_slope_factor>.decayed > 0)
				.for_types<Args...>()
			) {
				depth_bias_slope_factor = a.template
					get<is_same_as<vk::depth_bias_slope_factor>.decayed>();
			}

			if constexpr (
				(is_same_as<vk::line_width>.decayed > 0)
				.for_types<Args...>()
			) {
				line_width = a.template get<is_same_as<vk::line_width>.decayed>();
			}

		} // constructor

	}; // pipeline_rasterization_state_create_info

} // vk