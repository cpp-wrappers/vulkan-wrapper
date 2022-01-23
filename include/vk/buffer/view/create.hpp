#pragma once

#include "handle.hpp"
#include "create_info.hpp"
#include "../../create_or_allocate.hpp"
#include "../../result.hpp"
#include "../../device/handle.hpp"

#include <core/meta/decayed_same_as.hpp>

namespace vk {

	template<>
	struct vk::create_t<vk::buffer_view> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::buffer>,
			types::are_contain_one_decayed_same_as<vk::format>,
			types::are_contain_one_decayed_same_as<vk::memory_offset>,
			types::are_contain_one_decayed_same_as<vk::memory_size>
		>::for_types<Args...>
		vk::expected<vk::handle<vk::buffer_view>>
		operator () (Args&&... args) const {
			auto& buffer = elements::vk::possibly_guarded_handle_of<vk::buffer>(args...);

			auto format = elements::decayed_same_as<vk::format>(args...);
			auto offset = elements::decayed_same_as<vk::memory_offset>(args...);
			auto size = elements::decayed_same_as<vk::memory_size>(args...);

			vk::buffer_view_create_info ci {
				.buffer = vk::get_handle(buffer)
				.format = format
				.offset = offset
				.size = size
			};

			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);

			VkBufferView buffer_view;

			vk::result result {
				(int32) vkCreateBufferView(
					(VkDevice) vk::get_handle_value(device),
					(VkBufferViewCreateInfo*) &ci,
					(VkAllocationCallbacks*) nullptr,
					(VkBufferView*) &buffer_view
				)
			};

			if(result.error()) return result;

			return vk::handle<vk::buffer_view>{ buffer_view };
		}

	};

} // vk