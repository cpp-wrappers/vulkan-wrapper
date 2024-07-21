#pragma once

#include <tuple.hpp>

#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"
#include "../__command_buffer/handle.hpp"
#include "../__image/handle.hpp"
#include "../__image/layout.hpp"
#include "../__image/subresource_layers.hpp"
#include "../__sampler/filter.hpp"
#include "../__internal/function.hpp"
#include "../__internal/offset.hpp"

namespace vk {

	struct image_blit {
		vk::image_subresource_layers src_subresource;
		vk::offset<3> src_offset[2];
		vk::image_subresource_layers dst_subresource;
		vk::offset<3> dst_offset[2];
	};

	struct cmd_blit_image_function : vk::function<void(*)(
		handle<vk::command_buffer>::underlying_type,
		handle<vk::image>::underlying_type,
		vk::image_layout,
		handle<vk::image>::underlying_type,
		vk::image_layout,
		uint32 region_count,
		const vk::image_blit*,
		vk::filter
	)> {
		static constexpr auto name = "vkCmdBlitImage";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of<is_same_as<handle<vk::instance>>.decayed> == 1,
		count_of<is_same_as<handle<vk::device>>.decayed> == 1,
		count_of<is_same_as<handle<vk::command_buffer>>.decayed> == 1,

		count_of<is_same_as<vk::src_image>.decayed> == 1,
		count_of<is_same_as<vk::src_image_layout>.decayed> == 1,

		count_of<is_same_as<vk::dst_image>.decayed> == 1,
		count_of<is_same_as<vk::dst_image_layout>.decayed> == 1,

		count_of<is_range_of_element_type_satisfying_predicate<
			is_same_as<vk::image_blit>.decayed
		>> == 1,

		count_of<is_same_as<vk::filter>> == 1
	>
	void cmd_blit_image(Args&&... args) {
		tuple a{ forward<Args>(args)... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::command_buffer> command_buffer = a.template
			get<is_same_as<handle<vk::command_buffer>>.decayed>();

		vk::src_image src_image = a.template
			get<is_same_as<vk::src_image>.decayed>();
		vk::src_image_layout src_image_layout = a.template
			get<is_same_as<vk::src_image_layout>.decayed>();

		vk::dst_image dst_image = a.template
			get<is_same_as<vk::dst_image>.decayed>();
		vk::dst_image_layout dst_image_layout = a.template
			get<is_same_as<vk::dst_image_layout>.decayed>();

		auto& regions = a.template
			get<is_range_of_element_type_satisfying_predicate<
				is_same_as<vk::image_blit>.decayed
			>>();

		vk::filter filter = a.template
			get<is_same_as<vk::filter>.decayed>();

		vk::get_device_function<cmd_blit_image_function>(instance, device)(
			command_buffer.underlying(),
			src_image.underlying(),
			src_image_layout._,
			dst_image.underlying(),
			dst_image_layout._,
			(uint32) regions.size(),
			regions.iterator(),
			filter
		);
	}

} // vk