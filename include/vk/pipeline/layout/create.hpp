#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include "../../create_or_allocate.hpp"
#include "../../device/handle.hpp"
#include "../../function.hpp"

extern "C" VK_ATTR int32 VK_CALL vkCreatePipelineLayout(
	handle<vk::device> device,
	const vk::pipeline_layout_create_info* create_info,
	const void* allocator,
	handle<vk::pipeline_layout>* pipeline_layout
);

namespace vk {

	template<>
	struct vk::create_t<vk::pipeline_layout> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_may_contain_range_of<handle<vk::descriptor_set_layout>>,
			types::are_may_contain_range_of<vk::push_constant_range>
		>::for_types<Args...>
		vk::expected<handle<vk::pipeline_layout>>
		operator () (Args&&... args) const {
			vk::pipeline_layout_create_info ci{};

			if constexpr(
				types::are_contain_range_of<
					handle<vk::descriptor_set_layout>
				>::for_types<Args...>
			) {
				auto& layouts = elements::range_of<
					handle<vk::descriptor_set_layout>
				>(args...);
				ci.descriptor_set_layout_count = (uint32) layouts.size();
				ci.descriptor_set_layouts = layouts.data();
			}

			if constexpr(
				types::are_contain_range_of<
					vk::push_constant_range
				>::for_types<Args...>
			) {
				auto& push_constant_ranges = elements::range_of<
					vk::push_constant_range
				>(args...);

				ci.push_constant_range_count =
					(uint32) push_constant_ranges.size();
				ci.push_constant_ranges = push_constant_ranges.data();
			}

			auto& device = elements::possibly_guarded_handle_of<
				vk::device
			>(args...);

			handle<vk::pipeline_layout> pipeline_layout;

			vk::result result {
				vkCreatePipelineLayout(
					vk::get_handle(device),
					&ci,
					nullptr,
					&pipeline_layout
				)
			};

			if(result.error()) return result;

			return pipeline_layout;

		} // operator ()

	}; // create_t<pipeline_layout>

} // vk