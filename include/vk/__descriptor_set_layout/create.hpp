#pragma once

#include "./handle.hpp"
#include "./create_info.hpp"
#include "../__internal/result.hpp"
#include "../__device/handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/unexpected_handler.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct create_descriptor_set_layout_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type                 device,
		const vk::descriptor_set_layout_create_info*        create_info,
		const void*                                         allocator,
		handle<vk::descriptor_set_layout>::underlying_type* set_layout
	)> {
		static constexpr auto name = "vkCreateDescriptorSetLayout";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<vk::descriptor_set_layout_create_flags>.decayed <= 1,
		is_range_of<is_same_as<vk::descriptor_set_layout_binding>.decayed> <= 1
	>
	expected<handle<vk::descriptor_set_layout>>
	try_create_descriptor_set_layout(Args&&... args) {
		tuple a{ args... };

		auto& bindings = a.template
			get<is_range_of<is_same_as<vk::descriptor_set_layout_binding>.decayed>>();

		vk::descriptor_set_layout_create_info ci {
			.binding_count = (uint32) bindings.size(),
			.bindings = bindings.iterator()
		};
		
		if constexpr (
			(is_same_as<vk::descriptor_set_layout_create_flags>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.flags = a.template
				get<is_same_as<vk::descriptor_set_layout_create_flags>.decayed>();
		}

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::descriptor_set_layout> descriptor_set_layout;

		vk::result result {
			vk::get_device_function<vk::create_descriptor_set_layout_function>(
				instance, device
			)(
				device.underlying(),
				&ci,
				nullptr,
				&descriptor_set_layout.underlying()
			)
		};

		if(result.error()) return result;

		return descriptor_set_layout;
	}

	template<typename... Args>
	handle<vk::descriptor_set_layout>
	create_descriptor_set_layout(Args&&... args) {
		vk::expected<handle<vk::descriptor_set_layout>> result
			= vk::try_create_descriptor_set_layout(forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk