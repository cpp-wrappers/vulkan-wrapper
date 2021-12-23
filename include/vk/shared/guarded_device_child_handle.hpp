#pragma once

#include "../device/handle.hpp"

namespace vk {
	struct device;

	template<typename ObjectType>
	struct guarded_device_child_handle_base : vk::guarded_handle_base<ObjectType> {
	private:
		vk::handle<vk::device> m_device;
	public:

		guarded_device_child_handle_base() = default;

		guarded_device_child_handle_base(guarded_device_child_handle_base&& other)
			: vk::guarded_handle_base<ObjectType>{ other.handle }, m_device{ other.m_device }
		{}

		const vk::handle<vk::device>& device() const {
			return m_device;
		}
	};
}