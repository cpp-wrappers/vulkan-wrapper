#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

#include "vk/result.hpp"
#include "vk/device/handle.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::descriptor_set_layout> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_may_contain_one_decayed<vk::descriptor_set_layout_create_flags>,
			types::are_contain_range_of<vk::descriptor_set_layout_binding>
		>::for_types<Args...>
		expected<handle<vk::descriptor_set_layout>>
		operator () (Args&&... args) const {
			auto& bindings = elements::range_of<vk::descriptor_set_layout_binding>(args...);

			vk::descriptor_set_layout_create_info ci {
				.binding_count = (uint32) bindings.size(),
				.bindings = bindings.data()
			};
			
			if constexpr(types::are_contain_decayed<vk::descriptor_set_layout_create_flags>::for_types<Args...>) {
				ci.flags = elements::decayed<vk::descriptor_set_layout_create_flags>(args...);
			}

			auto& device = elements::possibly_guarded_handle_of<vk::device>(args...);

			handle<vk::descriptor_set_layout> descriptor_set_layout;

			vk::result result {
				(int32) vkCreateDescriptorSetLayout(
					(VkDevice) vk::get_handle_value(device),
					(VkDescriptorSetLayoutCreateInfo*) &ci,
					(VkAllocationCallbacks*) nullptr,
					(VkDescriptorSetLayout*) &descriptor_set_layout
				)
			};

			if(result.error()) return result;

			return descriptor_set_layout;
		}

	};

} // vk