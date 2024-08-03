#pragma once

#include "./handle.hpp"
#include "./allocate_info.hpp"
#include "../__internal/function.hpp"
#include "../__internal/result.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"

namespace vk {

	struct allocate_descriptor_sets_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		const vk::descriptor_set_allocate_info* allocate_info,
		handle<vk::descriptor_set>*             descriptor_sets
	)> {
		static constexpr auto name = "vkAllocateDescriptorSets";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::descriptor_pool>>.decayed == 1,
		is_range_of<is_same_as<handle<vk::descriptor_set_layout>>.decayed> == 1,
		is_range_of<is_same_as<handle<vk::descriptor_set>>.decayed> == 1
	>
	vk::result try_allocate_descriptor_sets(Args&&... args) {
		tuple a{ args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::descriptor_pool> pool = a.template
			get<is_same_as<handle<vk::descriptor_pool>>.decayed>();

		auto& sets = a.template
			get<is_range_of<is_same_as<handle<vk::descriptor_set>>.decayed>>();
		auto& layouts = a.template
			get<is_range_of<is_same_as<handle<vk::descriptor_set_layout>>.decayed>>();

		vk::descriptor_set_allocate_info ai {
			.descriptor_pool = pool.underlying(),
			.descriptor_set_count{ (uint32) layouts.size() },
			.descriptor_set_layouts =
				(const handle<vk::descriptor_set_layout>::underlying_type*)
				layouts.iterator()
		};

		return {
			vk::get_device_function<vk::allocate_descriptor_sets_function>(
				instance, device
			)(
				device.underlying(),
				&ai,
				sets.iterator()
			)
		};
	}


	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>> == 1,
		is_same_as<handle<vk::device>> == 1,
		is_same_as<handle<vk::descriptor_pool>> == 1,
		is_same_as<handle<vk::descriptor_set_layout>> == 1
	>
	vk::expected<handle<descriptor_set>>
	try_allocate_descriptor_set(Args... args) {
		tuple<Args...> a{ args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>>();

		handle<vk::descriptor_pool> pool = a.template
			get<is_same_as<handle<vk::descriptor_pool>>>();
		
		handle<vk::descriptor_set_layout> layout = a.template
			get<is_same_as<handle<vk::descriptor_set_layout>>>();
		
		handle<vk::descriptor_set> set;

		vk::result result = vk::try_allocate_descriptor_sets(
			instance,
			device,
			pool,
			array{ layout },
			span{ &set }
		);

		if(result.error()) return result;

		return set;
	}

	template<typename... Args>
	handle<vk::descriptor_set> allocate_descriptor_set(Args&&... args) {
		vk::expected<handle<vk::descriptor_set>> result
			= vk::try_allocate_descriptor_set(forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk