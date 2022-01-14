#pragma once

#include "../../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../../object/create_or_allocate.hpp"
#include "../../../shared/result.hpp"
#include "../../device/handle.hpp"
#include "create_info.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::buffer_view> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::buffer>,
			types::count_of_type<vk::format>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::memory_offset>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::memory_size>::equals<1>::ignore_const::ignore_reference
		>::for_types_of<Args...>
		vk::expected<vk::handle<vk::buffer_view>>
		operator () (Args&&... args) const {
			auto& buffer = elements::vk::possibly_guarded_handle_of<vk::buffer>::for_elements_of(args...);

			auto format = elements::of_type<vk::format>::ignore_const::ignore_reference::for_elements_of(args...);
			auto offset = elements::of_type<vk::memory_offset>::ignore_const::ignore_reference::for_elements_of(args...);
			auto size = elements::of_type<vk::memory_size>::ignore_const::ignore_reference::for_elements_of(args...);

			vk::buffer_view_create_info ci {
				.buffer = vk::get_handle(buffer)
				.format = format
				.offset = offset
				.size = size
			};

			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);

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