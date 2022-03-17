#pragma once

#include "handle.hpp"
#include "destroy.hpp"

#include "vk/handle/guarded/base.hpp"
#include "vk/default_unexpected_handler.hpp"

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

		template<typename ObjectType, typename... Args>
		vk::handle<ObjectType> allocate(Args&&... args) const {
			return handle().allocate<ObjectType>(forward<Args>(args)...);
		}

		template<typename ObjectType, typename... Args>
		vk::guarded_handle<ObjectType> allocate_guarded(Args&&... args) const {
			return { handle().allocate<ObjectType>(forward<Args>(args)...), handle() };
		}

		vk::handle<vk::queue> get_queue(vk::queue_family_index queue_family_index, vk::queue_index queue_index) const {
			return handle().get_queue(queue_family_index, queue_index);
		}

		vk::result try_wait_idle() const {
			return handle().try_wait_idle();
		}

		void wait_idle() const {
			auto result = try_wait_idle();
			if(result.error()) vk::default_unexpected_handler(result);
		}

		template<typename... Args>
		void update_descriptor_sets(Args&&... args) const {
			handle().update_descriptor_sets(forward<Args>(args)...);
		}

		template<typename... Args>
		void update_descriptor_set(Args&&... args) const {
			handle().update_descriptor_set(forward<Args>(args)...);
		}

	}; //device_guard

} // vk

#include "../shader/module/guarded_handle.hpp"
#include "../command/pool/guarded_handle.hpp"
#include "../framebuffer/guarded_handle.hpp"
#include "../image/guarded_handle.hpp"
#include "../image/view/guarded_handle.hpp"
#include "../pipeline/layout/guarded_handle.hpp"
#include "../pipeline/guarded_handle.hpp"
#include "../render_pass/guarded_handle.hpp"
#include "../semaphore/guarded_handle.hpp"
#include "../swapchain/guarded_handle.hpp"
#include "../buffer/guarded_handle.hpp"
#include "../buffer/view/guarded_handle.hpp"
#include "../fence/guarded_handle.hpp"
#include "../sampler/guarded_handle.hpp"
#include "../descriptor/set/layout/guarded_handle.hpp"
#include "../descriptor/pool/guarded_handle.hpp"
#include "../acceleration_structure/guarded_handle.hpp"
#include "memory/guarded_handle.hpp"