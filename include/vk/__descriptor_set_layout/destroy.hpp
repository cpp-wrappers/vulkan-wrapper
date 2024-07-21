#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__device/handle.hpp"
#include "../__descriptor_set_layout/handle.hpp"

namespace vk {

	struct destroy_descriptor_set_layout_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::descriptor_set_layout>::underlying_type
			descriptor_set_layout,
		const void* allocator
	)> {
		static constexpr auto name = "vkDestroyDescriptorSetLayout";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::descriptor_set_layout>>.decayed == 1
	>
	void destroy_descriptor_set_layout(Args&&... args) {
		tuple a{ args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::descriptor_set_layout> set_layout = a.template
			get_decayed_same_as<handle<vk::descriptor_set_layout>>();

		vk::get_device_function<vk::destroy_descriptor_set_layout_function>(
			instance, device
		)(
			device.underlying(), set_layout.underlying(), (void*) nullptr
		);
	}

} // vk