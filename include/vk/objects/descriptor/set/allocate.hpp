#pragma once

#include "../../../object/create_or_allocate.hpp"
#include "../../device/handle.hpp"
#include "allocate_info.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	constexpr inline bool is_allocatable<vk::descriptor_set> = true;

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::descriptor_pool>,
		types::count_of_ranges_of_value_type<vk::handle<vk::descriptor_set_layout>>::equals<1>,
		types::count_of_ranges_of_value_type<vk::handle<vk::descriptor_set>>::equals<1>
	>::for_types<Args...>
	vk::result try_allocate_descriptor_sets(Args&&... args) {
		auto& pool = elements::vk::possibly_guarded_handle_of<vk::descriptor_pool>(args...);
		auto& sets = elements::range_of_value_type<vk::handle<vk::descriptor_set>>(args...);
		auto& layouts = elements::range_of_value_type<vk::handle<vk::descriptor_set_layout>>(args...);

		vk::descriptor_set_allocate_info ai {
			.descriptor_pool = vk::get_handle(pool),
			.descriptor_set_count{ (uint32) layouts.size() },
			.descriptor_set_layouts = layouts.data()
		};

		auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);

		return {
			(int32) vkAllocateDescriptorSets(
				(VkDevice) vk::get_handle_value(device),
				(VkDescriptorSetAllocateInfo*) &ai,
				(VkDescriptorSet*) sets.data()
			)
		};
	}

	template<>
	struct vk::allocate_t<vk::descriptor_set> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::descriptor_pool>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::descriptor_set_layout>
		>::for_types<Args...>
		vk::expected<vk::handle<descriptor_set>>
		operator () (Args&&... args) const {
			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);
			auto& pool = elements::vk::possibly_guarded_handle_of<vk::descriptor_pool>(args...);
			auto& layout = elements::vk::possibly_guarded_handle_of<vk::descriptor_set_layout>(args...);
			
			vk::handle<vk::descriptor_set> set;

			vk::result result = vk::try_allocate_descriptor_sets(
				device,
				pool,
				array<vk::handle<vk::descriptor_set_layout>, 1>{ vk::get_handle(layout) },
				span{ &set, 1 }
			);

			if(result.error()) return result;

			return set;
		}

	};

} // vk