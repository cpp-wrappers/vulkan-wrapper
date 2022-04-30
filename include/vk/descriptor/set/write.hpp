#pragma once

#include "handle.hpp"

#include "../../buffer/view/handle.hpp"
#include "../../count.hpp"
#include "../../descriptor/binding.hpp"
#include "../../descriptor/type.hpp"
#include "../../descriptor/image_info.hpp"
#include "../../descriptor/buffer_info.hpp"
#include "../../descriptor/array_element.hpp"

#include <core/range_of_value_type_same_as.hpp>
#include <core/meta/decayed_same_as.hpp>

namespace vk {

	struct write_descriptor_set {
		uint32 strucutre_type = 35;
		const void* next = nullptr;
		handle<vk::descriptor_set> dst_set;
		vk::dst_binding dst_binding;
		vk::dst_array_element dst_array_element{ 1 };
		vk::count count;
		vk::descriptor_type descriptor_type;
		const vk::descriptor_image_info* image_info{};
		const vk::descriptor_buffer_info* buffer_info{};
		const handle<vk::buffer_view>* texel_buffer_view{};

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<handle<vk::descriptor_set>>,
			types::are_contain_one_decayed<vk::dst_binding>,
			types::are_contain_one_decayed<vk::dst_array_element>,
			types::are_contain_one_decayed<vk::descriptor_type>,
			types::are_may_contain_range_of<vk::descriptor_image_info>,
			types::are_may_contain_range_of<vk::descriptor_buffer_info>,
			types::are_may_contain_range_of<handle<vk::buffer_view>>
		>::for_types<Args...> &&
		(
			types::count_of_ranges_of<
				vk::descriptor_image_info
			>::for_types<Args...> +
			types::count_of_ranges_of<
				vk::descriptor_buffer_info
			>::for_types<Args...> +
			types::count_of_ranges_of<
				handle<vk::buffer_view>
			>::for_types<Args...>
			== 1
		)
		write_descriptor_set(Args&&... args) :
			dst_set {
				elements::decayed<handle<vk::descriptor_set>>(args...)
			},
			dst_binding { elements::decayed<vk::dst_binding>(args...) },
			dst_array_element {
				elements::decayed<vk::dst_array_element>(args...)
			},
			descriptor_type { elements::decayed<vk::descriptor_type>(args...) }
		{
			if constexpr (
				types::are_contain_range_of<
					vk::descriptor_image_info
				>::for_types<Args...>
			) {
				auto& r {
					elements::range_of<vk::descriptor_image_info>(args...)
				};

				count = vk::count{ (uint32) r.size() };
				image_info = r.data();
			}

			if constexpr (
				types::are_contain_range_of<
					vk::descriptor_buffer_info
				>::for_types<Args...>
			) {
				auto& r {
					elements::range_of<vk::descriptor_buffer_info>(args...)
				};

				count = vk::count{ (uint32) r.size() };
				buffer_info = r.data();
			}

			if constexpr (
				types::are_contain_range_of<
					handle<vk::buffer_view>
				>::for_types<Args...>
			) {
				auto& r = elements::range_of<handle<vk::buffer_view>>(args...);
				count = vk::count{ (uint32) r.size() };
				texel_buffer_view = r.data();
			}

		} // constructor

	}; // write_descriptor_set

} // vk