#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/offset.hpp"
#include "../__internal/extent.hpp"
#include "../__image/subresource_layers.hpp"
#include "../__image/handle.hpp"
#include "../__image/layout.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"

namespace vk {

	struct image_copy {
		vk::image_subresource_layers src_subresource;
		vk::offset<3> src_offset;
		vk::image_subresource_layers dst_subresource;
		vk::offset<3> dst_offset;
		vk::extent<3> extent;
	};

} // vk

namespace vk {

	struct cmd_copy_image_function : vk::function<void(*)(
		handle<vk::command_buffer>::underlying_type command_buffer,
		handle<vk::image>::underlying_type,
		vk::image_layout,
		handle<vk::image>::underlying_type,
		vk::image_layout,
		uint32 region_count,
		const vk::image_copy* regions
	)> {
		static constexpr auto name = "vkCmdCopyImage";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of<is_same_as<handle<vk::instance>>.while_decayed> == 1,
		count_of<is_same_as<handle<vk::device>>.while_decayed> == 1,
		count_of<is_same_as<handle<vk::command_buffer>>.while_decayed> == 1,
		count_of<is_same_as<vk::src_image>.while_decayed> == 1,
		count_of<is_same_as<vk::src_image_layout>.while_decayed> == 1,
		count_of<is_same_as<vk::dst_image>.while_decayed> == 1,
		count_of<is_same_as<vk::dst_image_layout>.while_decayed> == 1,
		count_of<is_range_of_element_type_satisfying_predicate<is_same_as<vk::image_copy>.while_decayed>> == 1
	>
	void cmd_copy_image(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.while_decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.while_decayed>();

		handle<vk::command_buffer> command_buffer = a.template
			get<is_same_as<handle<vk::command_buffer>>.while_decayed>();

		vk::src_image src = a.template
			get<is_same_as<vk::src_image>.while_decayed>();

		vk::src_image_layout src_layout = a.template
			get<is_same_as<vk::src_image_layout>.while_decayed>();

		vk::dst_image dst = a.template
			get<is_same_as<vk::dst_image>.while_decayed>();
		
		vk::dst_image_layout dst_layout = a.template
			get<is_same_as<vk::dst_image_layout>.while_decayed>();

		auto& regions = a.template
			get<is_range_of_element_type_satisfying_predicate<
				is_same_as<vk::image_copy>.while_decayed>
			>();

		vk::get_device_function<vk::cmd_copy_image_function>(
			instance, device
		)(
			command_buffer.underlying(),
			src.underlying(),
			src_layout._,
			dst.underlying(),
			dst_layout._,
			(uint32) regions.size(),
			regions.iterator()
		);
	}

} // vk