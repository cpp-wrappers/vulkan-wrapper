#pragma once

#include "handle.hpp"
#include "create_info.hpp"
#include "../../../device/handle.hpp"
#include "../../../../object/create_or_allocate.hpp"
#include "../../../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../../../shared/result.hpp"

#include <core/range/of_value_type.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

namespace vk {

	template<>
	struct vk::create_t<vk::descriptor_set_layout> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_contain_one_decayed_same_as<vk::descriptor_set_layout_create_flags>,
			types::are_contain_one_range_of_value_type<vk::descriptor_set_layout_binding>
		>::for_types<Args...>
		expected<vk::handle<vk::descriptor_set_layout>>
		operator () (Args&&... args) const {
			auto flags = elements::decayed_same_as<vk::descriptor_set_layout_create_flags>(args...);
			auto& bindings = elements::range_of_value_type<vk::descriptor_set_layout_binding>(args...);

			vk::descriptor_set_layout_create_info ci {
				.flags = flags,
				.binding_count = (uint32) bindings.size(),
				.bindings = bindings.data()
			};

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