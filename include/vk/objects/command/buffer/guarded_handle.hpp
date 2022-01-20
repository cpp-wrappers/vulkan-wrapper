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
		auto& begin(Args&&... args) const {
			handle().begin(forward<Args>(args)...);
			return *this;
		}

		template<typename... Args> auto& cmd_pipeline_barrier(Args&&... args) const { handle().cmd_pipeline_barrier(forward<Args>(args)...); return *this; }
		template<typename... Args> auto& cmd_copy_buffer_to_image(Args&&... args) const { handle().cmd_copy_buffer_to_image(forward<Args>(args)...); return *this; }
		template<typename... Args> auto& cmd_begin_render_pass(Args&&... args) const { handle().cmd_begin_render_pass(forward<Args>(args)...); return *this; }
		template<typename... Args> auto& cmd_bind_pipeline(Args&&... args) const { handle().cmd_bind_pipeline(forward<Args>(args)...); return *this; }
		template<typename... Args> auto& cmd_set_viewport(Args&&... args) const { handle().cmd_set_viewport(forward<Args>(args)...); return *this; }
		template<typename... Args> auto& cmd_set_scissor(Args&&... args) const { handle().cmd_set_scissor(forward<Args>(args)...); return *this; }
		template<typename... Args> auto& cmd_bind_vertex_buffers(Args&&... args) const { handle().cmd_bind_vertex_buffers(forward<Args>(args)...); return *this; }
		template<typename... Args> auto& cmd_bind_vertex_buffer(Args&&... args) const { handle().cmd_bind_vertex_buffer(forward<Args>(args)...); return *this; }
		template<typename... Args> auto& cmd_bind_descriptor_sets(Args&&... args) const { handle().cmd_bind_descriptor_sets(forward<Args>(args)...); return *this; }
		template<typename... Args> auto& cmd_bind_descriptor_set(Args&&... args) const { handle().cmd_bind_descriptor_set(forward<Args>(args)...); return *this; }
		template<typename... Args> auto& cmd_draw(Args&&... args) const { handle().cmd_draw(forward<Args>(args)...); return *this; }
		template<typename... Args> auto& cmd_end_render_pass(Args&&... args) const { handle().cmd_end_render_pass(forward<Args>(args)...); return *this; }
		template<typename... Args> auto& end(Args&&... args) const { handle().end(forward<Args>(args)...); return *this; }
	};

} // vk