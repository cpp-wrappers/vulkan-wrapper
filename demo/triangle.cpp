#if 0
pushd `dirname $0`
glslangValidator -e main -o ../build/triangle.vert.spv -V triangle.vert
bash build_and_run.sh triangle "-lglfw"
popd
exit 1
#endif

#include "vk/device_queue_create_info.hpp"
#include "vk/instance_create_info.hpp"
#include "vk/queue_family_index.hpp"
#include "vk/shader_module.hpp"
#include "vk/instance.hpp"
#include "vk/surface.hpp"
#include "vk/device.hpp"
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

	vk::physical_device& physical_device = instance.first_physical_device();
	vk::device& device = physical_device.create_device(
		vk::device_queue_create_info {
			vk::queue_family_index{ 0 },
			vk::queue_count{ 1 },
			vk::queue_priorities{ ps }
		}
	);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "Vulkan Triangle", NULL, NULL);
	if (!window) {
		std::cerr << "window creation failed" << std::endl;
		return -1;
	}

	vk::surface surface;
	if(glfwCreateWindowSurface((VkInstance)&instance, window, nullptr, &surface.m_surface) >= 0) {
		std::cout << "created surface" << std::endl;
	}
	else {
		std::cerr << "surface creation failed" << std::endl;
		return -1;
	}

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
}