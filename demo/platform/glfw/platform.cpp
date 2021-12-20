#include "../platform.hpp"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>

const platform::logger& platform::logger::string(const char* str, nuint length) const {
	fwrite(str, 1, length, (FILE*) raw);
	fflush((FILE*) raw);
	return *this;
}

const platform::logger& platform::logger::operator () (const char* str) const {
	fputs(str, (FILE*) raw);
	fflush((FILE*) raw);
	return *this;
}

const platform::logger& platform::logger::operator () (char c) const {
	fputc(c, (FILE*) raw);
	fflush((FILE*) raw);
	return *this;
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

span<vk::extension_name> platform::get_required_instance_extensions() {
	uint32 count;
	glfwGetRequiredInstanceExtensions(&count);

	uint32 ingnore;
	return {
		(vk::extension_name*) glfwGetRequiredInstanceExtensions(&ingnore),
		count
	};
}

GLFWwindow* window;

vk::surface_guard platform::create_surface(vk::instance instance) {
	glfwSetErrorCallback([](int error_code, const char* description) {
		platform::error("[glfw] error code: ", uint32(error_code), ", description: ", description).new_line();
	});

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	window = glfwCreateWindow(640, 640, "Vulkan Clear", nullptr, nullptr);

	if (!window) {
		platform::error("window creation failed").new_line();
		throw;
	}

	VkSurfaceKHR surface;

	auto result = glfwCreateWindowSurface(
		(VkInstance) instance.handle,
		window,
		nullptr,
		(VkSurfaceKHR*) &surface
	);

	if(result < 0) {
		platform::error("surface creation failed").new_line();
		throw;
	}

	return vk::surface_guard{ vk::surface{ surface }, instance };
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
		platform::info("glfw is initialised").new_line();
	}
	else {
		platform::error("glfw init failed").new_line();
		return -1;
	}

	if(glfwVulkanSupported()) {
	}
	else {
		platform::error("vulkan is not supported").new_line();
		return -1;
	}

	entrypoint();
}