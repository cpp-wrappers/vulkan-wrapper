#pragma once

#include "./handle.hpp"
#include "./create_info.hpp"
#include "../__device/handle.hpp"
#include "../__instance/handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/result.hpp"
#include "../__internal/unexpected_handler.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct create_swapchain_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		const vk::swapchain_create_info* create_info,
		const void* allocator,
		handle<vk::swapchain>::underlying_type* swapchain
	)> {
		static constexpr auto name = "vkCreateSwapchainKHR";
	};

	struct old_swapchain : handle<vk::swapchain>{};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::surface>>.decayed == 1,
		is_same_as<old_swapchain>.decayed <= 1,
		is_same_as<vk::swapchain_create_flag>.decayed >= 0,
		is_same_as<vk::min_image_count>.decayed == 1,
		is_same_as<vk::format>.decayed == 1,
		is_same_as<vk::color_space>.decayed == 1,
		is_same_as<vk::extent<2>>.decayed == 1,
		is_same_as<vk::image_usages>.decayed == 1,
		is_same_as<vk::sharing_mode>.decayed == 1,
		is_range_of<is_same_as<vk::queue_family_index>.decayed> <= 1,
		is_same_as<vk::surface_transform>.decayed >= 0,
		is_same_as<vk::composite_alpha>.decayed >= 0,
		is_same_as<vk::present_mode>.decayed == 1,
		is_same_as<vk::clipped>.decayed == 1
	>
	vk::expected<handle<vk::swapchain>>
	try_create_swapchain(Args&&... args) {
		tuple a{ args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::surface> surface = a.template
			get<is_same_as<handle<vk::surface>>.decayed>();

		vk::swapchain_create_info ci {
			.surface = surface.underlying(),
			.min_image_count = a.template
				get<is_same_as<vk::min_image_count>.decayed>(),
			.format = a.template get<is_same_as<vk::format>.decayed>(),
			.color_space = a.template get<is_same_as<vk::color_space>.decayed>(),
			.extent = a.template get<is_same_as<vk::extent<2>>.decayed>(),
			.usage = a.template get<is_same_as<vk::image_usages>.decayed>(),
			.sharing_mode = a.template get<is_same_as<vk::sharing_mode>.decayed>(),
			.present_mode = a.template get<is_same_as<vk::present_mode>.decayed>(),
			.clipped = a.template get<is_same_as<vk::clipped>.decayed>()
		};

		a.template for_each([&]<typename Type>(Type& arg) {
			if constexpr(
				is_same_as<vk::swapchain_create_flag>.decayed.for_type<Type>()
			) {
				ci.flags.set(arg);
			}
		});

		a.template for_each([&]<typename Type>(Type& arg) {
			if constexpr(
				is_same_as<vk::surface_transform>.decayed.for_type<Type>()
			) {
				ci.pre_transform.set(arg);
			}
		});

		a.template for_each([&]<typename Type>(Type& arg) {
			if constexpr(
				is_same_as<vk::composite_alpha>.decayed.for_type<Type>()
			) {
				ci.composite_alpha.set(arg);
			}
		});

		if constexpr (types<Args...>::template
			count_of<is_range_of<
				is_same_as<vk::queue_family_index>.decayed
			>> > 0
		) {
			auto& family_indices = a.template
				get<is_range_of<is_same_as<vk::queue_family_index>.decayed>>();

			ci.queue_family_index_count =
				vk::queue_family_index_count {
					(uint32) family_indices.size()
				};

			ci.queue_family_indices =
				vk::queue_family_indices{ family_indices.iterator() };
		}

		if constexpr (
			(is_same_as<vk::old_swapchain>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.old_swapchain = a.template
				get<is_same_as<vk::old_swapchain>.decayed>().underlying();
		}

		handle<vk::swapchain> swapchain;

		vk::result result {
			vk::get_device_function<vk::create_swapchain_function>(
				instance, device
			)(
				device.underlying(),
				&ci,
				nullptr,
				&swapchain.underlying()
			)
		};

		if(result.error()) return result;

		return swapchain;

	}

	template<typename... Args>
	handle<vk::swapchain> create_swapchain(Args&&... args) {
		vk::expected<handle<vk::swapchain>> result
			= vk::try_create_swapchain(forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk