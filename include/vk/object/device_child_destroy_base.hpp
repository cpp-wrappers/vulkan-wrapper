#pragma once

#include <core/types/are_contain_one_type.hpp>

#include "../shared/headers.hpp"
#include "../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../elements/possibly_guarded_handle_of.hpp"
#include "handle/get_value.hpp"

namespace vk {

	struct device;

	template<typename ObjectType, typename HandleType, void Function(const VkDevice, const HandleType, const VkAllocationCallbacks*)>
	struct device_child_destroy_base {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			typename types::are_contain_one_type<vk::handle<ObjectType>>::decay
		>::template for_types_of<Args...>
		void operator() (Args&&... args) const {
			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);
			auto fence = elements::of_type<vk::handle<ObjectType>>::decay::for_elements_of(args...);

			Function(
				(VkDevice) vk::get_handle_value(device),
				(VkFence) vk::get_handle_value(fence),
				(VkAllocationCallbacks*) nullptr
			);
		}
	};

}