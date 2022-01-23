#include "vk/headers.hpp"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <png.h>

#include "../platform.hpp"

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
		abort();
	}
	fseek(f, 0, SEEK_END);
	nuint size = ftell(f);
	fclose(f);
	return size;
}

void platform::read_file(const char* path, span<char> buff) {
	FILE* f = fopen(path, "rb");
	if(f == nullptr) {
		platform::error("couldn't open file ", path, '\n');
		abort();
	}

	auto result = fread(buff.data(), 1, buff.size(), f);
	fclose(f);

	if(result != buff.size()) {
		if (feof(f))
			platform::error("EOF");
		else if (ferror(f))
			platform::error("error");
		else
			platform::error("result != size");

		platform::error(" when reading file: ", path, ", buffer size: ", buff.size(), "read: ", result, '\n');
		abort();
	}
}

platform::image_info platform::read_image_info(const char* path) {
	FILE* f = fopen(path, "rb");
	if(f == nullptr) {
		platform::error("couldn't open file: ", path, '\n');
		abort();
	}

	png_image image {
		.version = PNG_IMAGE_VERSION
	};

	if(!png_image_begin_read_from_stdio(&image, f)) {
		abort();
	}

	fclose(f);

	return {
		.width = image.width,
		.height = image.height,
		.size = PNG_IMAGE_SIZE(image)
	};
}

void platform::read_image_data(const char* path, span<char> buffer) {
	FILE* f = fopen(path, "rb");
	if(f == nullptr) {
		platform::error("couldn't open file: ", path, '\n');
		abort();
	}

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if(!png_ptr) {
		error("couldn't create png_structp").new_line(); abort();
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if(!info_ptr) {
		error("couldn't create png_infop").new_line(); abort();
	}

	png_init_io(png_ptr, f);

	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, nullptr);

	auto rows = png_get_rows(png_ptr, info_ptr);

	for(unsigned r = 0; r < png_get_image_height(png_ptr, info_ptr); ++r) {
		for(unsigned x = 0; x < png_get_rowbytes(png_ptr, info_ptr); ++x) {
			buffer[png_get_rowbytes(png_ptr, info_ptr) * r + x] = rows[r][x];
		}
	}

	fclose(f);

	png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
}

span<vk::extension_name> platform::get_required_instance_extensions() {
	uint32 count;
	glfwGetRequiredInstanceExtensions(&count);

	uint32 ignore;
	return {
		(vk::extension_name*) glfwGetRequiredInstanceExtensions(&ignore),
		count
	};
}

GLFWwindow* window;

vk::guarded_handle<vk::surface> platform::create_surface(vk::handle<vk::instance> instance) {
	glfwSetErrorCallback([](int error_code, const char* description) {
		platform::error("[glfw] error code: ", uint32(error_code), ", description: ", description).new_line();
	});

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	window = glfwCreateWindow(640, 640, "Vulkan", nullptr, nullptr);

	if (!window) {
		platform::error("window creation failed").new_line();
		abort();
	}

	VkSurfaceKHR surface;

	auto result = glfwCreateWindowSurface(
		(VkInstance) vk::get_handle_value(instance),
		window,
		nullptr,
		(VkSurfaceKHR*) &surface
	);

	if(result < 0) {
		platform::error("surface creation failed").new_line();
		abort();
	}

	return { vk::handle<vk::surface>{ (uint64) surface }, instance };
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
		abort();
	}

	if(!glfwVulkanSupported()) {
		platform::error("vulkan is not supported").new_line();
		abort();
	}

	entrypoint();
	return 0;
}