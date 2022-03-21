#pragma once

#include "handle.hpp"
#include "create.hpp"
#include "destroy.hpp"

namespace vk {
	
	class debug_report_callback_guard;

} // vk

template<>
struct guarded_handle<vk::instance> : vk::guarded_handle_base<vk::instance> {

	::handle<vk::physical_device> get_first_physical_device() const {
		return handle().get_first_physical_device();
	}

	template<typename F>
	auto for_each_physical_device(F&& f) const {
		return handle().for_each_physical_device(forward<F>(f));
	}

	template<typename ObjectType, typename... Args>
	::handle<ObjectType> create(Args&&... args) const {
		return { handle().create<ObjectType>(forward<Args>(args)...) };
	}

	template<typename ObjectType, typename... Args>
	guarded_handle<ObjectType> create_guarded(Args&&... args) const {
		return {
			handle().create<ObjectType>(forward<Args>(args)...), handle()
		};
	}

};

template<typename... Args>
guarded_handle<vk::instance> create_guarded_instance(Args&&... args) {
	vk::expected<handle<vk::instance>> result =
		vk::create<vk::instance>(forward<Args>(args)...);

	if(result.is_unexpected()) {
		vk::unexpected_handler(result.get_unexpected());
	}

	return { result.get_expected() };
}

#include "../debug/report/callback/guarded_handle.hpp"