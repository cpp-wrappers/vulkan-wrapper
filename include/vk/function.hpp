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

typedef void (VK_PTR* PFN_vkVoidFunction)(void);