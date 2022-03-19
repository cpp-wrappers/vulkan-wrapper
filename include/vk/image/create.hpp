#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

#include "vk/device/handle.hpp"
#include "vk/create_or_allocate.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::image> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_contain_one_decayed<vk::image_create_flags>,
			types::are_contain_one_decayed<vk::image_type>,
			types::are_contain_one_decayed<vk::format>,
			types::are_contain_one_decayed<vk::extent<3>>,
			types::are_contain_one_decayed<vk::mip_levels>,
			types::are_contain_one_decayed<vk::array_layers>,
			types::are_contain_one_decayed<vk::sample_count>,
			types::are_contain_one_decayed<vk::image_tiling>,
			types::are_contain_one_decayed<vk::image_usages>,
			types::are_contain_one_decayed<vk::sharing_mode>,
			types::are_contain_one_range_of<vk::queue_family_index>,
			types::are_contain_one_decayed<vk::initial_layout>
		>::for_types<Args...>
		vk::expected<handle<vk::image>>
		operator () (Args&&... args) const {
			vk::image_create_info ci{};

			ci.flags = elements::decayed<vk::image_create_flags>(args...);
			ci.image_type = elements::decayed<vk::image_type>(args...);
			ci.format = elements::decayed<vk::format>(args...);
			ci.extent = elements::decayed<vk::extent<3>>(args...);
			ci.mip_levels = elements::decayed<vk::mip_levels>(args...);
			ci.array_layers = elements::decayed<vk::array_layers>(args...);
			ci.samples = elements::decayed<vk::sample_count>(args...);
			ci.tiling = elements::decayed<vk::image_tiling>(args...);
			ci.usages = elements::decayed<vk::image_usages>(args...);
			ci.sharing_mode = elements::decayed<vk::sharing_mode>(args...);
			ci.initial_layout = elements::decayed<vk::initial_layout>(args...);

			auto& queues = elements::range_of<vk::queue_family_index>(args...);

			ci.queue_family_index_count = (uint32) queues.size();
			ci.queue_family_indices = queues.data();

			auto& device = elements::possibly_guarded_handle_of<vk::device>(args...);

			handle<vk::image> image;

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