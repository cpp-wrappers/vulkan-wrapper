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

#include "../../shared/count.hpp"
#include "../../shared/result.hpp"
#include "../../object/handle/base.hpp"
#include "../physical_device/handle.hpp"

namespace vk {

	struct debug_report_callback;
	struct instance;

	template<>
	struct handle<vk::instance> : vk::handle_base<vk::dispatchable> {

		vk::expected<vk::count>
		enumerate_physical_devices(range::of_value_type<vk::handle<vk::physical_device>> auto&& devices) const {
			uint32 count = (uint32) devices.size();

			vk::result result {
				(int32) vkEnumeratePhysicalDevices(
					(VkInstance) value,
					&count,
					(VkPhysicalDevice*) devices.data()
				)
			};

			if(result.error()) return result;

			return vk::count{ count };
		}

		vk::expected<vk::count>
		get_physical_devices_count() const {
			return enumerate_physical_devices(
				span<vk::handle<vk::physical_device>>{ nullptr, 0 }
			);
		}

		vk::expected<vk::count>
		view_physical_devices(auto&& f, vk::count count) const {
			vk::handle<vk::physical_device> devices_storage[(uint32) count];

			auto result = enumerate_physical_devices(
				span{ devices_storage, (uint32) count }
			);

			if(result.is_expected()) {
				f(span<vk::handle<vk::physical_device>>{ devices_storage, (uint32) result.get_expected() });
			}
			
			return result;
		}

		vk::expected<vk::handle<vk::physical_device>>
		get_first_physical_device() const {
			vk::handle<vk::physical_device> physical_device;
			auto result = enumerate_physical_devices(span{ &physical_device, 1 });
			if(result.is_unexpected()) {
				result.set_handled();
				return result.get_unexpected();
			}
			return physical_device;
		}

		vk::expected<vk::count>
		for_each_physical_device(auto&& f, vk::count count) const {
			return view_physical_devices([&](auto view) {
				for(vk::handle<vk::physical_device> device : view) f(device);
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
		vk::handle<ObjectType> create(Args&&... args) const {
			return (vk::handle<ObjectType>) vk::create<ObjectType>(*this, forward<Args>(args)...);
		}
	}; // instance

} // vk

#include "../debug/report/callback/create.hpp"