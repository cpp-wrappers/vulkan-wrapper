#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include "../../create_or_allocate.hpp"
#include "../../result.hpp"
#include "../../device/handle.hpp"
#include "../../function.hpp"

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

extern "C" VK_ATTR int32 VK_CALL vkCreateDescriptorPool(
	handle<vk::device> device,
	const vk::descriptor_pool_create_info* create_info,
	const void* allocator,
	handle<vk::descriptor_pool>* descriptor_pool
);

namespace vk {

	template<>
	struct vk::create_t<vk::descriptor_pool> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<handle<vk::device>>,
			types::are_may_contain_one_decayed<
				vk::descriptor_pool_create_flags
			>,
			types::are_contain_one_decayed<vk::max_sets>,
			types::are_contain_range_of<vk::descriptor_pool_size>
		>::for_types<Args...>
		vk::expected<handle<vk::descriptor_pool>>
		operator () (Args&&... args) const {
			auto max_sets = elements::decayed<vk::max_sets>(args...);

			auto& sizes = elements::range_of<vk::descriptor_pool_size>(args...);

			vk::descriptor_pool_create_info ci {
				.max_sets = max_sets,
				.pool_size_count = (uint32) sizes.size(),
				.pool_sizes = sizes.data()
			};

			if constexpr (
				types::are_contain_decayed<
					vk::descriptor_pool_create_flags
				>::for_types<Args...>
			) {
				ci.flags = elements::decayed<
					vk::descriptor_pool_create_flags
				>(args...);
			}

			auto device = elements::decayed<handle<vk::device>>(args...);

			handle<vk::descriptor_pool> descriptor_pool;

			vk::result result {
				vkCreateDescriptorPool(
					device,
					&ci,
					nullptr,
					&descriptor_pool
				)
			};

			if(result.error()) return result;

			return descriptor_pool;

		} // operator ()

	}; // create_t<descriptor_pool>

} // vk