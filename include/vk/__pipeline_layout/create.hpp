#pragma once

#include "./create_info.hpp"
#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/result.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"

namespace vk {

	struct create_pipeline_layout_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		const vk::pipeline_layout_create_info* create_info,
		const void* allocator,
		handle<vk::pipeline_layout>::underlying_type* pipeline_layout
	)> {
		static constexpr auto name = "vkCreatePipelineLayout";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_range_of<is_same_as<handle<vk::descriptor_set_layout>>.decayed> <= 1,
		is_range_of<is_same_as<vk::push_constant_range>.decayed> <= 1
	>
	vk::expected<handle<vk::pipeline_layout>>
	try_create_pipeline_layout(Args&&... args) {
		vk::pipeline_layout_create_info ci{};

		if constexpr (types<Args...>::template
			count_of<is_range_of<
				is_same_as<handle<vk::descriptor_set_layout>>.decayed
			>> > 0
		) {
			auto& layouts = tuple{ args... }.template
				get<is_range_of<
					is_same_as<handle<vk::descriptor_set_layout>>.decayed
				>>();
			ci.descriptor_set_layout_count = (uint32) layouts.size();
			ci.descriptor_set_layouts = layouts.iterator();
		}

		if constexpr (types<Args...>::template
			count_of<is_range_of<
				is_same_as<vk::push_constant_range>.decayed
			>> > 0
		) {
			auto& push_constant_ranges = tuple{ args... }.template
				get<is_range_of<
					is_same_as<vk::push_constant_range>.decayed
				>>();

			ci.push_constant_range_count =
				(uint32) push_constant_ranges.size();
			ci.push_constant_ranges = push_constant_ranges.iterator();
		}

		handle<vk::instance> instance = tuple{ args... }.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = tuple{ args... }.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::pipeline_layout> pipeline_layout;

		vk::result result {
			vk::get_device_function<vk::create_pipeline_layout_function>(
				instance, device
			)(
				device.underlying(),
				&ci,
				nullptr,
				&pipeline_layout.underlying()
			)
		};

		if(result.error()) return result;

		return pipeline_layout;
	}

	template<typename... Args>
	handle<vk::pipeline_layout> create_pipeline_layout(Args&&... args) {
		vk::expected<handle<vk::pipeline_layout>> result
			= vk::try_create_pipeline_layout(forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk