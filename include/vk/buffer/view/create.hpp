#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include <core/meta/decayed_same_as.hpp>

#include "vk/create_or_allocate.hpp"
#include "vk/result.hpp"
#include "vk/device/handle.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::buffer_view> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_contain_one_possibly_guarded_handle_of<vk::buffer>,
			types::are_contain_one_decayed<vk::format>,
			types::are_contain_one_decayed<vk::memory_offset>,
			types::are_contain_one_decayed<vk::memory_size>
		>::for_types<Args...>
		vk::expected<handle<vk::buffer_view>>
		operator () (Args&&... args) const {
			auto& buffer = elements::possibly_guarded_handle_of<vk::buffer>(args...);

			auto format = elements::decayed<vk::format>(args...);
			auto offset = elements::decayed<vk::memory_offset>(args...);
			auto size = elements::decayed<vk::memory_size>(args...);

			vk::buffer_view_create_info ci {
				.buffer = vk::get_handle(buffer)
				.format = format
				.offset = offset
				.size = size
			};

			auto& device = elements::possibly_guarded_handle_of<vk::device>(args...);

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

			return handle<vk::buffer_view>{ buffer_view };
		}

	};

} // vk