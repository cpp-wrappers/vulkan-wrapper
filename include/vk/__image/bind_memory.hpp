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
		uint64 /*vk::device_size*/ memory_offset
	)> {
		static constexpr auto name = "vkBindImageMemory";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_convertible_to<handle<vk::instance>> == 1,
		is_convertible_to<handle<vk::device>> == 1,
		is_convertible_to<handle<vk::image>> == 1,
		is_convertible_to<handle<vk::device_memory>> == 1,
		is_same_as<vk::memory_offset>.decayed <= 1
	>
	[[nodiscard]] vk::result try_bind_image_memory(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = (handle<vk::instance>) a.template
			get<is_convertible_to<handle<vk::instance>>>();

		handle<vk::device> device = (handle<vk::device>) a.template
			get<is_convertible_to<handle<vk::device>>>();

		handle<vk::image> image = (handle<vk::image>) a.template
			get<is_convertible_to<handle<vk::image>>>();

		handle<vk::device_memory> device_memory = (handle<vk::device_memory>) a.template
			get<is_convertible_to<handle<vk::device_memory>>>();

		vk::memory_offset offset{ 0 };
		
		if constexpr (
			(is_same_as<vk::memory_offset>.decayed > 0).for_types<Args...>()
		) {
			offset = a.template get<is_same_as<vk::memory_offset>.decayed>();
		}

		return {
			vk::get_device_function<vk::bind_image_memory_function>(
				instance, device
			)(
				device.underlying(),
				image.underlying(),
				device_memory.underlying(),
				(uint64) offset
			)
		};
	} // try_bind_image_memory

	template<typename... Args>
	void bind_image_memory(Args&&... args) {
		vk::result result = vk::try_bind_image_memory(forward<Args>(args)...);
		if (result.error()) vk::unexpected_handler(result);
	}

} // vk