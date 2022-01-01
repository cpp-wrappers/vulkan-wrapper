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

		template<typename... Args> vk::result try_begin(Args&&... args) const;
		template<typename... Args> void begin(Args&&... args) const;

		vk::result try_end() const;
		void end() const;

		template<typename... Args>
		void cmd_pipeline_barrier(Args&&... args) const;

		template<typename... Args>
		void cmd_clear_color_image(Args&&... args) const;

		template<typename... Args> void cmd_begin_render_pass(Args&&... args) const;

		void cmd_bind_pipeline(vk::ordinary_or_guarded_handle<vk::graphics_pipeline> auto& pipeline) const {
			vkCmdBindPipeline(
				(VkCommandBuffer) vk::get_handle_value(*this),
				VK_PIPELINE_BIND_POINT_GRAPHICS,
				(VkPipeline) vk::get_handle_value(pipeline)
			);
		}

		void cmd_set_viewport(vk::viewport viewport) const {
			vkCmdSetViewport(
				(VkCommandBuffer) vk::get_handle_value(*this),
				0,
				1,
				(VkViewport*) &viewport
			);
		}

		void cmd_set_viewport(vk::extent<2> viewport) const {
			return cmd_set_viewport(vk::viewport {
				.width = (float)viewport.width(),
				.height = (float)viewport.height()
			});
		}

		void cmd_set_scissor(vk::rect2d scissor) const {
			vkCmdSetScissor(
				(VkCommandBuffer) vk::get_handle_value(*this),
				0,
				1,
				(VkRect2D*) &scissor
			);
		}

		void cmd_set_scissor(vk::extent<2> scissor) const {
			cmd_set_scissor(vk::rect2d {
				vk::offset<2>{ 0, 0 },
				scissor
			});
		}

		template<typename... Args> void cmd_draw(Args&&... args) const;

		void cmd_end_render_pass() const {
			vkCmdEndRenderPass((VkCommandBuffer) vk::get_handle_value(*this));
		}

		template<typename... Args> void cmd_bind_vertex_buffers(Args&&... args) const;
		template<typename... Args> void cmd_bind_vertex_buffer(Args&&... args) const;
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

vk::result vk::handle<vk::command_buffer>::try_end() const {
	return vk::try_end_command_buffer(*this);
}

void vk::handle<vk::command_buffer>::end() const {
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