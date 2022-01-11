#pragma once

#include "../../../object/create_or_allocate.hpp"
#include "../../device/handle.hpp"
#include "allocate_info.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	constexpr inline bool is_allocatable<vk::descriptor_set> = true;

	template<>
	struct vk::allocate_t<vk::descriptor_set> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::descriptor_pool>,
			types::count_of_ranges_of_value_type<vk::handle<vk::descriptor_set_layout>>::equals<1>,
			types::count_of_ranges_of_value_type<vk::handle<vk::descriptor_set>>::equals<1>
		>::for_types_of<Args...>
		vk::result operator () (Args&&... args) const {
			auto& pool = elements::vk::possibly_guarded_handle_of<vk::descriptor_pool>::for_elements_of(args...);
			auto& sets = elements::range_of_value_type<vk::handle<vk::descriptor_set>>::for_elements_of(args...);
			auto& layouts = elements::range_of_value_type<vk::handle<vk::descriptor_set_layout>>::for_elements_of(args...);

			vk::descriptor_set_allocate_info ai {
				.descriptor_pool = vk::get_handle(pool),
				.descriptor_set_count{ (uint32) layouts.size() },
				.descriptor_set_layouts = layouts.data()
			};

			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);

			return {
				(int32) vkAllocateDescriptorSets(
					(VkDevice) vk::get_handle_value(device),
					(VkDescriptorSetAllocateInfo*) &ai,
					(VkDescriptorSet*) sets.data()
				)
			};
		}

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::descriptor_pool>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::descriptor_set_layout>
		>::for_types_of<Args...>
		vk::expected<vk::handle<descriptor_set>>
		operator () (Args&&... args) const {
			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);
			auto& pool = elements::vk::possibly_guarded_handle_of<vk::descriptor_pool>::for_elements_of(args...);
			auto& layout = elements::vk::possibly_guarded_handle_of<vk::descriptor_set_layout>::for_elements_of(args...);
			
			vk::handle<vk::descriptor_set> set;

			vk::result result = this->operator () (
				device,
				pool,
				array{ vk::get_handle(layout) },
				span{ &set, 1 }
			);

			if(!result.success()) return result;

			return set;
		}
	};

} // vk