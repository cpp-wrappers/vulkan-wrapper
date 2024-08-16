#pragma once

#include "./handle.hpp"
#include "./create_info.hpp"
#include "../__internal/function.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct create_buffer_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		const vk::buffer_create_info* create_info,
		const void* allocator,
		handle<vk::buffer>::underlying_type* buffer
	)> {
		static constexpr auto name = "vkCreateBuffer";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_convertible_to<handle<vk::instance>> == 1,
		is_convertible_to<handle<vk::device>> == 1,
		is_same_as<vk::buffer_create_flags>.decayed <= 1,
		is_same_as<vk::buffer_size>.decayed == 1,
		(
			is_same_as<vk::buffer_usages>.decayed == 1 ||
			is_same_as<vk::buffer_usage>.decayed > 0
		),
		is_same_as<vk::sharing_mode>.decayed <= 1,
		is_range_of<is_same_as<vk::queue_family_index>.decayed> <= 1
	>
	vk::expected<handle<vk::buffer>>
	try_create_buffer(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = (handle<vk::instance>) a.template
			get<is_convertible_to<handle<vk::instance>>>();

		handle<vk::device> device = (handle<vk::device>) a.template
			get<is_convertible_to<handle<vk::device>>>();

		vk::buffer_usages usages;

		if constexpr (
			(is_same_as<vk::buffer_usages>.decayed > 0).for_types<Args...>()
		) {
			usages = a.template get<is_same_as<vk::buffer_usages>.decayed>();
		}
		a.template pass<is_same_as<vk::buffer_usage>.decayed>(
			[&](auto... _usages) {
				(usages.set(_usages), ...);
			}
		);

		vk::buffer_create_info ci {
			.size = a.template get<is_same_as<vk::buffer_size>.decayed>(),
			.usage = usages
		};

		if constexpr (
			(is_same_as<vk::sharing_mode>.decayed > 0).for_types<Args...>()
		) {
			ci.sharing_mode = a.template
				get<is_same_as<vk::sharing_mode>.decayed>();
		}

		if constexpr (
			(is_same_as<vk::buffer_create_flags> > 0).for_types<Args...>()
		) {
			ci.flags = a.template
				get<is_same_as<vk::buffer_create_flags>.decayed>();
		}

		if constexpr (
			(is_range_of<is_same_as<vk::queue_family_index>.decayed> > 0)
			.for_types<Args...>()
		) {
			auto& queue_fanily_indices = a.template
				get<is_range_of<is_same_as<vk::queue_family_index>.decayed>>();

			ci.queue_family_index_count = queue_fanily_indices.size();
			ci.queue_fanily_indices = queue_fanily_indices.iterator();
		}

		handle<vk::buffer> buffer;

		vk::result result {
			vk::get_device_function<vk::create_buffer_function>(
				instance, device
			)(
				device.underlying(),
				&ci ,
				nullptr,
				&buffer.underlying()
			)
		};

		if (result.error()) return result;

		return handle<vk::buffer>{ buffer };
	}

	template<typename... Args>
	handle<vk::buffer> create_buffer(Args&&... args) {
		vk::expected<handle<vk::buffer>> result
			= vk::try_create_buffer(forward<Args>(args)...);
		if (result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk