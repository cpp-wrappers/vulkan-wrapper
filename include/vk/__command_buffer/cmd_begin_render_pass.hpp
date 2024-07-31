#pragma once

#include "./render_pass_begin_info.hpp"
#include "../__internal/function.hpp"
#include "../__command_buffer/handle.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct cmd_begin_render_pass_function : vk::function<void(*)(
		handle<vk::command_buffer>::underlying_type command_buffer,
		const vk::render_pass_begin_info* render_pass_begin,
		int32 contents
	)> {
		static constexpr auto name = "vkCmdBeginRenderPass";
	};
	
	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::command_buffer>>.decayed == 1,
		is_same_as<vk::render_pass_begin_info>.decayed == 1
	>
	void cmd_begin_render_pass(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::command_buffer> command_buffer = a.template
			get<is_same_as<handle<vk::command_buffer>>.decayed>();

		auto& render_pass_begin_info = a.template
			get<is_same_as<vk::render_pass_begin_info>.decayed>();

		vk::get_device_function<vk::cmd_begin_render_pass_function>(
			instance, device
		)(
			command_buffer.underlying(),
			&render_pass_begin_info,
			0
		);
	} // cmd_begin_render_pass

	template<typename... Args>
	requires
	//(Order == 1) &&
	types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::command_buffer>>.decayed == 1,
		is_same_as<handle<vk::render_pass>>.decayed == 1,
		is_same_as<handle<vk::framebuffer>>.decayed == 1,
		is_same_as<vk::render_area>.decayed == 1,
		is_range_of<is_same_as<vk::clear_value>.decayed> <= 1
	>
	void cmd_begin_render_pass(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::command_buffer> command_buffer = a.template
			get<is_same_as<handle<vk::command_buffer>>.decayed>();

		handle<vk::render_pass> render_pass = a.template
			get<is_same_as<handle<vk::render_pass>>.decayed>();

		handle<vk::framebuffer> framebuffer = a.template
			get<is_same_as<handle<vk::framebuffer>>.decayed>();

		vk::clear_value* clear_values = nullptr;
		uint32 clear_values_count = 0;

		if constexpr(
			(is_range_of<is_same_as<vk::clear_value>.decayed> > 0)
			.for_types<Args...>()
		) {
			auto& clear_values0 = a.template
				get<is_range_of<is_same_as<vk::clear_value>.decayed>>();
			clear_values = clear_values0.iterator();
			clear_values_count = clear_values0.size();
		}

		vk::render_area render_area = a.template
			get<is_same_as<vk::render_area>.decayed>();

		return vk::cmd_begin_render_pass(
			instance,
			device,
			command_buffer,
			vk::render_pass_begin_info {
				.render_pass = render_pass.underlying(),
				.framebuffer = framebuffer.underlying(),
				.render_area = render_area,
				.clear_value_count = clear_values_count,
				.clear_values = clear_values
			}
		);
	} // cmd_begin_render_pass

	template<typename... Args>
	requires
	//(Order == 2) &&
	((is_same_as<vk::clear_value>.decayed == 1).for_types<Args...>())
	void cmd_begin_render_pass(Args&&... args) {
		vk::clear_value clear_value = tuple{ args... }.template
			get<is_same_as<vk::clear_value>.decayed>();

		tuple{ args... }.template
		pass<
			!is_same_as<vk::clear_value>.decayed
		>([&]<typename... Args0>(Args0&&... args0) {
			cmd_begin_render_pass(
				::array{ clear_value },
				::forward<Args0>(args0)...
			);
		});
	}

	//template<typename... Args>
	//requires (Order > 0)
	//void cmd_begin_render_pass(Args&&... args) {
	//	cmd_begin_render_pass<Order - 1>(forward<Args>(args)...);
	//}

	//template<typename... Args>
	//void cmd_begin_render_pass(Args&&... args) {
	//	cmd_begin_render_pass<2>(forward<Args>(args)...);
	//}

} // vk