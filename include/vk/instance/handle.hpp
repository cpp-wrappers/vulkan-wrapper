#pragma once

#include <core/integer.hpp>
#include <core/forward.hpp>
#include <core/span.hpp>
#include <core/elements/one_of.hpp>
#include <core/range/of_value_type.hpp>
#include <core/move.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/array.hpp>
#include <core/exchange.hpp>

#include "../shared/count.hpp"
#include "../shared/result.hpp"
#include "../shared/handle.hpp"
#include "../physical_device/handle.hpp"

namespace vk {

	struct debug_report_callback;
	struct instance;

	template<>
	struct handle<vk::instance> : vk::handle_base<vk::dispatchable> {
		elements::one_of<vk::result, vk::count>
		try_enumerate_physical_devices(range::of_value_type<vk::handle<vk::physical_device>> auto&& devices) const {
			uint32 count = (uint32) devices.size();

			vk::result result {
				(int32) vkEnumeratePhysicalDevices(
					(VkInstance) value,
					&count,
					(VkPhysicalDevice*) devices.data()
				)
			};

			if(result.success()) return vk::count{ count };
			return result;
		}

		template<typename... Args>
		vk::count enumerate_physical_devices(const Args... args) const {
			return try_enumerate_physical_devices(args...).template get<vk::count>();
		}

		elements::one_of<vk::result, vk::count>
		try_get_physical_devices_count() const {
			return try_enumerate_physical_devices(
				span<vk::handle<vk::physical_device>>{ nullptr, 0 }
			);
		}

		vk::count get_physical_devices_count() const {
			return try_get_physical_devices_count().get<vk::count>();
		}

		elements::one_of<vk::result, vk::count>
		try_view_physical_devices(vk::count count, auto&& f) const {
			vk::handle<vk::physical_device> devices_storage[(uint32) count];

			elements::one_of<vk::result, vk::count> result = try_enumerate_physical_devices(
				span{ devices_storage, (uint32) count }
			);

			if(!result.is_current<vk::result>())
				f(span<vk::handle<vk::physical_device>>{ devices_storage, (uint32) result.get<vk::count>() });
			return result;
		}

		template<typename F>
		elements::one_of<vk::result, vk::count>
		try_view_physical_devices(F&& f) const {
			auto result = try_get_physical_devices_count();
			if(result.is_current<vk::result>()) return result;
			return try_view_physical_devices(result.get<vk::count>(), forward<F>(f));
		}

		elements::one_of<vk::result, vk::handle<vk::physical_device>>
		try_get_first_physical_device() const {
			vk::handle<vk::physical_device> physical_device;
			auto result = try_enumerate_physical_devices(span{ &physical_device, 1 });
			if(result.is_current<vk::result>()) return result.get<vk::result>();
			return physical_device;
		}

		vk::handle<vk::physical_device> get_first_physical_device() const {
			return try_get_first_physical_device().get<vk::handle<vk::physical_device>>();
		}

		elements::one_of<vk::result, vk::count>
		try_for_each_physical_device(auto&& f) const {
			return try_view_physical_devices([&](auto view) {
				for(vk::physical_device& device : view) f(device);
			});
		}

		template<typename F>
		vk::count
		for_each_physical_device(F&& f) const {
			return try_for_each_physical_device(forward<F>(f)).template get<vk::count>();
		}

		template<typename... Args>
		elements::one_of<vk::result, vk::handle<vk::debug_report_callback>>
		try_create_debug_report_callback(Args&&... args) const;

		template<typename... Args>
		vk::handle<vk::debug_report_callback> create_debug_report_callback(Args&&... args) const;
	}; // instance

} // vk

#include "../debug/report/callback/create.hpp"

template<typename... Args>
elements::one_of<vk::result, vk::handle<vk::debug_report_callback>>
vk::handle<vk::instance>::try_create_debug_report_callback(Args&&... args) const {
	return vk::try_create_debug_report_callback(*this, forward<Args>(args)...);
}

template<typename... Args>
vk::handle<vk::debug_report_callback> vk::handle<vk::instance>::create_debug_report_callback(Args&&... args) const {
	return vk::create_debug_report_callback(*this, forward<Args>(args)...);
}