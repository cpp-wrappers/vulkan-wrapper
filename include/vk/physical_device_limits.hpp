export module vk.physical_device_limits;

export import <cinttypes>;
import vk_headers;
import <type_traits>;

static_assert(std::is_same_v<VkDeviceSize, uint64_t>);

export namespace vk {

struct physical_device_limits {
	uint32_t max_image_dimension_1d;
	uint32_t max_image_dimension_2d;
	uint32_t max_image_dimension_3d;
	uint32_t max_image_dimension_cube;
	uint32_t max_image_array_layers;
	uint32_t max_texel_buffer_elements;
	uint32_t max_uniform_buffer_range;
	uint32_t max_storage_buffer_range;
	uint32_t max_push_constants_size;
	uint32_t max_memory_allocation_count;
	uint32_t max_sampler_allocation_count;
	uint64_t buffer_image_granularity;
	uint64_t sparse_address_space_size;
	uint32_t max_bound_descriptor_sets;
	uint32_t max_per_stage_descriptor_samplers;
	uint32_t max_per_stage_descriptor_uniform_buffers;
	uint32_t max_per_stage_descriptor_storage_buffers;
	uint32_t max_per_stage_descriptor_sampled_images;
	uint32_t max_per_stage_descriptor_storage_images;
	uint32_t max_per_stage_descriptor_input_attachments;
	uint32_t max_per_stage_resources;
	uint32_t max_descriptor_set_samplers;
	uint32_t max_descriptor_set_uniform_buffers;
	uint32_t max_descriptor_set_uniform_buffers_dynamic;
	uint32_t max_descriptor_set_storage_buffers;
	uint32_t max_descriptor_set_storage_buffers_dynamic;
	uint32_t max_descriptor_set_sampled_images;
	uint32_t max_descriptor_set_storage_images;
	uint32_t max_descriptor_set_input_attachments;
	uint32_t max_vertex_input_attributes;
	uint32_t max_vertex_input_bindings;
	uint32_t max_vertex_input_attribute_offset;
	uint32_t max_vertex_input_binding_stride;
	uint32_t max_vertex_output_components;
	uint32_t max_tessellation_generation_level;
	uint32_t max_tessellation_patch_size;
	uint32_t max_tessellation_control_per_vertex_input_components;
	uint32_t max_tessellation_control_per_vertex_output_components;
	uint32_t max_tessellation_control_per_patch_output_components;
	uint32_t max_tessellation_control_total_output_components;
	uint32_t max_tessellation_evaluation_input_components;
	uint32_t max_tessellation_evaluation_output_components;
	uint32_t max_geometry_shader_invocations;
	uint32_t max_geometry_input_components;
	uint32_t max_geometry_output_components;
	uint32_t max_geometry_output_vertices;
	uint32_t max_geometry_total_output_components;
	uint32_t max_fragment_input_components;
	uint32_t max_fragment_output_attachments;
	uint32_t max_fragment_dual_src_attachments;
	uint32_t max_fragment_combined_output_resources;
	uint32_t max_compute_shared_memory_size;
	uint32_t max_compute_work_group_count[3];
	uint32_t max_compute_work_group_invocations;
	uint32_t max_compute_work_group_size[3];
	uint32_t sub_pixel_precision_bits;
	uint32_t sub_texel_precision_bits;
	uint32_t mipmap_precision_bits;
	uint32_t max_draw_indexed_index_value;
	uint32_t max_draw_indirect_count;
	float    max_sampler_lod_bias;
	float    max_sampler_anisotropy;
	uint32_t max_viewports;
	uint32_t max_viewport_dimensions[2];
	float    viewport_bounds_range[2];
	uint32_t viewport_sub_pixel_bits;
	size_t   min_memory_map_alignment;
	uint64_t min_texel_buffer_offset_alignment;
	uint64_t min_uniform_buffer_offset_alignment;
	uint64_t min_storage_buffer_offset_alignment;
	int32_t min_texel_offset;
	uint32_t max_texel_offset;
	int32_t min_texel_gather_offset;
	uint32_t max_texel_gather_offset;
	float min_interpolation_offset;
	float max_interpolation_offset;
	uint32_t sub_pixel_interpolation_offset_bits;
	uint32_t max_framebuffer_width;
	uint32_t max_framebuffer_height;
	uint32_t max_framebuffer_layers;
	uint32_t framebuffer_color_sample_counts;
	uint32_t framebuffer_depth_sample_counts;
	uint32_t framebuffer_stencil_sample_counts;
	uint32_t framebuffer_no_attachments_sample_counts;
	uint32_t max_color_attachments;
	uint32_t sampled_image_color_sample_counts;
	uint32_t sampled_image_integer_sample_counts;
	uint32_t sampled_image_depth_sample_counts;
	uint32_t sampled_image_stencil_sample_counts;
	uint32_t storage_image_sample_counts;
	uint32_t max_sample_mask_words;
	uint32_t timestamp_compute_and_graphics;
	float timestamp_period;
	uint32_t max_clip_distances;
	uint32_t max_cull_distances;
	uint32_t max_combined_clip_and_cull_distances;
	uint32_t discrete_queue_priorities;
	float point_size_range[2];
	float line_width_range[2];
	float point_size_granularity;
	float line_width_granularity;
	uint32_t strict_lines;
	uint32_t standard_sample_locations;
	uint64_t optimal_buffer_copy_offset_alignment;
	uint64_t optimal_buffer_copy_row_pitch_alignment;
	uint64_t non_coherent_atom_size;
};

}

static_assert(
	sizeof(vk::physical_device_limits)
	==
	sizeof(VkPhysicalDeviceLimits)
);