#pragma once

#include "../../result.hpp"
#include "../../handle/base.hpp"
#include "../../create_or_allocate.hpp"

namespace vk {

	struct command_buffer;

	template<>
	constexpr inline bool is_allocatable<vk::command_buffer> = true;

	template<>
	struct vk::handle<vk::command_buffer> : vk::handle_base<vk::dispatchable> {

		template<typename... Args> vk::result try_begin(Args&&...) const;

		template<typename... Args> requires(sizeof...(Args) > 0) auto& begin(Args&&...) const;

		inline vk::result try_end() const;
		inline void end() const;

		template<typename... Args> auto& cmd_pipeline_barrier(Args&&...) const;
		template<typename... Args> auto& cmd_copy_buffer_to_image(Args&&...) const;
		template<typename... Args> auto& cmd_clear_color_image(Args&&...) const;
		template<typename... Args> auto& cmd_begin_render_pass(Args&&...) const;
		inline                     auto& cmd_end_render_pass() const;
		template<typename... Args> auto& cmd_bind_pipeline(Args&&...) const;
		template<typename... Args> auto& cmd_set_viewport(Args&&...) const;
		template<typename... Args> auto& cmd_set_scissor(Args&&...) const;
		template<typename... Args> auto& cmd_draw(Args&&...) const;
		template<typename... Args> auto& cmd_bind_vertex_buffers(Args&&...) const;
		template<typename... Args> auto& cmd_bind_vertex_buffer(Args&&...) const;
		template<typename... Args> auto& cmd_bind_descriptor_sets(Args&&...) const;
		template<typename... Args> auto& cmd_bind_descriptor_set(Args&&...) const;
	};

} // vk

#include "begin.hpp"
#include "end.hpp"
#include "cmd_pipeline_barrier.hpp"
#include "cmd_copy_buffer_to_image.hpp"
#include "cmd_clear_color_image.hpp"
#include "cmd_begin_render_pass.hpp"
#include "cmd_end_render_pass.hpp"
#include "cmd_bind_pipeline.hpp"
#include "cmd_set_viewport.hpp"
#include "cmd_set_scissor.hpp"
#include "cmd_draw.hpp"
#include "cmd_bind_vertex_buffers.hpp"
#include "cmd_bind_vertex_buffer.hpp"
#include "cmd_bind_descriptor_sets.hpp"