#pragma once

#include "allocate_info.hpp"
#include "handle.hpp"

#include "../../function.hpp"
#include "../../create_or_allocate.hpp"
#include "../../device/handle.hpp"

extern "C" VK_ATTR int32 VK_CALL vkAllocateDescriptorSets(
	handle<vk::device>                      device,
	const vk::descriptor_set_allocate_info* allocate_info,
	handle<vk::descriptor_set>*             descriptor_sets
);

namespace vk {

	template<>
	constexpr inline bool is_allocatable<vk::descriptor_set> = true;

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::device>>,
		types::are_contain_one_decayed<handle<vk::descriptor_pool>>,
		types::are_contain_range_of<handle<vk::descriptor_set_layout>>,
		types::are_contain_range_of<handle<vk::descriptor_set>>
	>::for_types<Args...>
	vk::result try_allocate_descriptor_sets(Args&&... args) {
		auto pool = elements::decayed<handle<vk::descriptor_pool>>(args...);
		auto& sets = elements::range_of<handle<vk::descriptor_set>>(args...);
		auto& layouts {
			elements::range_of<handle<vk::descriptor_set_layout>>(args...)
		};

		vk::descriptor_set_allocate_info ai {
			.descriptor_pool = pool,
			.descriptor_set_count{ (uint32) layouts.size() },
			.descriptor_set_layouts = layouts.data()
		};

		auto device = elements::decayed<handle<vk::device>>(args...);

		return {
			vkAllocateDescriptorSets(
				device,
				&ai,
				sets.data()
			)
		};
	}

	template<>
	struct vk::allocate_t<vk::descriptor_set> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<handle<vk::device>>,
			types::are_contain_one_decayed<handle<vk::descriptor_pool>>,
			types::are_contain_one_decayed<handle<vk::descriptor_set_layout>>
		>::for_types<Args...>
		vk::expected<handle<descriptor_set>>
		operator () (Args&&... args) const {
			auto device = elements::decayed<handle<vk::device>>(args...);
			auto pool = elements::decayed<handle<vk::descriptor_pool>>(args...);
			auto layout = elements::decayed<handle<vk::descriptor_set_layout>>(args...);
			
			handle<vk::descriptor_set> set;

			vk::result result = vk::try_allocate_descriptor_sets(
				device,
				pool,
				array{ layout },
				single_view{ set }
			);

			if(result.error()) return result;

			return set;
		}

	};

} // vk