#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include "../../create_or_allocate.hpp"
#include "../../result.hpp"
#include "../../device/handle.hpp"
#include "../../function.hpp"

#include <core/meta/decayed_same_as.hpp>

extern "C" VK_ATTR int32 VK_CALL vkCreateBufferView(
	handle<vk::device> device,
	const vk::buffer_view_create_info* create_info,
	const void* allocator,
	handle<vk::buffer_view>* view
);

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
			auto& buffer {
				elements::possibly_guarded_handle_of<vk::buffer>(args...)
			};

			auto format = elements::decayed<vk::format>(args...);
			auto offset = elements::decayed<vk::memory_offset>(args...);
			auto size = elements::decayed<vk::memory_size>(args...);

			vk::buffer_view_create_info ci {
				.buffer = vk::get_handle(buffer)
				.format = format
				.offset = offset
				.size = size
			};

			auto& device {
				elements::possibly_guarded_handle_of<vk::device>(args...)
			};

			handle<vk::buffer_view> buffer_view;

			vk::result result {
				vkCreateBufferView(
					vk::get_handle(device),
					&ci,
					nullptr,
					&buffer_view
				)
			};

			if(result.error()) return result;

			return handle<vk::buffer_view>{ buffer_view };

		} // constructor

	}; // create_t<buffer_view>

} // vk