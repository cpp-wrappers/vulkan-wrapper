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

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::surface>> == 1,
		count_of_decayed_same_as<handle<vk::swapchain>> <= 1,
		count_of_decayed_same_as<vk::swapchain_create_flag> >= 0,
		count_of_decayed_same_as<vk::min_image_count> == 1,
		count_of_decayed_same_as<vk::format> == 1,
		count_of_decayed_same_as<vk::color_space> == 1,
		count_of_decayed_same_as<vk::extent<2>> == 1,
		count_of_decayed_same_as<vk::image_usages> == 1,
		count_of_decayed_same_as<vk::sharing_mode> == 1,
		count_of_range_of_decayed<vk::queue_family_index> <= 1,
		count_of_decayed_same_as<vk::surface_transform> >= 0,
		count_of_decayed_same_as<vk::composite_alpha> >= 0,
		count_of_decayed_same_as<vk::present_mode> == 1,
		count_of_decayed_same_as<vk::clipped> == 1
	>
	vk::expected<handle<vk::swapchain>>
	try_create_swapchain(Args&&... args) {
		tuple a{ args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::surface> surface = a.template
			get_decayed_same_as<handle<vk::surface>>();

		vk::swapchain_create_info ci {
			.surface = surface.underlying(),
			.min_image_count = a.template
				get_decayed_same_as<vk::min_image_count>(),
			.format = a.template get_decayed_same_as<vk::format>(),
			.color_space = a.template get_decayed_same_as<vk::color_space>(),
			.extent = a.template get_decayed_same_as<vk::extent<2>>(),
			.usage = a.template get_decayed_same_as<vk::image_usages>(),
			.sharing_mode = a.template get_decayed_same_as<vk::sharing_mode>(),
			.present_mode = a.template get_decayed_same_as<vk::present_mode>(),
			.clipped = a.template get_decayed_same_as<vk::clipped>()
		};

		a.template for_each([&]<typename Type>(Type& arg) {
			if constexpr(
				is_same_as<vk::swapchain_create_flag>
				.while_decayed
				.for_type<Type>()
			) {
				ci.flags.set(arg);
			}
		});

		a.template for_each([&]<typename Type>(Type& arg) {
			if constexpr(
				is_same_as<vk::surface_transform>
				.while_decayed
				.for_type<Type>()
			) {
				ci.pre_transform.set(arg);
			}
		});

		a.template for_each([&]<typename Type>(Type& arg) {
			if constexpr(
				is_same_as<vk::composite_alpha>
				.while_decayed
				.for_type<Type>()
			) {
				ci.composite_alpha.set(arg);
			}
		});

		if constexpr (types<Args...>::template
			count_of_range_of_decayed<vk::queue_family_index> > 0
		) {
			auto& family_indices = a.template
				get_range_of_decayed<vk::queue_family_index>();

			ci.queue_family_index_count =
				vk::queue_family_index_count {
					(uint32) family_indices.size()
				};

			ci.queue_family_indices =
				vk::queue_family_indices{ family_indices.iterator() };
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<handle<vk::swapchain>> > 0
		) {
			ci.old_swapchain = a.template
				get_decayed_same_as<handle<vk::swapchain>>().underlying();
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