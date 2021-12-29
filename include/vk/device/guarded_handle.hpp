#pragma once

#include <core/exchange.hpp>

#include "handle.hpp"
#include "destroy.hpp"
#include "../shared/guarded_handle.hpp"

namespace vk {

	template<>
	struct guarded_handle<vk::device> : vk::guarded_handle_base<vk::device> {
		using base_type = vk::guarded_handle_base<vk::device>;
		using base_type::base_type;
		
		template<typename ObjectType, typename... Args>
		vk::handle<ObjectType> create(Args&&... args) const {
			return handle().create<ObjectType>(forward<Args>(args)...);
		}

		template<typename ObjectType, typename... Args>
		vk::guarded_handle<ObjectType> create_guarded(Args&&... args) const {
			return { handle().create<ObjectType>(forward<Args>(args)...), handle() };
		}

		vk::memory_requirements
		get_buffer_memory_requirements(vk::ordinary_or_guarded_handle<vk::buffer> auto& buffer) const {
			return handle().get_buffer_memory_requirements(buffer);
		}

		template<typename... Args>
		vk::guarded_handle<vk::device_memory> allocate_guarded_memory(Args&&... args) const;

		vk::handle<vk::queue> get_queue(vk::queue_family_index queue_family_index, vk::queue_index queue_index) const {
			return handle().get_queue(queue_family_index, queue_index);
		}

		vk::result try_wait_idle() const {
			return handle().try_wait_idle();
		}

		void wait_idle() const {
			auto result = try_wait_idle();
			if(!result.success()) throw result;
		}
	}; //device_guard
} // vk

#include "../shader/module/guarded_handle.hpp"
#include "../command/pool/guarded_handle.hpp"
#include "../framebuffer/guarded_handle.hpp"
#include "../image/view/guarded_handle.hpp"
#include "../pipeline/layout/guarded_handle.hpp"
#include "../pipeline/guarded_handle.hpp"
#include "../pipeline/graphics/guarded_handle.hpp"
#include "../render_pass/guarded_handle.hpp"
#include "../semaphore/guarded_handle.hpp"
#include "../swapchain/guarded_handle.hpp"
#include "../buffer/guarded_handle.hpp"
#include "../fence/guarded_handle.hpp"
#include "memory/guarded_handle.hpp"