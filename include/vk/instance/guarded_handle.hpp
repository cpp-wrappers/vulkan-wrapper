#pragma once

#include "handle.hpp"
#include "create.hpp"
#include "../shared/guarded_handle.hpp"
#include "destroy.hpp"

namespace vk {
	class debug_report_callback_guard;

	template<>
	struct guarded_handle<vk::instance> : vk::guarded_handle_base<vk::instance> {

		vk::handle<vk::physical_device> get_first_physical_device() const {
			return handle().get_first_physical_device();
		}

		template<typename F>
		auto for_each_physical_device(F&& f) const {
			return handle().for_each_physical_device(forward<F>(f));
		}

		template<typename ObjectType, typename... Args>
		vk::guarded_handle<ObjectType> create_guarded(Args&&... args) const {
			return { handle().create<ObjectType>(forward<Args>(args)...), handle() };
		}

	};

	template<typename... Args>
	vk::guarded_handle<vk::instance> create_guarded_instance(Args&&... args) {
		return { (vk::handle<vk::instance>) vk::create<vk::instance>(forward<Args>(args)...) };
	}

} // vk

#include "../debug/report/callback/guarded_handle.hpp"