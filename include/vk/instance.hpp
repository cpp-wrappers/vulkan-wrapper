#pragma once

#include <core/integer.hpp>
#include <core/forward.hpp>
#include <core/span.hpp>

#include "core/elements/one_of.hpp"
#include "core/type/is_constructible_from.hpp"
#include "instance/enumerate_physical_devices.hpp"
#include "instance/create.hpp"
#include "instance/destroy.hpp"
#include "shared/result.hpp"

namespace vk {
	struct physical_device;

	class instance {
		void* m_instance;

	public:

		template<typename... Args>
		requires requires(Args... args) { vk::try_create_instance(args...); }
		instance(Args... args)
			: m_instance{ vk::internal::try_create_instance(args...).template get<vk::internal::instance*>() }
		{}

		~instance() {
			vk::internal::destroy_instance(m_instance);
		}

		template<typename... Args>
		requires requires(vk::internal::instance* i, Args... args) { vk::internal::try_enumerate_physical_devices(i, args...); }
		elements::one_of<vk::result, vk::count>
		try_enumerate_physical_devices(const Args&... args) const {
			return vk::internal::try_enumerate_physical_devices(m_instance, args...);
		}

		template<typename... Args>
		vk::count enumerate_physical_devices(const Args... args) const {
			return try_enumerate_physical_devices(args...).template get<vk::count>();
		}

		elements::one_of<vk::result, vk::count>
		try_get_physical_devices_count() const {
			return try_enumerate_physical_devices(
				span<vk::internal::physical_device*>{ nullptr, 0 }
			);
		}

		vk::count
		get_physical_devices_count() const {
			return try_get_physical_devices_count().get<vk::count>();
		}

		template<typename F>
		elements::one_of<vk::result, vk::count>
		try_view_physical_devices(vk::count count, F&& f) const {
			vk::internal::physical_device* devices_storage[(uint32) count];
			auto result = try_enumerate_physical_devices(
				span<vk::internal::physical_device*>{ devices_storage, (uint32) count }
			);
			if(!result.is_current<vk::result>())
				f(span<vk::physical_device>{ (vk::physical_device*) devices_storage, (uint32) result.get<vk::count>() });
			return result;
		}

		template<typename F>
		elements::one_of<vk::result, vk::count>
		try_view_physical_devices(F&& f) const {
			auto result = try_get_physical_devices_count();
			if(result.is_current<vk::result>()) return result;
			return try_view_physical_devices(result.get<vk::count>(), forward<F>(f));
		}

		elements::one_of<vk::result, vk::physical_device*>
		try_get_first_physical_device() const {
			vk::physical_device* ptr;

			auto result = try_view_physical_devices(vk::count{ 1u }, [&](auto devices) {
				ptr = &devices[0];
			});

			if(result.is_current<vk::result>())
				return result.get<vk::result>();
			return ptr;
		}

		vk::physical_device&
		get_first_physical_device() const {
			return * try_get_first_physical_device().get<vk::physical_device*>();
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
	}; // instance

} // vk