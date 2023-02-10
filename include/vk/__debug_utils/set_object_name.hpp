#pragma once

#include "./object_name_info.hpp"
#include "../__internal/function.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"

namespace vk::debug_utils {

	struct set_object_name_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		const vk::debug_utils::object_name_info* name_info
	)> {
		static constexpr auto name = "vkSetDebugUtilsObjectNameEXT";
	};

	template<typename ObjectType>
	inline vk::result try_set_object_name(
		handle<vk::instance> instance,
		handle<vk::device> device,
		handle<ObjectType> handle,
		vk::debug_utils::object_name name
	) {
		object_name_info oni {
			.object_type = vk::object_type_t<ObjectType>::value,
			.object_handle = (uint64) handle.underlying(),
			.object_name = name
		};
		return {
			vk::get_device_function<vk::debug_utils::set_object_name_function>(
				instance, device
			)(
				device.underlying(),
				&oni
			)
		};
	}

	template<typename... Args>
	inline void set_object_name(Args&&... args) {
		vk::result result
			= vk::debug_utils::try_set_object_name(forward<Args>(args)...);
		if(result.error()) {
			vk::unexpected_handler(result);
		}
	}

}