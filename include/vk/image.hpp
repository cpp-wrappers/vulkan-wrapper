export module vk.image;

import vk_headers;
export import <cinttypes>;
export import <type_traits>;
export import <cxx_util/int.hpp>;
export import vk.format;
export import vk.extent;


namespace vk {

export enum class image_create_flag {
	sparse_binding = 0x00000001,
	sparse_residency = 0x00000002,
	sparse_aliased = 0x00000004,
	mutable_format = 0x00000008,
	cube_compatible = 0x00000010,
	alias = 0x00000400,
	split_instance_bind_regions = 0x00000040,
	_2d_array_compatible = 0x00000020,
	block_texel_view_compatible = 0x00000080,
	extended_usage = 0x00000100,
	_protected = 0x00000800,
	disjoint = 0x00000200,
	sorner_sampled_nv = 0x00002000,
	sample_locations_compatible_peth_ext = 0x00001000,
	subsampled_ext = 0x00004000,
};

export struct mip_levels : u::integral_like<uint32_t> {};
export struct array_layers : u::integral_like<uint32_t> {};
export struct sample_count : u::integral_like<uint32_t> {};

export enum class image_tiling {
	optimal, linear
};

export enum class image_usage {
	transfer_src_bit = 0x00000001,
	transfer_dst_bit = 0x00000002,
	sampled_bit = 0x00000004,
	storage_bit = 0x00000008,
	color_attachment_bit = 0x00000010,
	depth_stencil_attachment_bit = 0x00000020,
	transient_attachment_bit = 0x00000040,
	input_attachment_bit = 0x00000080,
	fragment_density_map_bit_ext = 0x00000200,
	fragment_shading_rate_attachment_bit_khr = 0x00000100,
	invocation_mask_bit_huawei = 0x00040000,
	shading_rate_image_bit_nv = fragment_shading_rate_attachment_bit_khr
};

export enum class sharing_mode {
	exclusive, concurrent
};

export enum class image_layout {
	undefined = 0,
	general = 1,
	color_attachment_optimal = 2,
	depth_stencil_attachment_optimal = 3,
	depth_stencil_read_only_optimal = 4,
	shader_read_only_optimal = 5,
	transfer_src_optimal = 6,
	transfer_dst_optimal = 7,
	preinitialized = 8,
	depth_read_only_stencil_attachment_optimal = 1000117000,
	depth_attachment_stencil_read_only_optimal = 1000117001,
	depth_attachment_optimal = 1000241000,
	depth_read_only_optimal = 1000241001,
	stencil_attachment_optimal = 1000241002,
	stencil_read_only_optimal = 1000241003,
	present_src_khr = 1000001002,
	video_decode_dst_khr = 1000024000,
	shared_present_khr = 1000111000,
	fragment_density_map_optimal_ext = 1000218000,
	fragment_shading_rate_attachment_optimal_khr = 1000164003,
	read_only_optimal_khr = 1000314000,
	attachment_optimal_khr = 1000314001,
	depth_read_only_stencil_attachment_optimal_khr = depth_read_only_stencil_attachment_optimal,
	depth_attachment_stencil_read_only_optimal_khr = depth_attachment_stencil_read_only_optimal,
	shading_rate_optimal_nv = fragment_shading_rate_attachment_optimal_khr,
	depth_attachment_optimal_khr = depth_attachment_optimal,
	depth_read_only_optimal_khr = depth_read_only_optimal,
	stencil_attachment_optimal_khr = stencil_attachment_optimal,
	stencil_read_only_optimal_khr = stencil_read_only_optimal,
};

} // vk

void create_image(VkDevice device, VkImageCreateInfo ci, VkImage i) {
	VkCreateImage(
		device,
		&ci,
		nullptr,
		&i
	);
}

namespace vk {

export struct image {
	VkImage m_image;

	// TODO queue family indices
	template<typename... Args>
	image(Args&&... args) {
		create_image()
	}
};

}