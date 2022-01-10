#pragma once

#include "../../../object/handle/guarded/device_child_base.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::command_buffer> : vk::guarded_device_child_handle_base<vk::command_buffer> {
	private:
		vk::handle<vk::command_pool> m_command_pool;
	public:

		using base_type = vk::guarded_device_child_handle_base<vk::command_buffer>;

		guarded_handle() = default;

		guarded_handle(
			vk::handle<vk::device> device,
			vk::handle<vk::command_pool> command_pool,
			vk::handle<vk::command_buffer> command_buffer
		)
			: base_type{ command_buffer, device }, m_command_pool{ command_pool }
		{}

		guarded_handle(guarded_handle&& other) = default;
		guarded_handle& operator = (guarded_handle&&) = default;

		void free() const {
			vk::free<vk::command_buffer>(device(), command_pool(), ((base_type*)this)->handle());
		}

		const vk::handle<vk::command_pool>& command_pool() const {
			return m_command_pool;
		}

		vk::handle<vk::command_pool>& command_pool() {
			return m_command_pool;
		}

		template<typename... Args>
		requires(sizeof...(Args) > 0) // TODO
		auto begin(Args&&... args) const { return handle().begin(forward<Args>(args)...); }

		template<typename... Args> auto cmd_begin_render_pass(Args&&... args) const { return handle().cmd_begin_render_pass(forward<Args>(args)...); }
		template<typename... Args> auto cmd_bind_pipeline(Args&&... args) const { return handle().cmd_bind_pipeline(forward<Args>(args)...); }
		template<typename... Args> auto cmd_set_viewport(Args&&... args) const { return handle().cmd_set_viewport(forward<Args>(args)...); }
		template<typename... Args> auto cmd_set_scissor(Args&&... args) const { return handle().cmd_set_scissor(forward<Args>(args)...); }
		template<typename... Args> auto cmd_bind_vertex_buffers(Args&&... args) const { return handle().cmd_bind_vertex_buffers(forward<Args>(args)...); }
		template<typename... Args> auto cmd_bind_vertex_buffer(Args&&... args) const { return handle().cmd_bind_vertex_buffer(forward<Args>(args)...); }
		template<typename... Args> auto cmd_draw(Args&&... args) const { return handle().cmd_draw(forward<Args>(args)...); }
		template<typename... Args> auto cmd_end_render_pass(Args&&... args) const { return handle().cmd_end_render_pass(forward<Args>(args)...); }
		template<typename... Args> auto end(Args&&... args) const { return handle().end(forward<Args>(args)...); }
	};

}