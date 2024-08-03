#pragma once

#include "../__internal/count.hpp"
#include "../__internal/object_type.hpp"
#include "../__physical_device/handle.hpp"

#include <integer.hpp>
#include <handle.hpp>
#include <range.hpp>
#include <span.hpp>

namespace vk {

	struct instance;

	template<>
	struct object_type_t<vk::instance> {
		static constexpr auto value = vk::object_type::instance;
	};

} // vk

template<>
struct handle_underlying_t<vk::instance> {
	using type = vk::instance*;
	static constexpr type invalid = nullptr;
};

template<>
struct handle_interface<vk::instance> : handle_interface_base<vk::instance> {

	template<
		range_of<
			is_same_as<handle<vk::physical_device>>.decayed
		> PhysicalDevices
	>
	[[ nodiscard ]] vk::count
	enumerate_physical_devices(PhysicalDevices&&) const;

	[[ nodiscard ]]
	uint32 get_physical_device_count() const {
		return enumerate_physical_devices(
			span<handle<vk::physical_device>>{}
		);
	}

	template<typename Handler>
	uint32 view_physical_devices(vk::count count, Handler&& handler) const {
		handle<vk::physical_device> physical_devices[(uint32)count];
		::span span{ physical_devices, (uint32)count };
		count = enumerate_physical_devices(span);
		span = ::span{ physical_devices, (uint32)count };
		handler(span);
		return (uint32) count;
	}

	template<typename Handler>
	uint32 view_physical_devices(Handler&& handler) const {
		return view_physical_devices(
			get_physical_device_count(),
			forward<Handler>(handler)
		);
	}

	[[ nodiscard ]]
	inline handle<vk::physical_device> get_first_physical_device() const {
		handle<vk::physical_device> physical_device{};
		[[maybe_unused]] auto _
			= enumerate_physical_devices(span{ &physical_device});
		return physical_device;
	}

	/* template<typename F>
	void for_each_physical_device(vk::count count, F&& f) const; */

	/* template<typename F>
	void for_each_physical_device(F&& f) const; */

	/* template<typename ObjectType, typename... Args>
	[[ nodiscard ]]
	handle<ObjectType> create(Args&&... args) const {
		auto result {
			vk::create<ObjectType>(*this, forward<Args>(args)...)
		};

		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}

		return result.get_expected();
	} */

}; // handle_interface<vk::instance>