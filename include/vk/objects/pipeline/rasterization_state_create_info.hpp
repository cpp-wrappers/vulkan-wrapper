#pragma once

#include <core/wrapper/of_integer.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/are_may_contain_one_type.hpp>
#include <core/types/are_contain_one_type.hpp>
#include <core/types/are_contain_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/type/decay.hpp>

#include "../../shared/headers.hpp"
#include "../../shared/polygon_mode.hpp"
#include "../../shared/cull_mode.hpp"
#include "../../shared/front_face.hpp"

namespace vk {

	struct enable_depth_clamp : wrapper::of_integer<uint32, struct enable_depth_clamp_t> {};
	struct enable_rasterizer_discard : wrapper::of_integer<uint32, struct enable_rasterizer_discard_t> {};
	struct enable_depth_bias : wrapper::of_integer<uint32, struct enable_depth_bias_t> {};
	struct depth_bias_constant_factor : wrapper::of<float, struct depth_bias_constant_factor_t> {};
	struct depth_bias_clamp : wrapper::of<float, struct depth_bias_clamp_t> {};
	struct depth_bias_slope_factor : wrapper::of<float, struct depth_bias_slope_factor_t> {};
	struct line_width : wrapper::of<float, struct line_width_t> {};

	struct pipeline_rasterization_state_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		const void* const next{};
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
		requires types::are_exclusively_satsify_predicates<
			types::are_may_contain_one_type<vk::enable_depth_clamp>,
			types::are_may_contain_one_type<vk::enable_rasterizer_discard>,
			types::are_contain_one_type<vk::polygon_mode>,
			types::are_contain_one_type<vk::cull_mode>,
			types::are_contain_one_type<vk::front_face>,
			types::are_may_contain_one_type<vk::enable_depth_bias>,
			types::are_may_contain_one_type<vk::depth_bias_constant_factor>,
			types::are_may_contain_one_type<vk::depth_bias_clamp>,
			types::are_may_contain_one_type<vk::depth_bias_slope_factor>,
			types::are_may_contain_one_type<vk::line_width>
		>::for_types_of<decay<Args>...>
		pipeline_rasterization_state_create_info(Args&&... args) {
			polygon_mode = elements::of_type<vk::polygon_mode>(args...);
			cull_mode = elements::of_type<vk::cull_mode>(args...);
			front_face = elements::of_type<vk::front_face>(args...);

			if constexpr(types::are_contain_type<vk::enable_depth_clamp>::for_types_of<decay<Args>...>)
				enable_depth_clamp = elements::of_type<vk::enable_depth_clamp>(args...);
			if constexpr(types::are_contain_type<vk::enable_rasterizer_discard>::for_types_of<decay<Args>...>)
				enable_rasterizer_discard = elements::of_type<vk::enable_rasterizer_discard>(args...);
			if constexpr(types::are_contain_type<vk::enable_depth_bias>::for_types_of<decay<Args>...>)
				enable_depth_bias = elements::of_type<vk::enable_depth_bias>(args...);
			if constexpr(types::are_contain_type<vk::depth_bias_constant_factor>::for_types_of<decay<Args>...>)
				depth_bias_constant_factor = elements::of_type<vk::depth_bias_constant_factor>(args...);
			if constexpr(types::are_contain_type<vk::depth_bias_clamp>::for_types_of<decay<Args>...>)
				depth_bias_clamp = elements::of_type<vk::depth_bias_clamp>(args...);
			if constexpr(types::are_contain_type<vk::depth_bias_slope_factor>::for_types_of<decay<Args>...>)
				depth_bias_slope_factor = elements::of_type<vk::depth_bias_slope_factor>(args...);
			if constexpr(types::are_contain_type<vk::line_width>::for_types_of<decay<Args>...>)
				line_width = elements::of_type<vk::line_width>(args...);
		}
	};

} // vk

static_assert(sizeof(vk::pipeline_rasterization_state_create_info) == sizeof(VkPipelineRasterizationStateCreateInfo));