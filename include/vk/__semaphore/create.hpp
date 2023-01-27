#pragma once

#include "./handle.hpp"
#include "./create_info.hpp"
#include "../__internal/function.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"

namespace vk {

	struct create_semaphore_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		const vk::semaphore_create_info* create_info,
		const void* allocator,
		handle<vk::semaphore>::underlying_type* semaphore
	)> {
		static constexpr auto name = "vkCreateSemaphore";
	};

	inline vk::expected<handle<vk::semaphore>> try_create_semaphore(
		handle<vk::instance> instance,
		handle<vk::device> device
	) {
		vk::semaphore_create_info ci{};

		handle<vk::semaphore> semaphore;

		vk::result result {
			vk::get_device_function<vk::create_semaphore_function>(
				instance, device
			)(
				device.underlying(),
				&ci,
				nullptr,
				&semaphore.underlying()
			)
		};

		if(result.error()) return result;

		return semaphore;
	}

	template<typename... Args>
	handle<vk::semaphore> create_semaphore(Args&&... args) {
		vk::expected<handle<vk::semaphore>> result
			= vk::try_create_semaphore(forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk