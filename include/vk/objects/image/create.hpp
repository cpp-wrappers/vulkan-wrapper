#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>

#include "../../object/create_or_allocate.hpp"
#include "../device/handle.hpp"
#include "create_info.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::image> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::count_of_type<vk::image_create_flags>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::image_type>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::format>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::extent<3>>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::mip_levels>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::array_layers>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::sample_count>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::image_tiling>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::image_usages>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::sharing_mode>::equals<1>::ignore_const::ignore_reference,
			types::count_of_ranges_of_value_type<vk::queue_family_index>::equals<1>,
			types::count_of_type<vk::initial_layout>::equals<1>::ignore_const::ignore_reference
		>::for_types_of<Args...>
		vk::expected<vk::handle<vk::image>>
		operator () (Args&&... args) const {
			vk::image_create_info ci{};

			ci.flags = elements::of_type<vk::image_create_flags>::ignore_const::ignore_reference::for_elements_of(args...);
			ci.image_type = elements::of_type<vk::image_type>::ignore_const::ignore_reference::for_elements_of(args...);
			ci.format = elements::of_type<vk::format>::ignore_const::ignore_reference::for_elements_of(args...);
			ci.extent = elements::of_type<vk::extent<3>>::ignore_const::ignore_reference::for_elements_of(args...);
			ci.mip_levels = elements::of_type<vk::mip_levels>::ignore_const::ignore_reference::for_elements_of(args...);
			ci.array_layers = elements::of_type<vk::array_layers>::ignore_const::ignore_reference::for_elements_of(args...);
			ci.samples = elements::of_type<vk::sample_count>::ignore_const::ignore_reference::for_elements_of(args...);
			ci.tiling = elements::of_type<vk::image_tiling>::ignore_const::ignore_reference::for_elements_of(args...);
			ci.usages = elements::of_type<vk::image_usages>::ignore_const::ignore_reference::for_elements_of(args...);
			ci.sharing_mode = elements::of_type<vk::sharing_mode>::ignore_const::ignore_reference::for_elements_of(args...);
			ci.initial_layout = elements::of_type<vk::initial_layout>::ignore_const::ignore_reference::for_elements_of(args...);

			auto& queues = elements::range_of_value_type<vk::queue_family_index>::for_elements_of(args...);

			ci.queue_family_index_count = (uint32) queues.size();
			ci.queue_family_indices = queues.data();

			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);

			vk::handle<vk::image> image;

			vk::result result {
				(int32) vkCreateImage(
					(VkDevice) vk::get_handle_value(device),
					(VkImageCreateInfo*) &ci,
					(VkAllocationCallbacks*) nullptr,
					(VkImage*) &image
				)
			};

			if(result.error()) return result;

			return image;
		};

	};

} // vk