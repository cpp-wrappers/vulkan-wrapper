#pragma once

#include "./handle.hpp"
#include "./create_info.hpp"
#include "../__internal/function.hpp"
#include "../__internal/result.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"

#include <tuple.hpp>

namespace vk {

	struct create_buffer_view_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		const vk::buffer_view_create_info* create_info,
		const void* allocator,
		handle<vk::buffer_view>::underlying_type* view
	)> {
		static constexpr auto name = "vkCreateBufferView";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::buffer>> == 1,
		count_of_decayed_same_as<vk::format> == 1,
		count_of_decayed_same_as<vk::memory_offset> == 1,
		count_of_decayed_same_as<vk::memory_size> == 1
	>
	vk::expected<handle<vk::buffer_view>>
	try_create_buffer_view(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::buffer> buffer = a.template
			get_decayed_same_as<handle<vk::buffer>>();

		vk::format format = a.template get_decayed_same_as<vk::format>();
		vk::memory_offset offset = a.template
			get_decayed_same_as<vk::memory_offset>();
		vk::memory_size size = a.template
			get_decayed_same_as<vk::memory_size>();

		vk::buffer_view_create_info ci {
			.buffer = buffer,
			.format = format,
			.offset = offset,
			.size = size
		};

		handle<vk::buffer_view> buffer_view;

		vk::result result {
			vk::get_device_function<vk::create_buffer_view_function>(
				instance, device
			)(
				device.underlying(),
				&ci,
				nullptr,
				&buffer_view.underlying()
			)
		};

		if(result.error()) return result;

		return handle<vk::buffer_view>{ buffer_view };
	}

	template<typename... Args>
	handle<vk::buffer_view> create_buffer(Args&&... args) {
		vk::expected<handle<vk::buffer_view>> result
			= vk::try_create_buffer_view(forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk