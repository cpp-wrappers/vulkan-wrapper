#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include "../function.hpp"
#include "../create_or_allocate.hpp"

#include <core/meta/decayed_same_as.hpp>

VK_ATTR VkResult VK_CALL vkCreateInstance(
	const vk::instance_create_info*,
	const void*,
	handle<vk::instance>*
);

namespace vk {

	template<>
	struct vk::create_t<vk::instance> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_may_contain_one_decayed<vk::application_info>,
			types::are_may_contain_range_of<vk::layer_name>,
			types::are_may_contain_range_of<vk::extension_name>
		>::for_types<Args...>
		vk::expected<handle<vk::instance>>
		operator () (Args&&... args) const {
			instance_create_info ici{};

			if constexpr(
				types::are_contain_decayed<
					vk::application_info
				>::for_types<Args...>
			) {
				ici.application_info = & elements::decayed<
					vk::application_info
				>(args...);
			}

			if constexpr(
				types::are_contain_range_of<
					vk::extension_name
				>::for_types<Args...>
			) {
				auto& range = elements::range_of<vk::extension_name>(args...);
				ici.enabled_extension_count = (uint32) range.size();
				ici.enabled_extension_names = range.data();
			}

			if constexpr(
				types::are_contain_range_of<vk::layer_name>::for_types<Args...>
			) {
				auto& range = elements::range_of<vk::layer_name>(args...);
				ici.enabled_layer_count = (uint32) range.size();
				ici.enabled_layer_names = range.data();
			}

			handle<vk::instance> instance;

			vk::result result {
				(int32) vkCreateInstance(
					(VkInstanceCreateInfo*) &ici,
					(VkAllocationCallbacks*) nullptr,
					(VkInstance*) &instance
				)
			};

			if(result.error()) return result;

			return instance;

		} // operator ()

	}; // create_t<instance>

} // vk