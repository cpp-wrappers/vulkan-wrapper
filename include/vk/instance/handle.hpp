#pragma once

#include "../physical_device/handle.hpp"
#include "../handle/base.hpp"
#include "../count.hpp"
#include "../result.hpp"
#include "../create_or_allocate.hpp"

#include <core/forward.hpp>
#include <core/span.hpp>
#include <core/move.hpp>
#include <core/array.hpp>
#include <core/exchange.hpp>
#include <core/range/of_value_type_same_as.hpp>
#include <core/handle.hpp>

namespace vk {

	struct debug_report_callback;
	struct instance;

	template<>
	inline constexpr bool is_creatable<vk::instance> = true;

} // vk

extern "C" VK_ATTR int32 VK_CALL vkEnumeratePhysicalDevices(
	handle<vk::instance> instance,
	uint32* physical_device_count,
	handle<vk::physical_device>* physical_devices
);

template<>
struct handle<vk::instance> : vk::handle_base<vk::dispatchable> {

	template<range::of<handle<vk::physical_device>> PhysicalDevices>
	vk::count enumerate_physical_devices(PhysicalDevices&& devices) const;

	vk::count inline get_physical_device_count() const;

	template<typename F>
	vk::count view_physical_devices(vk::count count, F&& f) const;

	handle<vk::physical_device> inline get_first_physical_device() const;

	template<typename F>
	vk::count for_each_physical_device(vk::count count, F&& f) const;

	template<typename F>
	vk::count for_each_physical_device(F&& f) const;

	template<typename ObjectType, typename... Args>
	handle<ObjectType> create(Args&&... args) const {
		auto result {
			vk::create<ObjectType>(*this, forward<Args>(args)...)
		};

		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}

		return result.get_expected();
	}

}; // handle<vk::instance>

#include "../debug/report/callback/create.hpp"

#include "enumerate_physical_devices.hpp"
#include "get_physical_device_count.hpp"
#include "view_physical_devices.hpp"
#include "get_first_physical_device.hpp"
#include "for_each_physical_device.hpp"