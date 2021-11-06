#if 0
pushd `dirname $0`
glslangValidator -e main -o ../build/triangle.vert.spv -V triangle.vert
glslangValidator -e main -o ../build/triangle.frag.spv -V triangle.frag
bash build_and_run.sh triangle "-lglfw"
popd
exit 1
#endif

#include "vk/instance.hpp"
#include "vk/device.hpp"
#include "vk/physical_device.hpp"
#include "vk/shader_module.hpp"
#include "vk/surface.hpp"
#include "vk/render_pass.hpp"
#include "vk/swapchain.hpp"
#include "vk/pipeline.hpp"

#include <core/array.hpp>

#include <GLFW/glfw3.h>

#include <stdio.h>

vk::shader_module read_shader_module(vk::device& device, const char* path) {
	FILE* f = fopen(path, "r");
	fseek(f, 0, SEEK_END);
	uint size = ftell(f);
	fseek(f, 0, SEEK_SET);

	char src[size];

	fread(src, 1, size, f);
	fclose(f);

	return device.create_shader_module(
		vk::code_size{ (uint32) size },
		vk::code{ (uint32*) src }
	);
}

int main() {
	if (!glfwInit()) {
		fprintf(stderr, "glfw init failed\n");
		return -1;
	}

	if(glfwVulkanSupported()) {
		printf("supported\n");
	}
	else {
		fprintf(stderr, "vulkan isn't supported\n");
		return -1;
	}

	printf("required extensions:\n");
	uint32 count;
	const char** extensions = glfwGetRequiredInstanceExtensions(&count);
	while(count > 0) {
		printf("%s\n", extensions[--count]);
	}
	fflush(stdout);

	vk::instance instance = vk::create_instance(
		array {
			vk::layer_name{ "VK_LAYER_KHRONOS_validation" }
		},
		array {
			vk::extension_name{ extensions[0] },
			vk::extension_name{ extensions[1] } // TODO
		}
	);

	float ps[1]{ 1.0F };

	vk::physical_device& physical_device = instance.get_first_physical_device();

	vk::device device = vk::create_device(
		physical_device,
		array {
			vk::queue_create_info {
				vk::queue_family_index{ 0u },
				vk::queue_count{ 1u },
				vk::queue_priorities{ ps }
			}
		},
		array {
			vk::extension_name {
				"VK_KHR_swapchain"
			}
		}
	);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window;
	window = glfwCreateWindow(
		640,
		480,
		"Vulkan Triangle",
		nullptr,
		nullptr
	);
	if (!window) {
		fprintf(stderr, "window creation failed\n");
		return -1;
	}

	VkSurfaceKHR surface_raw;

	if(glfwCreateWindowSurface(
		*((VkInstance*) &instance),
		window,
		nullptr,
		&surface_raw
	) >= 0) {
		printf("created surface\n");
	}
	else {
		fprintf(stderr, "surface creation failed\n");
		return -1;
	}

	vk::surface surface{ surface_raw, instance };

	if(!physical_device.get_surface_support(vk::queue_family_index{ 0u }, surface)) {
		fprintf(stderr, "surface is not supported by physical device, queue family index 0\n");
		return -1;
	}

	vk::surface_format surface_format;

	physical_device.view_surface_formats(surface, [&](auto formats) {
		surface_format = formats[0];
	});

	vk::render_pass render_pass = vk::create_render_pass(
		device,
		array{
			vk::attachment_description {
				surface_format.format,
				vk::load_op{ vk::attachment_load_op::clear },
				vk::store_op{ vk::attachment_store_op::store },
				vk::final_layout{ vk::image_layout::color_attachment_optimal }
			},
		},
		array{ vk::subpass_description {} }
	);

	vk::queue_family_index queue_family_indices[]{ 0u };

	vk::surface_capabilities surface_caps = physical_device.get_surface_capabilities(surface);

	vk::swapchain swapchain = vk::create_swapchain(
		device,
		surface,
		vk::min_image_count{ surface_caps.min_image_count },
		surface_format.format,
		surface_format.color_space,
		vk::extent<2>{ 640, 480 },
		vk::image_usage::color_attachment,
		vk::sharing_mode::exclusive,
		vk::queue_family_index_count{ 0 },
		vk::queue_family_indices{ nullptr },
		vk::present_mode::immediate,
		vk::clipped{ 1 },
		vk::surface_transform::identity,
		vk::composite_alpha::opaque
	);

	vk::pipeline_color_blend_attachment_state attachment_state {
		.color_write_mask{ vk::color_component::r, vk::color_component::g, vk::color_component::b, vk::color_component::a }
	};

	vk::shader_module vertex_module = read_shader_module(device, "triangle.vert.spv");
	vk::shader_module fragment_module = read_shader_module(device, "triangle.frag.spv");
	
	vk::pipeline_shader_stage_create_info vertex {
		.stage = vk::shader_stage::vertex,
		.module = vertex_module,
		.entry_point_name = "main"
	};

	vk::pipeline_shader_stage_create_info fragment {
		.stage = vk::shader_stage::fragment,
		.module = fragment_module,
		.entry_point_name = "main"
	};

	array dynamics {
		vk::dynamic_state::viewport,
		vk::dynamic_state::scissor
	};

	/*vk::pipeline_layout& pipeline_layout = vk::create_pipeline_layout(device);

	vk::pipeline pipeline = vk::create_graphics_pipeline(
		device,
		render_pass,
		vk::subpass{ 0u },
		pipeline_layout,
		array<vk::pipeline_shader_stage_create_info, 2u> { vertex, fragment },
		vk::pipeline_vertex_input_state_create_info {},
		vk::pipeline_input_assembly_state_create_info {
			.topology = vk::primitive_topology::triangle_list
		},
		vk::pipeline_rasterization_state_create_info {
			.cull_mode = vk::cull_mode::back,
			.front_face = vk::front_face::clockwise,
			.line_width = 1.0
		},
		vk::pipeline_color_blend_state_create_info {
			.attachment_count = 1u,
			.attachments = &attachment_state
		},
		vk::pipeline_viewport_state_create_info {
			.viewport_count = 1u,
			.scissor_count = 1u
		},
		vk::pipeline_depth_stencil_state_create_info{},
		vk::pipeline_multisample_state_create_info {
			.rasterization_samples = vk::sample_count{ 1u }
		},
		vk::pipeline_dynamic_state_create_info {
			.dynamic_state_count = (primitive::uint32)(primitive::uint) dynamics.size(),
			.dynamic_states = dynamics.data()
		}
	);

	vk::image_view* first_image_view;
	swapchain.view_images(device, 1u, [&](auto& images_view) {
		first_image_view = & vk::create_image_view(
			device,
			images_view.front(),
			surface_format.format,
			vk::image_subresource_range {
				vk::image_aspect_flag{ vk::image_aspect::color },
				vk::level_count{ 1u },
				vk::layer_count{ 1u }
			},
			vk::component_mapping {
				vk::r { (primitive::uint32) vk::component_swizzle::r },
				vk::g { (primitive::uint32) vk::component_swizzle::g },
				vk::b { (primitive::uint32) vk::component_swizzle::b },
				vk::a { (primitive::uint32) vk::component_swizzle::a }
			},
			vk::image_view_type::two_d
		);
	});
	
	array attachments{ first_image_view };

	vk::framebuffer& framebuffer = vk::create_framebuffer(
		device,
		render_pass,
		vk::attachment_count{ 1u },
		vk::attachments{ (const vk::image_view**)attachments.data() },
		vk::extent<3u> { 640u, 480u, 1u }
	);*/

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
}