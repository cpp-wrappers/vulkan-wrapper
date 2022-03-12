#pragma once

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/meta/decayed_same_as.hpp>

#include "headers.hpp"
#include "handle/possibly_guarded_handle_of.hpp"
#include "handle/get_value.hpp"

namespace vk {

	struct device;

	template<typename ObjectType, typename HandleType, void Function(const VkDevice, const HandleType, const VkAllocationCallbacks*)>
	struct device_child_destroy_base {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_contain_one_decayed<vk::handle<ObjectType>>
		>::template for_types<Args...>
		void operator() (Args&&... args) const {
			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);
			auto fence = elements::decayed<vk::handle<ObjectType>>(args...);

			Function(
				(VkDevice) vk::get_handle_value(device),
				(HandleType) vk::get_handle_value(fence),
				(VkAllocationCallbacks*) nullptr
			);
		}

	};

}