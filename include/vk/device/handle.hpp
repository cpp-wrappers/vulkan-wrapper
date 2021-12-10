#pragma once

#include <core/forward.hpp>
#include <core/elements/one_of.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/exchange.hpp>

#include "../shared/headers.hpp"
#include "../shared/queue_family_index.hpp"
#include "../queue/handle.hpp"

namespace vk {

	class physical_device;
	class shader_module;
	class command_pool;

	struct queue_index : wrapper::of_integer<uint32, struct queue_index_t> {};

	struct device {
		void* handle;

		template<typename... Args>
		elements::one_of<vk::result, vk::shader_module>
		try_create_shader_module(Args&&... args) const;

		template<typename... Args>
		vk::shader_module create_shader_module(Args&&... args) const;

		template<typename... Args>
		vk::command_pool create_command_pool(Args&&... args) const;

		vk::queue get_queue(vk::queue_family_index queue_family_index, vk::queue_index queue_index) const {
			VkQueue queue;

			vkGetDeviceQueue(
				(VkDevice) handle,
				(uint32) queue_family_index,
				(uint32) queue_index,
				(VkQueue*) &queue
			);

			return { queue };
		}

		vk::result try_wait_idle() const {
			return {
				(int32) vkDeviceWaitIdle(
					(VkDevice) handle
				)
			};
		}
		
	}; // device

} // vk

#include "../command/pool/create.hpp"

template<typename... Args>
vk::command_pool
vk::device::create_command_pool(Args&&... args) const {
	return vk::create_command_pool(*this, forward<Args>(args)...);
}

#include "../shader/module/create.hpp"

template<typename... Args>
elements::one_of<vk::result, vk::shader_module>
vk::device::try_create_shader_module(Args&&... args) const {
	return vk::try_create_shader_module(*this, args...);
}

template<typename... Args>
vk::shader_module
vk::device::create_shader_module(Args&&... args) const {
	auto result = try_create_shader_module(forward<Args>(args)...);
	if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
	return result.template get<vk::shader_module>();
}

