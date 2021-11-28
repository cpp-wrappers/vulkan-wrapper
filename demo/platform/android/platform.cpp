#include <android/looper.h>
#include <android/native_app_glue/android_native_app_glue.h>
#include <android/asset_manager.h>
#include <android/native_activity.h>
#include <android/log.h>
#include <android/native_window.h>
#include <vulkan/vulkan_core.h>
#include <vulkan/vulkan_android.h>

#include "../platform.hpp"

void platform::info(const char* str) {
	__android_log_write(ANDROID_LOG_INFO, "vulkan", str);
}
void platform::error(const char* str) {
	__android_log_write(ANDROID_LOG_ERROR, "vulkan", str);
}

array<const char*, 2> required_instance_extensions{ "VK_KHR_surface", "VK_KHR_android_surface" };

nuint platform::required_instance_extension_count() { return required_instance_extensions.size(); }
const char** platform::get_required_instance_extensions() { return required_instance_extensions.data(); }

android_app* app;

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

void poll() {
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
	platform::info("starting");

	while(app->window == nullptr) {
		poll();
	}

	entrypoint();
}