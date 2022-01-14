#pragma once

#include "../../../objects/instance/handle.hpp"

namespace vk {

	struct instance;

	template<typename ObjectType>
	struct guarded_instance_child_handle_base : vk::guarded_handle_base<ObjectType> {
	private:
		vk::handle<vk::instance> m_instance;
	public:
		using base_type = vk::guarded_handle_base<ObjectType>;

		guarded_instance_child_handle_base() = default;

		guarded_instance_child_handle_base(vk::handle<ObjectType> handle, vk::handle<vk::instance> instance)
			: base_type{ handle }, m_instance{ instance }
		{}

		guarded_instance_child_handle_base(guarded_instance_child_handle_base&& other) = default;
		guarded_instance_child_handle_base& operator = (guarded_instance_child_handle_base&& other) = default;

		void destroy() const {
			vk::destroy<ObjectType>(instance(), ((base_type*)this)->handle());
		}

		const vk::handle<vk::instance>& instance() const &  { return m_instance; }
		      vk::handle<vk::instance>& instance()       &  { return m_instance; }
		      vk::handle<vk::instance>  instance() const && { return m_instance; }
		      vk::handle<vk::instance>  instance()       && { return m_instance; }
	};

} // vk