#pragma once

namespace vk {

	enum class debug_report_object_type {
		unknown                    = 0,
		instance                   = 1,
		physical_device            = 2,
		device                     = 3,
		queue                      = 4,
		semaphore                  = 5,
		command_buffer             = 6,
		fence                      = 7,
		device_memory              = 8,
		buffer                     = 9,
		image                      = 10,
		event                      = 11,
		query_pool                 = 12,
		buffer_view                = 13,
		image_view                 = 14,
		shader_module              = 15,
		pipeline_cache             = 16,
		pipeline_layout            = 17,
		render_pass                = 18,
		pipeline                   = 19,
		descriptor_set_layout      = 20,
		sampler                    = 21,
		descriptor_pool            = 22,
		descriptor_set             = 23,
		framebuffer                = 24,
		command_pool               = 25,
		surface                    = 26,
		swapchain                  = 27,
		debug_report_callback      = 28,
		display                    = 29,
		display_mode               = 30,
		validation_cache           = 33,
		sampler_ycbcr_conversion   = 1000156000,
		descriptor_update_template = 1000085000,
		cu_module                  = 1000029000,
		cu_function_nvx            = 1000029001,
		acceleration_structure     = 1000150000,
		acceleration_structure_nv  = 1000165000,
		buffer_collection_fuchsia  = 1000366000
	};

} // vk