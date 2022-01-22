#pragma once

#include "handle/get_value.hpp"
#include "../shared/headers.hpp"
#include "../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../elements/possibly_guarded_handle_of.hpp"

#include <core/meta/types/are_contain_decayed_same_as.hpp>
#include <core/meta/elements/decayed_same_as.hpp>

namespace vk {

	struct device;

	template<typename ObjectType, typename HandleType, void Function(const VkDevice, const HandleType, const VkAllocationCallbacks*)>
	struct device_child_destroy_base {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			typename types::are_contain_one_decayed_same_as<vk::handle<ObjectType>>
		>::template for_types<Args...>
		void operator() (Args&&... args) const {
			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);
			auto fence = elements::decayed_same_as<vk::handle<ObjectType>>(args...);

			Function(
				(VkDevice) vk::get_handle_value(device),
				(VkFence) vk::get_handle_value(fence),
				(VkAllocationCallbacks*) nullptr
			);
		}
	};

}