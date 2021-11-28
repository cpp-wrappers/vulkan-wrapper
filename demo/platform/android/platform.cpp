#include <android/looper.h>
#include <android/native_app_glue/android_native_app_glue.h>
#include <android/asset_manager.h>
#include <android/native_activity.h>
#include <android/log.h>
#include <android/native_window.h>
#include <vulkan/vulkan_core.h>
#include <vulkan/vulkan_android.h>

#include "../platform.hpp"
#include <string.h>
#include <assert.h>

struct message_buffer {
	int prio;
	char buf[256]{ 0 };
	uint size = 0;

	void add(const char* str) {
		while(char ch = *(str++)) {
			assert(size < 256);

			if(ch == '\n') {
				buf[size] = 0;
				__android_log_write(prio, "vulkan", buf);
				size = 0;
			}
			else {
				buf[size++] = ch;
			}
		}
	}
};

static message_buffer info_message_buffer{ ANDROID_LOG_INFO };
static message_buffer error_message_buffer{ ANDROID_LOG_ERROR };

void platform::info(const char* str) {
	info_message_buffer.add(str);
}
void platform::error(const char* str) {
	error_message_buffer.add(str);
}

array<const char*, 2> required_instance_extensions{ "VK_KHR_surface", "VK_KHR_android_surface" };

nuint platform::required_instance_extension_count() { return required_instance_extensions.size(); }
const char** platform::get_required_instance_extensions() { return required_instance_extensions.data(); }

static android_app* app;

elements::one_of<c_string, vk::surface> platform::try_create_surface(vk::instance instance) {

	VkAndroidSurfaceCreateInfoKHR ci {
		.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR,
		.pNext = nullptr,
		.flags = 0,
		.window = app->window
	};

	vk::surface surface;

	VkResult result = vkCreateAndroidSurfaceKHR(
		(VkInstance) instance.handle,
		&ci,
		nullptr,
		(VkSurfaceKHR*) &surface
	);

	if(result != VK_SUCCESS) {
		return c_string{ "couldn't create android surface" };
	}

	return surface;
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