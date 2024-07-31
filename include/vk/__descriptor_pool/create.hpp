#pragma once

#include "./handle.hpp"
#include "./create_info.hpp"
#include "../__internal/function.hpp"
#include "../__internal/result.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"

namespace vk {

	struct create_descriptor_pool_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		const vk::descriptor_pool_create_info* create_info,
		const void* allocator,
		handle<vk::descriptor_pool>::underlying_type* descriptor_pool
	)> {
		static constexpr auto name = "vkCreateDescriptorPool";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<vk::descriptor_pool_create_flags>.decayed <= 1,
		is_same_as<vk::max_sets>.decayed == 1,
		is_range_of_element_type_satisfying_predicate<
			is_same_as<vk::descriptor_pool_size>.decayed
		> == 1
	>
	vk::expected<handle<vk::descriptor_pool>>
	try_create_descriptor_pool(Args&&... args) {
		tuple a{ args... };

		vk::max_sets max_sets = a.template
			get<is_same_as<vk::max_sets>.decayed>();

		auto& sizes = a.template
			get<is_range_of<is_same_as<vk::descriptor_pool_size>.decayed>>();

		vk::descriptor_pool_create_info ci {
			.max_sets = max_sets,
			.pool_size_count = (uint32) sizes.size(),
			.pool_sizes = sizes.iterator()
		};

		if constexpr (
			(is_same_as<vk::descriptor_pool_create_flags>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.flags = a.template
				get<is_same_as<vk::descriptor_pool_create_flags>.decayed>();
		}

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::descriptor_pool> descriptor_pool;

		vk::result result {
			vk::get_device_function<vk::create_descriptor_pool_function>(
				instance, device
			)(
				device.underlying(),
				&ci,
				nullptr,
				&descriptor_pool.underlying()
			)
		};

		if(result.error()) return result;

		return descriptor_pool;
	}

	template<typename... Args>
	handle<vk::descriptor_pool> create_descriptor_pool(Args&&... args) {
		vk::expected<handle<vk::descriptor_pool>> result
			= vk::try_create_descriptor_pool(forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk