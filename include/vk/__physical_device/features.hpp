#pragma once

#include <integer.hpp>
#include <type.hpp>

namespace vk {

	struct physical_device_features_marker {};

	static constexpr auto is_physical_device_features
		= is_base_of<physical_device_features_marker>;

	struct physical_device_features {
		uint32
			robust_buffer_access,
			full_draw_index_uint32,
			image_cube_array,
			independent_blend,
			geometry_shader,
			tessellation_shader,
			sample_rate_shading,
			dual_src_blend,
			logic_op,
			multi_draw_indirect,
			draw_indirect_first_instance,
			depth_clamp,
			depth_bias_clamp,
			fill_mode_non_solid,
			depth_bounds,
			wide_lines,
			large_points,
			alpha_to_one,
			multi_viewport,
			sampler_anisotropy,
			texture_compression_etc2,
			texture_compression_ast_cldr,
			texture_compression_bc,
			occlusion_query_precise,
			pipeline_statistics_query,
			vertex_pipeline_stores_and_atomics,
			fragment_stores_and_atomics,
			shader_tessellation_and_geometry_point_size,
			shader_image_gather_extended,
			shader_storage_image_extended_formats,
			shader_storage_image_multisample,
			shader_storage_image_read_without_format,
			shader_storage_image_write_without_format,
			shader_uniform_buffer_array_dynamic_indexing,
			shader_sampled_image_array_dynamic_indexing,
			shader_storage_buffer_array_dynamic_indexing,
			shader_storage_image_array_dynamic_indexing,
			shader_clip_distance,
			shader_cull_distance,
			shader_float64,
			shader_int64,
			shader_int16,
			shader_resource_residency,
			shader_resource_min_lod,
			sparse_binding,
			sparse_residency_buffer,
			sparse_residency_image_2d,
			sparse_residency_image_3d,
			sparse_residency_2_samples,
			sparse_residency_4_samples,
			sparse_residency_8_samples,
			sparse_residency_16_samples,
			sparse_residency_aliased,
			variable_multisample_rate,
			inherited_queries;
	};

} // vk