#if 0
pushd `dirname $0`
glslangValidator -e main -o ../build/triangle.vert.spv -V triangle.vert
bash build_and_run.sh triangle "-lglfw"
popd
exit 1
#endif

#include "vk/surface_capabilities.hpp"
#include "vk/surface_format.hpp"
#include "vk/color_space.hpp"
#include "vk/extent.hpp"
#include "vk/image/usage.hpp"
#include "vk/sharing_mode.hpp"
#include "vk/swapchain_create_info.hpp"
#include "vk/device_queue_create_info.hpp"
#include "vk/queue_family_index.hpp"
#include "vk/shader_module.hpp"
#include "vk/instance.hpp"
#include "vk/surface.hpp"
#include "vk/device.hpp"
#include "vk/physical_device.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <ios>

vk::shader_module& read_shader_module(vk::device& device, const char* path) {
	auto size = std::filesystem::file_size(path);
	char src[size];

	std::ifstream{ path, std::ios::binary }.read(src, size);

	return device.create_shader_module(
		vk::code_size{ (uint32_t) size },
		vk::code{ (uint32_t*) src }
	);
}

int main() {
	if (!glfwInit()) {
		std::cerr << "glfw init failed" << std::endl;
		return -1;
	}

	if(glfwVulkanSupported()) {
		std::cout << "supported" << std::endl;
	}
	else {
		std::cerr << "vulkan isn't supported" << std::endl;
		return -1;
	}

	std::cout << "required extensions:" << std::endl;
	uint32_t count;
	const char** extensions = glfwGetRequiredInstanceExtensions(&count);
	while(count > 0) {
		std::cout << extensions[--count] << std::endl;
	}

	vk::instance& instance = vk::create_instance(
		vk::enabled_layer_name{ "VK_LAYER_KHRONOS_validation" },
		vk::enabled_extension_name{ extensions[0] },
		vk::enabled_extension_name{ extensions[1] } // TODO
	);

	float ps[1]{ 1.0F };

	const null_terminated_string_view<size_is::undefined> device_extensions[] {
		"VK_KHR_swapchain"
	};
	vk::physical_device& physical_device = instance.first_physical_device();
	vk::device& device = physical_device.create_device(
		vk::device_queue_create_info {
			vk::queue_family_index{ 0 },
			vk::queue_count{ 1 },
			vk::queue_priorities{ ps }
		},
		vk::enabled_extension_count{ 1 },
		vk::enabled_extension_names{ device_extensions }
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
		std::cerr << "window creation failed" << std::endl;
		return -1;
	}

	vk::surface* surface_ptr;
	if(glfwCreateWindowSurface(
		(VkInstance)&instance,
		window,
		nullptr,
		(VkSurfaceKHR*)&surface_ptr
	) >= 0) {
		std::cout << "created surface" << std::endl;
	}
	else {
		std::cerr << "surface creation failed" << std::endl;
		return -1;
	}

	vk::surface& surface = *surface_ptr;

	if(!physical_device.get_surface_support(vk::queue_family_index{ 0 }, surface)) {
		std::cerr << "surface is not supported by physical device, queue family index 0" << std::endl;
		return -1;
	}

	vk::surface_format surface_format;

	physical_device.view_surface_formats(*surface_ptr, [&](auto& formats) {
		surface_format = formats.front();
	});

	vk::render_pass& render_pass = device.create_render_pass(
		vk::attachment_description {
			vk::format::r8_g8_b8_a8_unorm,
			vk::load_op{ vk::attachment_load_op::clear },
			vk::store_op{ vk::attachment_store_op::store },
			vk::final_layout{ vk::image_layout::color_attachment_optimal }
		},
		vk::subpass_description {}
	);

	vk::queue_family_index queue_family_indices[]{ 0 };

	vk::surface_capabilities surface_caps = physical_device.get_surface_capabilities(*surface_ptr);

	vk::swapchain& swapchain = device.create_swapchain(
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
		vk::clipped{ true },
		vk::surface_transform::identity,
		vk::composite_alpha::opaque
	);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
}