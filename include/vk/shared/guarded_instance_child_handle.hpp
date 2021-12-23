#pragma once

#include "../instance/handle.hpp"

namespace vk {
	struct instance;

	template<typename ObjectType>
	struct guarded_instance_child_handle_base : vk::guarded_handle_base<ObjectType> {
	private:
		vk::handle<vk::instance> m_instance;
	public:

		guarded_instance_child_handle_base() = default;

		guarded_instance_child_handle_base(guarded_instance_child_handle_base&& other)
			: vk::guarded_handle_base<ObjectType>{ other.handle }, m_instance{ other.m_instance }
		{}

		const vk::handle<vk::instance>& instance() const {
			return m_instance;
		}
	};
}