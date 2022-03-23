#pragma once

#include "allocate_info.hpp"
#include "handle.hpp"

#include "vk/create_or_allocate.hpp"
#include "vk/device/handle.hpp"

namespace vk {

	template<>
	constexpr inline bool is_allocatable<vk::descriptor_set> = true;

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_one_possibly_guarded_handle_of<vk::descriptor_pool>,
		types::are_contain_range_of<handle<vk::descriptor_set_layout>>,
		types::are_contain_range_of<handle<vk::descriptor_set>>
	>::for_types<Args...>
	vk::result try_allocate_descriptor_sets(Args&&... args) {
		auto& pool = elements::possibly_guarded_handle_of<vk::descriptor_pool>(args...);
		auto& sets = elements::range_of<handle<vk::descriptor_set>>(args...);
		auto& layouts = elements::range_of<handle<vk::descriptor_set_layout>>(args...);

		vk::descriptor_set_allocate_info ai {
			.descriptor_pool = vk::get_handle(pool),
			.descriptor_set_count{ (uint32) layouts.size() },
			.descriptor_set_layouts = layouts.data()
		};

		auto& device = elements::possibly_guarded_handle_of<vk::device>(args...);

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
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_contain_one_possibly_guarded_handle_of<vk::descriptor_pool>,
			types::are_contain_one_possibly_guarded_handle_of<vk::descriptor_set_layout>
		>::for_types<Args...>
		vk::expected<handle<descriptor_set>>
		operator () (Args&&... args) const {
			auto& device = elements::possibly_guarded_handle_of<vk::device>(args...);
			auto& pool = elements::possibly_guarded_handle_of<vk::descriptor_pool>(args...);
			auto& layout = elements::possibly_guarded_handle_of<vk::descriptor_set_layout>(args...);
			
			handle<vk::descriptor_set> set;

			vk::result result = vk::try_allocate_descriptor_sets(
				device,
				pool,
				array<handle<vk::descriptor_set_layout>, 1>{ vk::get_handle(layout) },
				span{ &set, 1 }
			);

			if(result.error()) return result;

			return set;
		}

	};

} // vk