#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include "vk/create_or_allocate.hpp"
#include "vk/queue_family_index.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::command_pool> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_may_contain_one_decayed<vk::command_pool_create_flags>,
			types::are_contain_decayed<vk::queue_family_index>
		>::for_types<Args...>
		vk::expected<handle<vk::command_pool>>
		operator () (Args&&... args) const {
			vk::command_pool_create_info ci{};

			ci.queue_family_index = elements::decayed<vk::queue_family_index>(args...);

			if constexpr(types::are_contain_decayed<vk::command_pool_create_flags>::for_types<Args...>) {
				ci.flags = elements::decayed<vk::command_pool_create_flags>(args...);
			}

			auto& device = elements::possibly_guarded_handle_of<vk::device>(args...);

			VkCommandPool command_pool;

			vk::result result {
				(int32) vkCreateCommandPool(
					(VkDevice) vk::get_handle_value(device),
					(VkCommandPoolCreateInfo*) &ci,
					nullptr,
					&command_pool
				)
			};

			if(result.error()) return result;

			return handle<vk::command_pool>{ command_pool };
		}

	};

} // vk