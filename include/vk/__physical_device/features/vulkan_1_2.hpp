#pragma once

#include "../features.hpp"

namespace vk {

	struct physical_device_vulkan_1_2_features :
		vk::physical_device_features_marker
	{
		uint32 structure_type = 51;
		const void* next;
		uint32 sampler_mirror_clamp_to_edge;
		uint32 draw_indirect_count;
		uint32 storage_buffer8_bit_access;
		uint32 uniform_and_storage_buffer8_bit_access;
		uint32 storage_push_constant8;
		uint32 shader_buffer_int64_atomics;
		uint32 shader_shared_int64_atomics;
		uint32 shader_float16;
		uint32 shader_int8;
		uint32 descriptor_indexing;
		uint32 shader_input_attachment_array_dynamic_indexing;
		uint32 shader_uniform_texel_buffer_array_dynamic_indexing;
		uint32 shader_storage_texel_buffer_array_dynamic_indexing;
		uint32 shader_uniform_buffer_array_non_uniform_indexing;
		uint32 shader_sampled_image_array_non_uniform_indexing;
		uint32 shader_storage_buffer_array_non_uniform_indexing;
		uint32 shader_storage_image_array_non_uniform_indexing;
		uint32 shader_input_attachment_array_non_uniform_indexing;
		uint32 shader_uniform_texel_buffer_array_non_uniform_indexing;
		uint32 shader_storage_texel_buffer_array_non_uniform_indexing;
		uint32 descriptor_binding_uniform_buffer_update_after_bind;
		uint32 descriptor_binding_sampled_image_update_after_bind;
		uint32 descriptor_binding_storage_image_update_after_bind;
		uint32 descriptor_binding_storage_buffer_update_after_bind;
		uint32 descriptor_binding_uniform_texel_buffer_update_after_bind;
		uint32 descriptor_binding_storage_texel_buffer_update_after_bind;
		uint32 descriptor_binding_update_unused_while_pending;
		uint32 descriptor_binding_partially_bound;
		uint32 descriptor_binding_variable_descriptor_count;
		uint32 runtime_descriptor_array;
		uint32 sampler_filter_minmax;
		uint32 scalar_block_layout;
		uint32 imageless_framebuffer;
		uint32 uniform_buffer_standard_layout;
		uint32 shader_subgroup_extended_types;
		uint32 separate_depth_stencil_layouts;
		uint32 host_query_reset;
		uint32 timeline_semaphore;
		uint32 buffer_device_address;
		uint32 buffer_device_address_capture_replay;
		uint32 buffer_device_address_multi_device;
		uint32 vulkan_memory_model;
		uint32 vulkan_memory_model_device_scope;
		uint32 vulkan_memory_model_availability_visibility_chains;
		uint32 shader_output_viewport_index;
		uint32 shader_output_layer;
		uint32 subgroup_broadcast_dynamic_id;
	};

} // vk