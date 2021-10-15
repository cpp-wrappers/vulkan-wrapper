#if 0
pushd `dirname $0`
glslangValidator -e main -o ../build/triangle.vert.spv -V triangle.vert
bash build_and_run.sh triangle "-lglfw"
popd
exit 1
#endif

#include "vk/instance/create.hpp"
#include "vk/instance/instance.hpp"

#include "vk/shader/module/create.hpp"

#include "vk/device/create.hpp"

#include "vk/swapchain/create.hpp"

#include "vk/render_pass/create.hpp"

#include "vk/surface/format.hpp"

#include <GLFW/glfw3.h>

#include <stdio.h>

vk::shader_module& read_shader_module(vk::device& device, const char* path) {
	FILE* f = fopen(path, "r");
	fseek(f, 0, SEEK_END);
	primitive::uint size = ftell(f);
	fseek(f, 0, SEEK_SET);

	char src[size];

	fread(src, 1, size, f);
	fclose(f);

	return create_shader_module(
		device,
		vk::code_size{ (uint32_t) size },
		vk::code{ (uint32_t*) src }
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
	primitive::uint32 count;
	const char** extensions = glfwGetRequiredInstanceExtensions(&count);
	while(count > 0) {
		printf("%s", extensions[--count]);
	}

	vk::instance& instance = vk::create_instance(
		array {
			vk::enabled_layer_name{ "VK_LAYER_KHRONOS_validation" }
		},
		array {
			vk::enabled_extension_name{ extensions[0] },
			vk::enabled_extension_name{ extensions[1] } // TODO
		}
	);

	float ps[1]{ 1.0F };

	vk::physical_device& physical_device = instance.first_physical_device();
	vk::device& device = vk::create_device(
		physical_device,
		array {
			vk::device_queue_create_info {
				vk::queue_family_index{ 0u },
				vk::queue_count{ 1u },
				vk::queue_priorities{ ps }
			}
		},
		array {
			vk::enabled_extension_name {
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

	vk::surface* surface_ptr;
	if(glfwCreateWindowSurface(
		(VkInstance)&instance,
		window,
		nullptr,
		(VkSurfaceKHR*)&surface_ptr
	) >= 0) {
		printf("created surface\n");
	}
	else {
		fprintf(stderr, "surface creation failed\n");
		return -1;
	}

	vk::surface& surface = *surface_ptr;

	if(!physical_device.get_surface_support(vk::queue_family_index{ 0u }, surface)) {
		fprintf(stderr, "surface is not supported by physical device, queue family index 0\n");
		return -1;
	}

	vk::surface_format surface_format;

	physical_device.view_surface_formats(*surface_ptr, [&](auto& formats) {
		surface_format = formats.front();
	});

	vk::render_pass& render_pass = vk::create_render_pass(
		device,
		array{
			vk::attachment_description {
				vk::format::r8_g8_b8_a8_unorm,
				vk::load_op{ vk::attachment_load_op::clear },
				vk::store_op{ vk::attachment_store_op::store },
				vk::final_layout{ vk::image_layout::color_attachment_optimal }
			},
		},
		array{ vk::subpass_description {} }
	);

	vk::queue_family_index queue_family_indices[]{ 0u };

	vk::surface_capabilities surface_caps = physical_device.get_surface_capabilities(*surface_ptr);

	vk::swapchain& swapchain = vk::create_swapchain(
		device,
		surface,
		vk::min_image_count{ surface_caps.min_image_count },
		surface_format.format,
		surface_format.color_space,
		vk::extent<2u>{ 640u, 480u },
		vk::image_usage::color_attachment,
		vk::sharing_mode::exclusive,
		vk::queue_family_index_count{ 0u },
		vk::queue_family_indices{ nullptr },
		vk::present_mode::immediate,
		vk::clipped{ 1u },
		vk::surface_transform::identity,
		vk::composite_alpha::opaque
	);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
}