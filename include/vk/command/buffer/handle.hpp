#pragma once

#include "../../shared/handle.hpp"
#include "../../shared/guarded_handle.hpp"
#include "../../shared/result.hpp"

namespace vk {

	struct command_buffer;

	template<>
	constexpr inline bool is_allocatable<vk::command_buffer> = true;

	template<>
	struct vk::handle<vk::command_buffer> : vk::handle_base<vk::dispatchable> {

		template<typename... Args> vk::result try_begin(Args&&...) const;
		template<typename... Args> void begin(Args&&...) const;

		inline vk::result try_end() const;
		inline void end() const;

		template<typename... Args>
		void cmd_pipeline_barrier(Args&&...) const;

		template<typename... Args>
		void cmd_clear_color_image(Args&&...) const;

		template<typename... Args> void cmd_begin_render_pass(Args&&...) const;
		inline void cmd_end_render_pass() const;

		template<typename... Args> void cmd_bind_pipeline(Args&&...) const;

		template<typename... Args> void cmd_set_viewport(Args&&...) const;

		template<typename... Args> void cmd_set_scissor(Args&&...) const;

		template<typename... Args> void cmd_draw(Args&&...) const;

		template<typename... Args> void cmd_bind_vertex_buffers(Args&&...) const;
		template<typename... Args> void cmd_bind_vertex_buffer(Args&&...) const;
	};

} // vk

#include "begin.hpp"

template<typename... Args>
vk::result vk::handle<vk::command_buffer>::try_begin(Args&&... args) const {
	return vk::try_begin_command_buffer(*this, forward<Args>(args)...);
}

template<typename... Args>
void vk::handle<vk::command_buffer>::begin(Args&&... args) const {
	vk::begin_command_buffer(*this, forward<Args>(args)...);
}

#include "end.hpp"

inline vk::result vk::handle<vk::command_buffer>::try_end() const {
	return vk::try_end_command_buffer(*this);
}

inline void vk::handle<vk::command_buffer>::end() const {
	vk::end_command_buffer(*this);
}

#include "cmd_pipeline_barrier.hpp"


template<typename... Args>
void vk::handle<vk::command_buffer>::cmd_pipeline_barrier(Args&&... args) const {
	vk::cmd_pipeline_barrier(*this, forward<Args>(args)...);
}

#include "cmd_clear_color_image.hpp"

template<typename... Args>
void vk::handle<vk::command_buffer>::cmd_clear_color_image(Args&&... args) const {
	vk::cmd_clear_color_image(*this, forward<Args>(args)...);
}

#include "cmd_begin_render_pass.hpp"

template<typename... Args>
void vk::handle<vk::command_buffer>::cmd_begin_render_pass(Args&&... args) const {
	vk::cmd_begin_render_pass(*this, forward<Args>(args)...);
}

#include "cmd_end_render_pass.hpp"

inline void vk::handle<vk::command_buffer>::cmd_end_render_pass() const {
	vk::cmd_end_render_pass(*this);
}

#include "cmd_bind_pipeline.hpp"

template<typename... Args>
void vk::handle<vk::command_buffer>::cmd_bind_pipeline(Args&&... args) const {
	vk::cmd_bind_pipeline(*this, forward<Args>(args)...);
}

#include "cmd_set_viewport.hpp"

template<typename... Args>
void vk::handle<vk::command_buffer>::cmd_set_viewport(Args&&... args) const {
	vk::cmd_set_viewport(*this, forward<Args>(args)...);
}

#include "cmd_set_scissor.hpp"

template<typename... Args>
void vk::handle<vk::command_buffer>::cmd_set_scissor(Args&&... args) const {
	vk::cmd_set_scissor(*this, forward<Args>(args)...);
}

#include "cmd_draw.hpp"

template<typename... Args>
void vk::handle<vk::command_buffer>::cmd_draw(Args&&... args) const {
	vk::cmd_draw(*this, forward<Args>(args)...);
}

#include "cmd_bind_vertex_buffers.hpp"

template<typename... Args> 
void vk::handle<vk::command_buffer>::cmd_bind_vertex_buffers(Args&&... args) const {
	vk::cmd_bind_vertex_buffers(*this, forward<Args>(args)...);
}

#include "cmd_bind_vertex_buffer.hpp"

template<typename... Args> 
void vk::handle<vk::command_buffer>::cmd_bind_vertex_buffer(Args&&... args) const {
	vk::cmd_bind_vertex_buffer(*this, forward<Args>(args)...);
}