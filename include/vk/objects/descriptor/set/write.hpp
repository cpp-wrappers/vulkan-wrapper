#pragma once

#include "handle.hpp"
#include "../binding.hpp"
#include "../type.hpp"
#include "../image_info.hpp"
#include "../buffer_info.hpp"
#include "../array_element.hpp"
#include "../../buffer/view/handle.hpp"
#include "../../../object/handle/get.hpp"
#include "../../../shared/headers.hpp"
#include "../../../shared/count.hpp"

#include <core/meta/types/are_contain_decayed_same_as.hpp>
#include <core/meta/types/are_contain_range_of_value_type.hpp>

namespace vk {

	struct write_descriptor_set {
		const uint32 type = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		const void* const next{};
		vk::handle<vk::descriptor_set> dst_set;
		vk::dst_binding dst_binding;
		vk::dst_array_element dst_array_element;
		vk::count count;
		vk::descriptor_type descriptor_type;
		const vk::descriptor_image_info* image_info{};
		const vk::descriptor_buffer_info* buffer_info{};
		const vk::handle<vk::buffer_view>* texel_buffer_view{};

		template<typename... Args>
		requires (
			types::are_exclusively_satsify_predicates<
				types::vk::are_contain_one_possibly_guarded_handle_of<vk::descriptor_set>,
				types::are_contain_one_decayed_same_as<vk::dst_binding>,
				types::are_contain_one_decayed_same_as<vk::dst_array_element>,
				types::are_contain_one_decayed_same_as<vk::descriptor_type>,
				types::are_may_contain_one_range_of_value_type<vk::descriptor_image_info>,
				types::are_may_contain_one_range_of_value_type<vk::descriptor_buffer_info>,
				types::are_may_contain_one_range_of_value_type<vk::handle<vk::buffer_view>>
			>::for_types<Args...> &&
			(
				types::count_of_ranges_of_value_type<vk::descriptor_image_info>::for_types<Args...> + 
				types::count_of_ranges_of_value_type<vk::descriptor_buffer_info>::for_types<Args...> +
				types::count_of_ranges_of_value_type<vk::handle<vk::buffer_view>>::for_types<Args...>
				== 1 
			)
		)
		write_descriptor_set(Args&&... args) {
			dst_set = vk::get_handle(elements::vk::possibly_guarded_handle_of<vk::descriptor_set>(args...));
			dst_binding = elements::decayed_same_as<vk::dst_binding>(args...);
			dst_array_element = elements::decayed_same_as<vk::dst_array_element>(args...);
			descriptor_type = elements::decayed_same_as<vk::descriptor_type>(args...);

			if constexpr(types::are_contain_range_of_value_type<vk::descriptor_image_info>::for_types<Args...>) {
				auto& r = elements::range_of_value_type<vk::descriptor_image_info>(args...);
				count = vk::count{ (uint32) r.size() };
				image_info = r.data();
			}

			if constexpr(types::are_contain_range_of_value_type<vk::descriptor_buffer_info>::for_types<Args...>) {
				auto& r = elements::range_of_value_type<vk::descriptor_buffer_info>(args...);
				count = vk::count{ (uint32) r.size() };
				image_info = r.data();
			}

			if constexpr(types::are_contain_range_of_value_type<vk::handle<vk::buffer_view>>::for_types<Args...>) {
				auto& r = elements::range_of_value_type<vk::handle<vk::buffer_view>>(args...);
				count = vk::count{ (uint32) r.size() };
				image_info = r.data();
			}
		}
	};

} // vk

static_assert(sizeof(vk::write_descriptor_set) == sizeof(VkWriteDescriptorSet));