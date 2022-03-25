#pragma once

#include "base.hpp"
#include "../../instance/handle.hpp"

namespace vk {

	struct instance;

	template<typename ObjectType>
	struct guarded_instance_child_handle_base : guarded_handle_base<ObjectType> {
	private:
		handle<vk::instance> m_instance;
	public:
		using base_type = guarded_handle_base<ObjectType>;

		guarded_instance_child_handle_base() = default;

		guarded_instance_child_handle_base(
			::handle<ObjectType> handle,
			::handle<vk::instance> instance
		) :
			base_type{ handle }, m_instance{ instance }
		{}

		guarded_instance_child_handle_base(
			guarded_instance_child_handle_base&& other
		) = default;

		guarded_instance_child_handle_base& operator = (
			guarded_instance_child_handle_base&& other
		) = default;

		void destroy() const requires vk::is_creatable<ObjectType> {
			vk::destroy<ObjectType>(instance(), ((base_type*)this)->handle());
		}

		const handle<vk::instance>& instance() const &  { return m_instance; }
		      handle<vk::instance>& instance()       &  { return m_instance; }
		      handle<vk::instance>  instance() const && { return m_instance; }
		      handle<vk::instance>  instance()       && { return m_instance; }
	};

} // vk