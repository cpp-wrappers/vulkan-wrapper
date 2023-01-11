#pragma once

// from vk_platform.h

#if defined(_WIN32)
	#define VK_ATTR
	#define VK_CALL __stdcall
	#define VK_PTR VK_CALL
#elif defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH < 7
	#error "Vulkan is not supported for the 'armeabi' NDK ABI"
#elif defined(__ANDROID__) && defined(__ARM_ARCH) && __ARM_ARCH >= 7 && defined(__ARM_32BIT_STATE)
	#define VK_ATTR __attribute__((pcs("aapcs-vfp")))
	#define VK_CALL
	#define VK_PTR VK_ATTR
#else
	#define VK_ATTR
	#define VK_CALL
	#define VK_PTR
#endif

#include <handle.hpp>

namespace vk {

	template<typename Prototype>
	struct function {
		using prototype = Prototype;
	};

	struct instance;
	struct device;

	template<typename Function>
	struct get_global_function_t {
		typename Function::prototype operator () () const;
	};
	template<typename Function>
	static constexpr get_global_function_t<Function> get_global_function{};

	template<typename Function>
	struct get_instance_function_t {
		typename Function::prototype operator () (handle<vk::instance>) const;
	};
	template<typename Function>
	static constexpr get_instance_function_t<Function> get_instance_function{};

	/*template<typename Type>
	Type get_device_function(handle<vk::device>, const char* name);*/

}