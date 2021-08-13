export module vk.result;

import vk_headers;
export import <system_error>;
export import <string>;

export namespace vk {

inline struct error_category : std::error_category {

	const char* name() const noexcept override{
		return "vulkan";
	}

	std::string message(int condition) const override {
		switch(condition) {
			case VK_ERROR_OUT_OF_HOST_MEMORY :
				return "A host memory allocation has failed";
			case VK_ERROR_OUT_OF_DEVICE_MEMORY :
				return "A device memory allocation has failed";
			case VK_ERROR_INITIALIZATION_FAILED :
				return "Initialization of an object could not be completed for implementation-specific reasons";
			case VK_ERROR_DEVICE_LOST :
				return "The logical or physical device has been lost";
			case VK_ERROR_MEMORY_MAP_FAILED :
				return "Mapping of a memory object has failed";
			case VK_ERROR_LAYER_NOT_PRESENT :
				return "A requested layer is not present or could not be loaded";
			case VK_ERROR_EXTENSION_NOT_PRESENT :
				return "A requested extension is not supported";
			case VK_ERROR_FEATURE_NOT_PRESENT :
				return "A requested feature is not supported";
			case VK_ERROR_INCOMPATIBLE_DRIVER :
				return "The requested version of Vulkan is not supported by the driver or is otherwise incompatible for implementation-specific reasons";
			case VK_ERROR_TOO_MANY_OBJECTS :
				return "Too many objects of the type have already been created";
			case VK_ERROR_FORMAT_NOT_SUPPORTED :
				return "A requested format is not supported on this device";
			case VK_ERROR_FRAGMENTED_POOL :
				return "A pool allocation has failed due to fragmentation of the pool’s memory";
			case VK_ERROR_SURFACE_LOST_KHR :
				return "A surface is no longer available";
			case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR :
				return "The requested window is already in use by Vulkan or another API in a manner which prevents it from being used again";
			case VK_ERROR_OUT_OF_DATE_KHR :
				return "A surface has changed in such a way that it is no longer compatible with the swapchain, and further presentation requests using the swapchain will fail";
			case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR :
				return "The display used by a swapchain does not use the same presentable image layout, or is incompatible in a way that prevents sharing an image";
			case VK_ERROR_INVALID_SHADER_NV :
				return "One or more shaders failed to compile or link";
			case VK_ERROR_OUT_OF_POOL_MEMORY :
				return "A pool memory allocation has failed";
			case VK_ERROR_INVALID_EXTERNAL_HANDLE :
				return "An external handle is not a valid handle of the specified type";
			case VK_ERROR_FRAGMENTATION :
				return "A descriptor pool creation has failed due to fragmentation";
			case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS :
				return "A buffer creation or memory allocation failed because the requested address is not available";
			case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT :
				return "An operation on a swapchain created with VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT failed as it did not have exlusive full-screen access";
			case VK_ERROR_UNKNOWN :
				return "An unknown error has occurred";
		}
		return "";
	}
} error_category;

inline void throw_if_error(int result) {
	if(result < 0) {
		throw std::system_error{ result, error_category };
	}
}

}