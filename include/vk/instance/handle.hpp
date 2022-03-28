#pragma once

#include "../physical_device/handle.hpp"
#include "../handle/base.hpp"
#include "../count.hpp"
#include "../result.hpp"

#include <core/forward.hpp>
#include <core/span.hpp>
#include <core/move.hpp>
#include <core/array.hpp>
#include <core/exchange.hpp>
#include <core/range/of_value_type_same_as.hpp>

namespace vk {

	struct debug_report_callback;
	struct instance;

} // vk

extern "C" VK_ATTR int32 VK_CALL vkEnumeratePhysicalDevices(
	handle<vk::instance> instance,
	uint32* physical_device_count,
	handle<vk::physical_device>* physical_devices
);

template<>
struct handle<vk::instance> : vk::handle_base<vk::dispatchable> {

	template<range::of<handle<vk::physical_device>> DevicesRange>
	vk::expected<vk::count>
	enumerate_physical_devices(DevicesRange&& devices) const {
		uint32 count = (uint32) devices.size();

		vk::result result {
			vkEnumeratePhysicalDevices(
				*this,
				&count,
				devices.data()
			)
		};

		if(result.error()) return result;

		return vk::count{ count };
	}

	vk::expected<vk::count>
	get_physical_devices_count() const {
		return enumerate_physical_devices(
			span<handle<vk::physical_device>>{ nullptr, 0 }
		);
	}

	vk::expected<vk::count>
	view_physical_devices(auto&& f, vk::count count) const {
		handle<vk::physical_device> devices_storage[(uint32) count];

		auto result = enumerate_physical_devices(
			span{ devices_storage, (uint32) count }
		);

		if(result.is_expected()) {
			f(span<handle<vk::physical_device>> {
				devices_storage,
				(uint32) result.get_expected()
			});
		}
		
		return result;
	}

	vk::expected<handle<vk::physical_device>>
	try_get_first_physical_device() const {
		handle<vk::physical_device> physical_device;
		auto result = enumerate_physical_devices(span{ &physical_device, 1 });
		if(result.is_unexpected()) {
			return result.get_unexpected();
		}
		return physical_device;
	}

	handle<vk::physical_device>
	get_first_physical_device() const {
		auto result = try_get_first_physical_device();
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

	vk::expected<vk::count>
	for_each_physical_device(auto&& f, vk::count count) const {
		return view_physical_devices([&](auto view) {
			for(handle<vk::physical_device> device : view) f(device);
		}, count);
	}

	template<typename F>
	vk::expected<vk::count>
	for_each_physical_device(F&& f) const {
		auto result = get_physical_devices_count();
		if(result.is_unexpected()) return result;
		return for_each_physical_device(
			forward<F>(f),
			result.get_expected()
		);
	}

	template<typename ObjectType, typename... Args>
	handle<ObjectType> create(Args&&... args) const {
		auto result = vk::create<ObjectType>(*this, forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

}; // handle<vk::instance>

#include "../debug/report/callback/create.hpp"