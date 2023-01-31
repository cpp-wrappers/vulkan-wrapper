#pragma once

#include "./handle.hpp"
#include "../__buffer_view/handle.hpp"
#include "../__internal/descriptor_binding.hpp"
#include "../__internal/descriptor_array_element.hpp"
#include "../__internal/count.hpp"
#include "../__internal/descriptor_type.hpp"
#include "../__internal/descriptor_image_info.hpp"
#include "../__internal/descriptor_buffer_info.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"
#include "../__command_buffer/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct write_descriptor_set {
		uint32 strucutre_type = 35;
		const void* next = nullptr;
		handle<vk::descriptor_set>::underlying_type dst_set;
		vk::dst_binding dst_binding;
		vk::dst_array_element dst_array_element{ 0 };
		vk::count count;
		vk::descriptor_type descriptor_type;
		const vk::descriptor_image_info* image_info{};
		const vk::descriptor_buffer_info* buffer_info{};
		const handle<vk::buffer_view>::underlying_type* texel_buffer_view{};

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			count_of_decayed_same_as<handle<vk::descriptor_set>> == 1,
			count_of_decayed_same_as<vk::dst_binding> == 1,
			count_of_decayed_same_as<vk::dst_array_element> <= 1,
			count_of_decayed_same_as<vk::descriptor_type> == 1,
			count_of_range_of_decayed<vk::descriptor_image_info> <= 1,
			count_of_range_of_decayed<vk::descriptor_buffer_info> <= 1,
			count_of_range_of_decayed<handle<vk::buffer_view>> <= 1
		> &&
		(
			types<Args...>::template count_of_range_of_decayed<
				vk::descriptor_image_info
			> +
			types<Args...>::template count_of_range_of_decayed<
				vk::descriptor_buffer_info
			> +
			types<Args...>::template count_of_range_of_decayed<
				handle<vk::buffer_view>
			>
			== 1
		)
		write_descriptor_set(Args&&... args) {
			tuple a { args... };
			
			dst_set = a.template
				get_decayed_same_as<handle<vk::descriptor_set>>().underlying();

			dst_binding = a.template
				get_decayed_same_as<vk::dst_binding>();

			descriptor_type = a.template
				get_decayed_same_as<vk::descriptor_type>();

			if constexpr (types<Args...>::template
				count_of_decayed_same_as<vk::dst_array_element> > 0
			) {
				dst_array_element = a.template
					get_decayed_same_as<vk::dst_array_element>();
			}

			if constexpr (types<Args...>::template
				count_of_range_of_decayed<vk::descriptor_image_info> > 0
			) {
				auto& r = a.template
					get_range_of_decayed<vk::descriptor_image_info>();

				count = vk::count{ (uint32) r.size() };
				image_info = r.iterator();
			}

			if constexpr (types<Args...>::template
				count_of_range_of_decayed<vk::descriptor_buffer_info>
			) {
				auto& r = a.template
					get_range_of_decayed<vk::descriptor_buffer_info>();

				count = vk::count{ (uint32) r.size() };
				buffer_info = r.iterator();
			}

			if constexpr (types<Args...>::template
				count_of_range_of_decayed<handle<vk::buffer_view>> > 0
			) {
				auto& r = a.template
					get_range_of_decayed<handle<vk::buffer_view>>();

				count = vk::count{ (uint32) r.size() };
				texel_buffer_view =
					(const handle<vk::buffer_view>::underlying_type*)
					r.iterator();
			}

		} // constructor

	}; // write_descriptor_set

} // vk