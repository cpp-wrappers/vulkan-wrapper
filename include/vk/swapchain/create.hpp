#pragma once

#include "handle.hpp"
#include "create_info.hpp"
#include "../surface/handle.hpp"

namespace vk {
	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::device>::equals<1>,
			types::count_of_type<vk::swapchain_create_flag>::greater_or_equals<0>,
			types::count_of_type<vk::surface>::equals<1>,
			types::count_of_type<vk::min_image_count>::equals<1>,
			types::count_of_type<vk::format>::equals<1>,
			types::count_of_type<vk::color_space>::equals<1>,
			types::count_of_type<vk::extent<2>>::equals<1>,
			types::count_of_type<vk::image_usage>::equals<1>,
			types::count_of_type<vk::sharing_mode>::equals<1>,
			types::count_of_type<vk::queue_family_index_count>::equals<1>,
			types::count_of_type<vk::queue_family_indices>::equals<1>,
			types::count_of_type<vk::surface_transform>::greater_or_equals<0>,
			types::count_of_type<vk::composite_alpha>::greater_or_equals<0>,
			types::count_of_type<vk::present_mode>::equals<1>,
			types::count_of_type<vk::clipped>::equals<1>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::swapchain>
	try_create_swapchain(const Args&... args) {
		const vk::surface& surface = elements::of_type<const vk::surface&>::for_elements_of(args...);

		vk::swapchain_create_info ci {
			.surface = surface.handle,
			.min_image_count = elements::of_type<const vk::min_image_count&>::for_elements_of(args...),
			.format = elements::of_type<const vk::format&>::for_elements_of(args...),
			.color_space = elements::of_type<const vk::color_space&>::for_elements_of(args...),
			.extent = elements::of_type<const vk::extent<2u>&>::for_elements_of(args...),
			.usage = elements::of_type<const vk::image_usage&>::for_elements_of(args...),
			.sharing_mode = elements::of_type<const vk::sharing_mode&>::for_elements_of(args...),
			.queue_family_index_count = elements::of_type<const vk::queue_family_index_count&>::for_elements_of(args...),
			.queue_family_indices = elements::of_type<const vk::queue_family_indices&>::for_elements_of(args...),
			.present_mode = elements::of_type<const vk::present_mode&>::for_elements_of(args...),
			.clipped = elements::of_type<const vk::clipped&>::for_elements_of(args...)
		};

		elements::for_each_of_type<const vk::swapchain_create_flag&>(
			[&](auto f) { ci.flags.set(f); },
			args...
		);
		elements::for_each_of_type<const vk::surface_transform&>(
			[&](auto f) { ci.pre_transform.set(f); },
			args...
		);
		elements::for_each_of_type<const vk::composite_alpha&>(
			[&](auto f) { ci.composite_alpha.set(f); },
			args...
		);

		const vk::device& device = elements::of_type<const vk::device&>::for_elements_of(args...);
		VkSwapchainKHR swapchain;

		vk::result result {
			(uint32) vkCreateSwapchainKHR(
				(VkDevice) device.handle,
				(VkSwapchainCreateInfoKHR*) &ci,
				nullptr,
				(VkSwapchainKHR*) &swapchain
			)
		};

		if(result.success()) return (uint64) swapchain;

		return result;
	}

	template<typename... Args>
	vk::swapchain create_swapchain(const Args&... args) {
		return try_create_swapchain(args...).template get<vk::swapchain>();
	}
}