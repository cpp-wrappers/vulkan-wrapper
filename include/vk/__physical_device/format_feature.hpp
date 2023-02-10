#pragma once

#include <enum_flags.hpp>

namespace vk {

	enum class format_feature {
		sampled_image_bit = 0x00000001,
		storage_image_bit = 0x00000002,
		storage_image_atomic_bit = 0x00000004,
		uniform_texel_buffer_bit = 0x00000008,
		storage_texel_buffer_bit = 0x00000010,
		storage_texel_buffer_atomic_bit = 0x00000020,
		vertex_buffer_bit = 0x00000040,
		color_attachment_bit = 0x00000080,
		color_attachment_blend_bit = 0x00000100,
		depth_stencil_attachment_bit = 0x00000200,
		blit_src_bit = 0x00000400,
		blit_dst_bit = 0x00000800,
		sampled_image_filter_linear_bit = 0x00001000,
		transfer_src_bit = 0x00004000,
		transfer_dst_bit = 0x00008000,
		midpoint_chroma_samples_bit = 0x00020000,
		sampled_image_ycbcr_conversion_linear_filter_bit = 0x00040000,
		sampled_image_ycbcr_conversion_separate_reconstruction_filter_bit = 0x00080000,
		sampled_image_ycbcr_conversion_chroma_reconstruction_explicit_bit = 0x00100000,
		sampled_image_ycbcr_conversion_chroma_reconstruction_explicit_forceable_bit = 0x00200000,
		disjoint_bit = 0x00400000,
		cosited_chroma_samples_bit = 0x00800000,
		sampled_image_filter_minmax_bit = 0x00010000,
		video_decode_output_bit_khr = 0x02000000,
		video_decode_dpb_bit_khr = 0x04000000,
		acceleration_structure_vertex_buffer_bit_khr = 0x20000000,
		sampled_image_filter_cubic_bit_ext = 0x00002000,
		fragment_density_map_bit_ext = 0x01000000,
		fragment_shading_rate_attachment_bit_khr = 0x40000000,
#ifdef VK_ENABLE_BETA_EXTENSIONS
		video_encode_input_bit_khr = 0x08000000,
#endif
#ifdef VK_ENABLE_BETA_EXTENSIONS
		video_encode_dpb_bit_khr = 0x10000000,
#endif
		sampled_image_filter_cubic_bit_img = sampled_image_filter_cubic_bit_ext,
		transfer_src_bit_khr = transfer_src_bit,
		transfer_dst_bit_khr = transfer_dst_bit,
		sampled_image_filter_minmax_bit_ext = sampled_image_filter_minmax_bit,
		midpoint_chroma_samples_bit_khr = midpoint_chroma_samples_bit,
		sampled_image_ycbcr_conversion_linear_filter_bit_khr = sampled_image_ycbcr_conversion_linear_filter_bit,
		sampled_image_ycbcr_conversion_separate_reconstruction_filter_bit_khr = sampled_image_ycbcr_conversion_separate_reconstruction_filter_bit,
		sampled_image_ycbcr_conversion_chroma_reconstruction_explicit_bit_khr = sampled_image_ycbcr_conversion_chroma_reconstruction_explicit_bit,
		sampled_image_ycbcr_conversion_chroma_reconstruction_explicit_forceable_bit_khr = sampled_image_ycbcr_conversion_chroma_reconstruction_explicit_forceable_bit,
		disjoint_bit_khr = disjoint_bit,
		cosited_chroma_samples_bit_khr = cosited_chroma_samples_bit,
	}; // format_feature

	using format_features = enum_flags<vk::format_feature>;

} // vk