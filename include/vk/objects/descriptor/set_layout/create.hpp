#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/types/are_contain_range_of_value_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/for_each_of_type.hpp>
#include <core/elements/range_of_value_type.hpp>

#include "../../../shared/result.hpp"
#include "../../../object/create_or_allocate.hpp"
#include "../../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../device/handle.hpp"
#include "create_info.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::descriptor_set_layout> {

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
				types::count_of_type<vk::descriptor_set_layout_create_flags>::equals<1>::ignore_const::ignore_reference,
				types::count_of_ranges_of_value_type<vk::descriptor_set_layout_binding>::equals<1>
			>::for_types_of<Args...>
		)
		expected<vk::handle<vk::descriptor_set_layout>>
		operator () (Args&&... args) const {
			auto flags = elements::of_type<vk::descriptor_set_layout_create_flags>::ignore_const::ignore_reference::for_elements_of(args...);
			auto& bindings = elements::range_of_value_type<vk::descriptor_set_layout_binding>::for_elements_of(args...);

			vk::descriptor_set_layout_create_info ci {
				.flags = flags,
				.binding_count = (uint32) bindings.size(),
				.bindings = bindings.data()
			};

			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);

			VkDescriptorSetLayout descriptor_set_layout;

			vk::result result {
				(int32) vkCreateDescriptorSetLayout(
					(VkDevice) vk::get_handle_value(device),
					(VkDescriptorSetLayoutCreateInfo*) &ci,
					(VkAllocationCallbacks*) nullptr,
					(VkDescriptorSetLayout*) &descriptor_set_layout
				)
			};

			if(!result.success()) return result;

			return vk::handle<vk::descriptor_set_layout>{ descriptor_set_layout };
		}

	};

} // vk