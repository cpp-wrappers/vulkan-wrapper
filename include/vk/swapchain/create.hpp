#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/for_each_of_type.hpp>

#include "core/elements/of_type.hpp"
#include "create_info.hpp"
#include "../result.hpp"

namespace vk {

	struct device;
	struct swapchain;

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::device&>::equals<1u>,
			types::count_of_type<vk::swapchain_create_flag>::remove_reference::greater_or_equals<0u>,
			types::count_of_type<vk::surface&>::equals<1u>,
			types::count_of_type<vk::min_image_count>::remove_reference::equals<1u>,
			types::count_of_type<vk::format>::remove_reference::equals<1u>,
			types::count_of_type<vk::color_space>::remove_reference::equals<1u>,
			types::count_of_type<vk::extent<2u>>::remove_reference::equals<1u>,
			types::count_of_type<vk::image_usage>::remove_reference::equals<1u>,
			types::count_of_type<vk::sharing_mode>::remove_reference::equals<1u>,
			types::count_of_type<vk::queue_family_index_count>::remove_reference::equals<1u>,
			types::count_of_type<vk::queue_family_indices>::remove_reference::equals<1u>,
			types::count_of_type<vk::surface_transform>::remove_reference::greater_or_equals<0u>,
			types::count_of_type<vk::composite_alpha>::remove_reference::greater_or_equals<0u>,
			types::count_of_type<vk::present_mode>::remove_reference::equals<1u>,
			types::count_of_type<vk::clipped>::remove_reference::equals<1u>
		>::for_types_of<Args...>
	)
	vk::swapchain& create_swapchain(Args&&... args) {
		vk::swapchain_create_info ci {
			.surface = elements::of_type<vk::surface&>::for_elements_of(args...),
			.min_image_count = elements::of_type<vk::min_image_count&>::for_elements_of(args...),
			.format = elements::of_type<vk::format&>::for_elements_of(args...),
			.color_space = elements::of_type<vk::color_space&>::for_elements_of(args...),
			.extent = elements::of_type<vk::extent<2u>&>::for_elements_of(args...),
			.usage = elements::of_type<vk::image_usage&>::for_elements_of(args...),
			.sharing_mode = elements::of_type<vk::sharing_mode&>::for_elements_of(args...),
			.queue_family_index_count = elements::of_type<vk::queue_family_index_count&>::for_elements_of(args...),
			.queue_family_indices = elements::of_type<vk::queue_family_indices&>::for_elements_of(args...),
			.present_mode = elements::of_type<vk::present_mode&>::for_elements_of(args...),
			.clipped = elements::of_type<vk::clipped&>::for_elements_of(args...)
		};

		elements::for_each_of_type_remove_reference<vk::swapchain_create_flag>(
			[&](auto f) { ci.flags.set(f); },
			args...
		);
		elements::for_each_of_type_remove_reference<vk::surface_transform>(
			[&](auto f) { ci.pre_transform.set(f); },
			args...
		);
		elements::for_each_of_type_remove_reference<vk::composite_alpha>(
			[&](auto f) { ci.composite_alpha.set(f); },
			args...
		);

		vk::swapchain* swapchain;

		vk::throw_if_error(
			vkCreateSwapchainKHR(
				(VkDevice) & elements::of_type<vk::device&>::for_elements_of(args...),
				(VkSwapchainCreateInfoKHR*) &ci,
				nullptr,
				(VkSwapchainKHR*) &swapchain
			)
		);

		return *swapchain;
	}

}