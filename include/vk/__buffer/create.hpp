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
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<vk::buffer_create_flags> <= 1,
		count_of_decayed_same_as<vk::buffer_size> == 1,
		count_of_decayed_same_as<vk::buffer_usages> == 1,
		count_of_decayed_same_as<vk::sharing_mode> <= 1,
		count_of_range_of_decayed<vk::queue_family_index> <= 1
	>
	vk::expected<handle<vk::buffer>>
	try_create_buffer(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		vk::buffer_create_info ci {
			.size = a.template get_decayed_same_as<vk::buffer_size>(),
			.usage = a.template get_decayed_same_as<vk::buffer_usages>()
		};

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::sharing_mode> > 0
		) {
			ci.sharing_mode = a.template
				get_decayed_same_as<vk::sharing_mode>();
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::buffer_create_flags> > 0
		) {
			ci.flags = a.template
				get_decayed_same_as<vk::buffer_create_flags>();
		}

		if constexpr (types<Args...>::template
			count_of_range_of_decayed<vk::queue_family_index> > 0
		) {
			auto& queue_fanily_indices = a.template
				get_range_of_decayed<vk::queue_family_index>();

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

		if(result.error()) return result;

		return handle<vk::buffer>{ buffer };
	}

	template<typename... Args>
	handle<vk::buffer> create_buffer(Args&&... args) {
		vk::expected<handle<vk::buffer>> result
			= vk::try_create_buffer(forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk