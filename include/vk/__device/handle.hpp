#pragma once

#include "../__instance/handle.hpp"
#include <integer.hpp>
#include <handle.hpp>
#include <body.hpp>

namespace vk {

	struct device;

	template<>
	struct object_type_t<vk::device> {
		static constexpr auto value = vk::object_type::device;
	};

	enum wait_all : bool {};

} // vk

template<>
struct handle_underlying_t<vk::device> {
	using type = vk::device*;
	static constexpr type invalid = nullptr;
};

template<>
struct body_base<vk::device> {
private:
	handle<vk::instance> instance_{};
public:
	handle<vk::instance>& get_instance_handle() { return instance_; }
};

template<>
struct handle_interface<vk::device> : handle_interface_base<vk::device> {

	/*template<typename ObjectType, typename... Args>
	handle<ObjectType>
	create(Args&&... args) const {
		auto result = vk::create<ObjectType>(*this, forward<Args>(args)...);
		if (result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

	template<typename ObjectType>
	void destroy(handle<ObjectType> handle) const {
		vk::destroy<ObjectType>(*this, handle);
	}

	template<typename ObjectType, typename... Args>
	handle<ObjectType>
	allocate(Args&&... args) const {
		auto result = vk::allocate<ObjectType>(*this, forward<Args>(args)...);
		if (result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

	template<typename ObjectType>
	void free(handle<ObjectType> handle) const {
		vk::free<ObjectType>(*this, handle);
	}

	template<typename ObjectType, typename... Args>
	void free(Args&&... args) const {
		vk::free<ObjectType>(*this, forward<Args>(args)...);
	}

	template<typename... Args>
	handle<vk::queue>
	get_queue(Args&&... args) const;

	vk::result inline try_wait_idle() const;

	void inline wait_idle() const;

	template<typename... Args>
	void update_descriptor_sets(Args&&... args) const;

	template<typename... Args>
	void update_descriptor_set(Args&&... args) const;

	vk::memory_requirements inline
	get_memory_requirements(handle<vk::buffer>) const;

	vk::memory_requirements inline
	get_memory_requirements(handle<vk::image>) const;

	void inline
	bind_memory(
		handle<vk::buffer> buffer,
		handle<vk::device_memory> memory,
		vk::memory_offset offset = {}
	) const;

	void inline
	bind_memory(
		handle<vk::image> image, handle<vk::device_memory> memory
	) const;

	template<typename... Args>
	void map_memory(Args&&... args) const;

	void inline
	unmap_memory(handle<vk::device_memory> device_memory) const;

	template<typename... Args>
	void flush_mapped_memory_range(Args&&... args) const;

	template<typename... Args>
	void wait_for_fence(Args&&... args) const;

	void inline reset_fence(handle<vk::fence> fence) const;

	template<typename... Args>
	vk::count get_swapchain_images(Args&&...) const;

	vk::count inline
	get_swapchain_image_count(handle<vk::swapchain> swapchain) const;

	template<typename... Args>
	vk::expected<vk::image_index>
	try_acquire_next_image(Args&&... args) const;

	decltype(auto)
	view_swapchain_images(
		handle<vk::swapchain> swapchain, vk::count count, auto&& f
	) const;

	template<typename F>
	decltype(auto)
	view_swapchain_images(handle<vk::swapchain> swapchain, F&& f) const;

	template<typename F>
	void
	for_each_swapchain_image(handle<vk::swapchain> swapchain, F&& f) const;

	template<range_of<handle<vk::command_buffer>> CommandBuffers>
	void free_command_buffers(
		handle<vk::command_pool> command_pool, CommandBuffers&& command_buffers
	) const;*/

}; // handle<device>