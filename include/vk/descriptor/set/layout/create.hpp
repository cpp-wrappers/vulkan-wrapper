#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include <core/range/of_value_type.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

#include "vk/result.hpp"
#include "vk/device/handle.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::descriptor_set_layout> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_may_contain_one_decayed_same_as<vk::descriptor_set_layout_create_flags>,
			types::are_contain_one_range_of_value_type<vk::descriptor_set_layout_binding>
		>::for_types<Args...>
		expected<vk::handle<vk::descriptor_set_layout>>
		operator () (Args&&... args) const {
			auto& bindings = elements::range_of_value_type<vk::descriptor_set_layout_binding>(args...);

			vk::descriptor_set_layout_create_info ci {
				.binding_count = (uint32) bindings.size(),
				.bindings = bindings.data()
			};
			
			if constexpr(types::are_contain_decayed_same_as<vk::descriptor_set_layout_create_flags>::for_types<Args...>) {
				ci.flags = elements::decayed_same_as<vk::descriptor_set_layout_create_flags>(args...);
			}

			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);

			vk::handle<vk::descriptor_set_layout> descriptor_set_layout;

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