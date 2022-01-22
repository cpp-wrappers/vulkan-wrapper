#pragma once

#include "../../destroy_or_free.hpp"
#include "../../../objects/device/handle.hpp"

namespace vk {

	struct device;

	template<typename ObjectType>
	struct guarded_device_child_handle_base : vk::guarded_handle_base<ObjectType> {
	private:
		vk::handle<vk::device> m_device;
	public:
		using base_type = vk::guarded_handle_base<ObjectType>;

		guarded_device_child_handle_base() = default;

		guarded_device_child_handle_base(vk::handle<ObjectType> handle, vk::handle<vk::device> device)
			: base_type{ handle }, m_device { device }
		{}

		guarded_device_child_handle_base(guarded_device_child_handle_base&& other) = default;
		guarded_device_child_handle_base& operator = (guarded_device_child_handle_base&& other) = default;

		void destroy() const requires vk::is_creatable<ObjectType> {
			vk::destroy<ObjectType>(device(), ((base_type*)this)->handle());
		}

		void free() const requires vk::is_allocatable<ObjectType> {
			vk::free<ObjectType>(device(), ((base_type*)this)->handle());
		}

		const vk::handle<vk::device>& device() const &  { return m_device; }
		      vk::handle<vk::device>& device()       &  { return m_device; }
		      vk::handle<vk::device>  device() const && { return m_device; }
		      vk::handle<vk::device>  device()       && { return m_device; }
	};

} // vk