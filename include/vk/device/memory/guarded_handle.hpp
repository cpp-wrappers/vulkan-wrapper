#pragma once

#include "../../shared/guarded_device_child_handle.hpp"
#include "../../shared/result.hpp"
#include "free.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::device_memory> : vk::guarded_device_child_handle_base<vk::device_memory> {
		using base_type = vk::guarded_device_child_handle_base<vk::device_memory>;

		using base_type::base_type;

		template<typename... Args> vk::result try_map(Args&&...) const;
		template<typename... Args> void map(Args&&...) const;

		inline void unmap() const;

		template<typename... Args> void flush_mapped(Args&&...) const;
	};

} // vk

#include "map.hpp"

template<typename... Args>
vk::result vk::guarded_handle<vk::device_memory>::try_map(Args&&... args) const {
	return vk::try_map_device_memory(device(), handle(), forward<Args>(args)...);
}

template<typename... Args>
void vk::guarded_handle<vk::device_memory>::map(Args&&... args) const {
	vk::map_device_memory(device(), handle(), forward<Args>(args)...);
}

#include "unmap.hpp"

inline void vk::guarded_handle<vk::device_memory>::unmap() const {
	vk::unmap_device_memory(device(), handle());
}

#include "flush_mapped_range.hpp"

template<typename... Args>
void vk::guarded_handle<vk::device_memory>::flush_mapped(Args&&... args) const {
	vk::flush_mapped_device_memory_range(device(), handle(), forward<Args>(args)...);
}