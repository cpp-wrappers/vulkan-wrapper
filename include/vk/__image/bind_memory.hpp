#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__internal/result.hpp"
#include "../__internal/device_size.hpp"
#include "../__internal/memory_offset.hpp"
#include "../__device/handle.hpp"
#include "../__device_memory/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct bind_image_memory_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::image>::underlying_type image,
		handle<vk::device_memory>::underlying_type memory,
		vk::device_size memory_offset
	)> {
		static constexpr auto name = "vkBindImageMemory";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::image>> == 1,
		count_of_decayed_same_as<handle<vk::device_memory>> == 1,
		count_of_decayed_same_as<vk::memory_offset> <= 1
	>
	[[nodiscard]] vk::result try_bind_image_memory(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::image> image = a.template
			get_decayed_same_as<handle<vk::image>>();

		handle<vk::device_memory> device_memory = a.template
			get_decayed_same_as<handle<vk::device_memory>>();

		vk::memory_offset offset{ 0 };
		
		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::memory_offset> > 0
		) {
			offset = a.template get_decayed_same_as<vk::memory_offset>();
		}

		return {
			vk::get_device_function<vk::bind_image_memory_function>(
				instance, device
			)(
				device.underlying(),
				image.underlying(),
				device_memory.underlying(),
				offset
			)
		};
	} // try_bind_image_memory

	template<typename... Args>
	void bind_image_memory(Args&&... args) {
		vk::result result = vk::try_bind_image_memory(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk