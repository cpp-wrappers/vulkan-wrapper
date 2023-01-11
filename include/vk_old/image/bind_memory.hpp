#pragma once

#include "handle.hpp"

#include "../device/handle.hpp"
#include "../result.hpp"
#include "../memory_offset.hpp"
#include "../function.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

extern "C" VK_ATTR int32 VK_CALL vkBindImageMemory(
	handle<vk::device>        device,
	handle<vk::image>         image,
	handle<vk::device_memory> memory,
	vk::device_size           memory_offset
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::device>>,
		types::are_contain_one_decayed<handle<vk::image>>,
		types::are_contain_one_decayed<handle<vk::device_memory>>,
		types::are_may_contain_one_decayed<vk::memory_offset>
	>::for_types<Args...> [[nodiscard]]
	vk::result try_bind_image_memory(Args&&... args) {
		auto device = elements::decayed<handle<vk::device>>(args...);
		auto image = elements::decayed<handle<vk::image>>(args...);
		auto device_memory {
			elements::decayed<handle<vk::device_memory>>(args...)
		};

		vk::memory_offset offset{ 0 };
		
		if constexpr (
			types::are_contain_decayed<vk::memory_offset>::for_types<Args...>
		) { offset = elements::decayed<vk::memory_offset>(args...); }

		return {
			vkBindImageMemory(
				device, image, device_memory, offset
			)
		};
	} // try_bind_image_memory

	template<typename... Args>
	void bind_image_memory(Args&&... args) {
		vk::result result = vk::try_bind_image_memory(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk

void inline
handle<vk::device>::bind_memory(
	handle<vk::image> image, handle<vk::device_memory> memory
) const {
	vk::bind_image_memory(*this, image, memory);
}