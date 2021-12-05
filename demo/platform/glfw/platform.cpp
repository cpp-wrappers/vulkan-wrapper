#include "../platform.hpp"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>

void print(const char* str, FILE* file) {
	fwrite(str, strlen(str), 1, file);
	fflush(file);
}

void platform::info(const char* str) {
	print(str, stdout);
}

void platform::error(const char* str) {
	print(str, stderr);
}

nuint platform::file_size(const char* path) {
	FILE* f = fopen(path, "r");
	if(f == nullptr) {
		platform::error("couldn't open file ");
		platform::error(path);
		platform::error("\n");

		throw;
	}
	fseek(f, 0, SEEK_END);
	nuint size = ftell(f);
	fclose(f);
	return size;
}

void platform::read_file(const char* path, char* buff, nuint size) {
	FILE* f = fopen(path, "r");
	if(f == nullptr) {
		platform::error("couldn't open file ");
		platform::error(path);
		platform::error("\n");

		throw;
	}

	fread(buff, 1, size, f);
	fclose(f);
}

nuint platform::required_instance_extension_count() {
	uint32 count;
	glfwGetRequiredInstanceExtensions(&count);
	return count;
}

const char** platform::get_required_instance_extensions() {
	uint32 ingnore;
	return glfwGetRequiredInstanceExtensions(&ingnore);
}

GLFWwindow* window;

elements::one_of<c_string, vk::surface> platform::try_create_surface(vk::instance instance) {
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	window = glfwCreateWindow(640, 480, "Vulkan Clear", nullptr, nullptr);
	if (!window) {
		return c_string{ "window creation failed\n" };
	}

	vk::surface surface;

	if(glfwCreateWindowSurface(
		(VkInstance) instance.handle,
		window,
		nullptr,
		(VkSurfaceKHR*) &surface.handle
	) < 0) {
		return c_string{ "surface creation failed\n" };
	}

	return surface;
}

bool platform::should_close() {
	return glfwWindowShouldClose(window);
}

void platform::begin() {}

void platform::end() {
	glfwPollEvents();
} 

int main() {
	if (glfwInit()) {
		platform::info("glfw is initialised\n");
	}
	else {
		platform::error("glfw init failed\n");
		return -1;
	}

	if(glfwVulkanSupported()) {
		//platform::info("vulkan is supported\n");
	}
	else {
		platform::error("vulkan is not supported\n");
		return -1;
	}

	return entrypoint();
}