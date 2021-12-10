#include "../platform.hpp"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>

void platform::logger::string(const char* str, nuint length) const {
	fwrite(str, 1, length, (FILE*) raw);
	fflush((FILE*) raw);
}

void platform::logger::operator () (const char* str) const {
	fputs(str, (FILE*) raw);
	fflush((FILE*) raw);
}

void platform::logger::operator () (char c) const {
	fputc(c, (FILE*) raw);
	fflush((FILE*) raw);
}

namespace platform {
	logger info{ stdout };
	logger error{ stderr };
}

nuint platform::file_size(const char* path) {
	FILE* f = fopen(path, "rb");
	if(f == nullptr) {
		platform::error("couldn't open file: ", path, '\n');
		throw;
	}
	fseek(f, 0, SEEK_END);
	nuint size = ftell(f);
	fclose(f);
	return size;
}

void platform::read_file(const char* path, char* buff, nuint size) {
	FILE* f = fopen(path, "rb");
	if(f == nullptr) {
		platform::error("couldn't open file ", path, '\n');
		throw;
	}

	auto result = fread(buff, 1, size, f);
	fclose(f);

	if(result != size) {
		if (feof(f))
			platform::error("EOF");
		else if (ferror(f))
			platform::error("error");
		else
			platform::error("result != size");

		platform::error(" when reading file: ", path, ", buffer size: ", size, "read: ", result, '\n');
		throw;
	}
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
	glfwSetErrorCallback([](int error_code, const char* description) {
		platform::error("glfw error: ", description, '\n');
	});

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	window = glfwCreateWindow(640, 480, "Vulkan Clear", nullptr, nullptr);
	if (!window) {
		return c_string{ "window creation failed\n" };
	}

	VkSurfaceKHR surface;

	auto result = glfwCreateWindowSurface(
		(VkInstance) instance.handle,
		window,
		nullptr,
		(VkSurfaceKHR*) &surface
	);

	if(result < 0) {
		platform::info((uint32)result);
		platform::info("\n");
		return c_string{ "surface creation failed\n" };
	}

	return vk::surface{ surface };
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
	}
	else {
		platform::error("vulkan is not supported\n");
		return -1;
	}

	return entrypoint();
}