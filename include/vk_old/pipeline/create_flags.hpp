#pragma once

#include <core/flag_enum.hpp>

namespace vk {

	enum class pipeline_create_flag {
		disable_optimization                           = 0x00000001,
		allow_derivatives                              = 0x00000002,
		derivative                                     = 0x00000004,
		view_index_from_device_index                   = 0x00000008,
		dispatch_base                                  = 0x00000010,
		fail_on_pipeline_compile_required              = 0x00000100,
		early_return_on_failure                        = 0x00000200,
		rendering_fragment_shading_rate_attachment     = 0x00200000,
		rendering_fragment_density_map_attachment      = 0x00400000,
		ray_tracing_no_null_any_hit_shaders            = 0x00004000,
		ray_tracing_no_null_closest_hit_shaders        = 0x00008000,
		ray_tracing_no_null_miss_shaders               = 0x00010000,
		ray_tracing_no_null_intersection_shaders       = 0x00020000,
		ray_tracing_skip_triangles                     = 0x00001000,
		ray_tracing_skip_aabbs                         = 0x00002000,
		ray_tracing_shader_group_handle_capture_replay = 0x00080000,
		defer_compile                                  = 0x00000020,
		capture_statistics                             = 0x00000040,
		capture_internal_representations               = 0x00000080,
		indirect_bindable                              = 0x00040000,
		library                                        = 0x00000800,
		ray_tracing_allow_motion                       = 0x00100000
	};

	using pipeline_create_flags = flag_enum<vk::pipeline_create_flag>;

} // vk