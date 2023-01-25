#pragma once

#include "../__internal/function.hpp"
#include "../__device/handle.hpp"
#include "../__descriptor_pool/handle.hpp"

namespace vk {

	struct destroy_descriptor_pool_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::descriptor_pool>::underlying_type descriptor_pool,
		const void* allocator
	)> {
		static constexpr auto name = "vkDestroyDescriptorPool";
	};

	inline void destroy_descriptor_pool(
		handle<vk::instance> instance,
		handle<vk::device> device,
		handle<vk::descriptor_pool> descriptor_pool
	) {
		vk::get_device_function<vk::destroy_descriptor_pool_function>(
			instance, device
		)(
			device.underlying(), descriptor_pool.underlying(), nullptr
		);
	}

} // vk