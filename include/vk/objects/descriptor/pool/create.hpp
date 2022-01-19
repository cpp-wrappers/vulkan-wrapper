#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>

#include "../../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../../object/create_or_allocate.hpp"
#include "../../../shared/result.hpp"
#include "../../device/handle.hpp"
#include "create_info.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::descriptor_pool> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::count_of_type<vk::descriptor_pool_create_flags>::equals<1>,
			types::count_of_type<vk::max_sets>::equals<1>,
			types::count_of_ranges_of_value_type<vk::descriptor_pool_size>::equals<1>
		>::for_types_of<decay<Args>...>
		vk::expected<vk::handle<vk::descriptor_pool>>
		operator () (Args&&... args) const {
			auto flags = elements::of_type<vk::descriptor_pool_create_flags>(args...);
			auto max_sets = elements::of_type<vk::max_sets>(args...);

			auto& sizes = elements::range_of_value_type<vk::descriptor_pool_size>(args...);

			vk::descriptor_pool_create_info ci {
				.flags = flags,
				.max_sets = max_sets,
				.pool_size_count = (uint32) sizes.size(),
				.pool_sizes = sizes.data()
			};

			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);

			vk::handle<vk::descriptor_pool> descriptor_pool;

			vk::result result {
				(int) vkCreateDescriptorPool(
					(VkDevice) vk::get_handle_value(device),
					(VkDescriptorPoolCreateInfo*) &ci,
					(VkAllocationCallbacks*) nullptr,
					(VkDescriptorPool*) &descriptor_pool
				)
			};

			if(result.error()) return result;

			return descriptor_pool;
		}

	};

} // vk