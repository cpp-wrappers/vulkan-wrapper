#pragma once

#include "../__internal/function.hpp"
#include "../__device/handle.hpp"
#include "../__pipeline_layout/handle.hpp"

namespace vk {

	struct destroy_pipeline_layout_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::pipeline_layout>::underlying_type pipeline_layout,
		const void* allocator
	)> {
		static constexpr auto name = "vkDestroyPipelineLayout";
	};

	template<typename... Args>
	void destroy_pipeline_layout(Args&&... args) {
		handle<vk::instance> instance = tuple{ args... }.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = tuple{ args... }.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::pipeline_layout> layout = tuple{ args... }.template
			get_decayed_same_as<handle<vk::pipeline_layout>>();

		vk::get_device_function<vk::destroy_pipeline_layout_function>(
			instance, device
		)(
			device.underlying(), layout.underlying(), nullptr
		);
	}

} // vk