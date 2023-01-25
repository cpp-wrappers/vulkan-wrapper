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
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_range_of_decayed<handle<vk::descriptor_set_layout>> <= 1,
		count_of_range_of_decayed<vk::push_constant_range> <= 1
	>
	vk::expected<handle<vk::pipeline_layout>>
	try_create_pipeline_layout(Args&&... args) {
		vk::pipeline_layout_create_info ci{};

		if constexpr (types<Args...>::template
			count_of_range_of_decayed<handle<vk::descriptor_set_layout>> > 0
		) {
			auto& layouts = tuple{ args... }.template
				get_range_of_decayed<handle<vk::descriptor_set_layout>>();
			ci.descriptor_set_layout_count = (uint32) layouts.size();
			ci.descriptor_set_layouts = layouts.iterator();
		}

		if constexpr (types<Args...>::template
			count_of_range_of_decayed<vk::push_constant_range> > 0
		) {
			auto& push_constant_ranges = tuple{ args... }.template
				get_range_of_decayed<vk::push_constant_range>();

			ci.push_constant_range_count =
				(uint32) push_constant_ranges.size();
			ci.push_constant_ranges = push_constant_ranges.data();
		}

		handle<vk::instance> instance = tuple{ args... }.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = tuple{ args... }.template
			get_decayed_same_as<handle<vk::device>>();

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