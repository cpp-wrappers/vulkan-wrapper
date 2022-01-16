#include <string.h>
#include <stdlib.h>

#include <android/looper.h>
#include <android/native_app_glue/android_native_app_glue.h>
#include <android/asset_manager.h>
#include <android/native_activity.h>
#include <android/log.h>
#include <android/native_window.h>

#include <spng.h>

#include "vk/shared/headers.hpp"
#include "vulkan/vulkan_android.h"

#include "../platform.hpp"

struct message_buffer {
	int prio;
	static constexpr nuint buf_size = 256;
	char buf[buf_size]{ 0 };
	nuint size = 0;

	void add(const char* str, nuint length) {
		while(length-- > 0) {
			char ch = str[0];
			++str;

			if(ch == '\n') {
				if(size >= buf_size) abort();
				buf[size] = 0;
				__android_log_write(prio, "vulkan", buf);
				size = 0;
			}
			else {
				if(size >= buf_size - 1) abort();
				buf[size++] = ch;
			}
		}
	}

	void add(const char* str) {
		while(char ch = *(str++)) {
			if(ch == '\n') {
				if(size >= buf_size) abort();
				buf[size] = 0;
				__android_log_write(prio, "vulkan", buf);
				size = 0;
			}
			else {
				if(size >= buf_size - 1) abort();
				buf[size++] = ch;
			}
		}
	}
};

static message_buffer info_message_buffer{ ANDROID_LOG_INFO };
static message_buffer error_message_buffer{ ANDROID_LOG_ERROR };

const platform::logger& platform::logger::string(const char* str, nuint length) const {
	((message_buffer*)raw)->add(str, length);
	return *this;
}

const platform::logger& platform::logger::operator () (const char* str) const {
	((message_buffer*)raw)->add(str);
	return *this;
}

const platform::logger& platform::logger::operator () (char ch) const {
	((message_buffer*)raw)->add(&ch, 1);
	return *this;
}

namespace platform {
	logger info { &info_message_buffer };
	logger error { &error_message_buffer };
}

static android_app* app;

nuint platform::file_size(const char* path) {
	AAsset* asset = AAssetManager_open(app->activity->assetManager, path, AASSET_MODE_BUFFER);
	auto size = AAsset_getLength(asset);
	AAsset_close(asset);
	return size;
}

void platform::read_file(const char* path, span<char> buff) {
	AAsset* asset = AAssetManager_open(app->activity->assetManager, path, AASSET_MODE_BUFFER);
	char* asset_buff = (char*) AAsset_getBuffer(asset);
	memcpy(buff.data(), asset_buff, buff.size());
	AAsset_close(asset);
}

platform::image_info platform::read_image_info(const char *path) {
	auto file_size = platform::file_size(path);
	char storage[file_size];
	span buff{ storage, file_size };

	read_file(path, buff);

	spng_ctx *ctx = spng_ctx_new(0);
	spng_set_png_buffer(ctx, buff.data(), buff.size());

	spng_ihdr ihdr;
	if(spng_get_ihdr(ctx, &ihdr)) {
		platform::error("couldn't get ihdr").new_line();
		abort();
	}

	nuint size;
	spng_decoded_image_size(ctx, SPNG_FMT_RGBA8, &size);

	spng_ctx_free(ctx);

	return {
		.width = (uint32) ihdr.width,
		.height = (uint32) ihdr.height,
		.size = size
	};
}

void platform::read_image_data(const char *path, span<char> buff) {
	auto file_size = platform::file_size(path);
	char storage[file_size];
	span file_buff{ storage, file_size };

	read_file(path, file_buff);

	spng_ctx *ctx = spng_ctx_new(0);
	spng_set_png_buffer(ctx, file_buff.data(), file_buff.size());

	//spng_ihdr ihdr;
	//if(spng_get_ihdr(ctx, &ihdr)) {
	//	platform::error("couldn't get ihdr").new_line();
	//	abort();
	//}

	//nuint size;
	//spng_decoded_image_size(ctx, SPNG_FMT_RGBA8, &size);

	spng_decode_image(ctx, buff.data(), buff.size(), SPNG_FMT_RGBA8, 0);

	spng_ctx_free(ctx);
}

static array<vk::extension_name, 2> required_instance_extensions{ "VK_KHR_surface", "VK_KHR_android_surface" };

span<vk::extension_name> platform::get_required_instance_extensions() { return span{ required_instance_extensions.data(), required_instance_extensions.size() }; }

vk::guarded_handle<vk::surface> platform::create_surface(vk::handle<vk::instance> instance) {

	VkAndroidSurfaceCreateInfoKHR ci {
		.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR,
		.window = app->window
	};

	vk::handle<vk::surface> surface;

	VkResult result = vkCreateAndroidSurfaceKHR(
		(VkInstance) vk::get_handle_value(instance),
		&ci,
		nullptr,
		(VkSurfaceKHR*) &surface
	);

	if(result != VK_SUCCESS) {
		error("couldn't create surface").new_line();
		abort();
	}

	return { surface, instance };
}

static void poll() {
	int identifier;
	int events;
	android_poll_source* source;

	while((identifier = ALooper_pollAll(0, nullptr, &events, (void**)&source)) >= 0) {
		if(source != nullptr) source->process(app, source);
		if(app->destroyRequested) return;
	}
}

bool platform::should_close() {
	return app->destroyRequested;
}

void platform::begin() {
	poll();
}

void platform::end() {} 

extern "C" void android_main(android_app* app) {
	::app = app;
	platform::info("starting\n");

	while(app->window == nullptr) {
		poll();
	}

	entrypoint();
}