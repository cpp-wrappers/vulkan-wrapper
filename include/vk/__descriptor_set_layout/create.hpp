#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include "../__internal/result.hpp"
#include "../__device/handle.hpp"
#include "../__internal/function.hpp"

extern "C" VK_ATTR int32 VK_CALL vkCreateDescriptorSetLayout(
	handle<vk::device>                           device,
	const vk::descriptor_set_layout_create_info* create_info,
	const void*                                  allocator,
	handle<vk::descriptor_set_layout>*           set_layout
);

namespace vk {

	template<>
	struct vk::create_t<vk::descriptor_set_layout> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<handle<vk::device>>,
			types::are_may_contain_one_decayed<
				vk::descriptor_set_layout_create_flags
			>,
			types::are_contain_range_of<vk::descriptor_set_layout_binding>
		>::for_types<Args...>
		expected<handle<vk::descriptor_set_layout>>
		operator () (Args&&... args) const {
			auto& bindings {
				elements::range_of<vk::descriptor_set_layout_binding>(args...)
			};

			vk::descriptor_set_layout_create_info ci {
				.binding_count = (uint32) bindings.size(),
				.bindings = bindings.data()
			};
			
			if constexpr (
				types::are_contain_decayed<
					vk::descriptor_set_layout_create_flags
				>::for_types<Args...>
			) {
				ci.flags = elements::decayed<
					vk::descriptor_set_layout_create_flags
				>(args...);
			}

			auto device = elements::decayed<handle<vk::device>>(args...);

			handle<vk::descriptor_set_layout> descriptor_set_layout;

			vk::result result {
				vkCreateDescriptorSetLayout(
					device,
					&ci,
					nullptr,
					&descriptor_set_layout
				)
			};

			if(result.error()) return result;

			return descriptor_set_layout;

		} // constructor

	}; // create_t<descriptor_set_layout>

} // vk