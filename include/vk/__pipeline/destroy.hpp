#pragma once

#include "../__internal/function.hpp"
#include "../__device/handle.hpp"
#include "../__pipeline/handle.hpp"
#include "../__instance/handle.hpp"

namespace vk {

	struct destroy_pipeline_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::pipeline>::underlying_type pipeline,
		const void* allocator
	)> {
		static constexpr auto name = "vkDestroyPipeline";
	};

	inline void destroy_pipeline(
		handle<vk::instance> instance,
		handle<vk::device> device,
		handle<vk::pipeline> pipeline
	) {
		vk::get_device_function<vk::destroy_pipeline_function>(
			instance, device
		)(
			device.underlying(), pipeline.underlying(), nullptr
		);
	}

} // vk