#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__device/handle.hpp"

namespace vk {

	struct destroy_sampler_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::sampler>::underlying_type sampler,
		const void* allocator
	)> {
		static constexpr auto name = "vkDestroySampler";
	};

	inline void destroy_sampler(
		handle<vk::instance> instance,
		handle<vk::device> device,
		handle<vk::sampler> sampler
	) {
		vk::get_device_function<vk::destroy_sampler_function>(
			instance, device
		)(
			device.underlying(), sampler.underlying(), nullptr
		);
	}

} // vk