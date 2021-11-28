#pragma once

#include <core/elements/of.hpp>
#include <core/values/erase_at_index.hpp>
#include <core/elements/pass_satisfying_type_predicate.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/type/negated_predicate.hpp>

#include "handle.hpp"
#include "create_info.hpp"
#include "../surface/handle.hpp"
#include "../surface/format.hpp"

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
			types::count_of_type<vk::image_usage>::greater_or_equals<1>,
			types::count_of_type<vk::sharing_mode>::equals<1>,
			types::count_of_ranges_of_value_type<vk::queue_family_index>::less_or_equals<1>,
			types::count_of_type<vk::surface_transform>::greater_or_equals<0>,
			types::count_of_type<vk::composite_alpha>::greater_or_equals<0>,
			types::count_of_type<vk::present_mode>::equals<1>,
			types::count_of_type<vk::clipped>::equals<1>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::swapchain>
	try_create_swapchain(Args... args) {
		vk::surface surface = elements::of_type<vk::surface&>::for_elements_of(args...);

		vk::swapchain_create_info ci {
			.surface = surface.handle,
			.min_image_count = elements::of_type<vk::min_image_count&>::for_elements_of(args...),
			.format = elements::of_type<vk::format&>::for_elements_of(args...),
			.color_space = elements::of_type<vk::color_space&>::for_elements_of(args...),
			.extent = elements::of_type<vk::extent<2u>&>::for_elements_of(args...),
			.sharing_mode = elements::of_type<vk::sharing_mode&>::for_elements_of(args...),
			.present_mode = elements::of_type<vk::present_mode&>::for_elements_of(args...),
			.clipped = elements::of_type<vk::clipped&>::for_elements_of(args...)
		};

		elements::for_each_of_type<vk::swapchain_create_flag&>(
			[&](auto f) { ci.flags.set(f); },
			args...
		);
		elements::for_each_of_type<vk::image_usage&>(
			[&](auto f) { ci.usage.set(f); },
			args...
		);
		elements::for_each_of_type<vk::surface_transform&>(
			[&](auto f) { ci.pre_transform.set(f); },
			args...
		);
		elements::for_each_of_type<vk::composite_alpha&>(
			[&](auto f) { ci.composite_alpha.set(f); },
			args...
		);
		if constexpr(types::count_of_ranges_of_value_type<vk::queue_family_index>::for_types_of<Args...> == 1) {
			auto& family_indices = elements::range_of_value_type<vk::queue_family_index>::for_elements_of(args...);
			ci.queue_family_index_count = vk::queue_family_index_count{ (uint32) family_indices.size() };
			ci.queue_family_indices = vk::queue_family_indices{ family_indices.data() };
		}
		else {
			ci.queue_family_index_count = vk::queue_family_index_count{ 0 };
			ci.queue_family_indices = vk::queue_family_indices{ nullptr };
		}

		vk::device device = elements::of_type<vk::device&>::for_elements_of(args...);
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
	requires(types::count_of_type<vk::surface_format>::equals<1>::for_types_of<Args...>)
	elements::one_of<vk::result, vk::swapchain>
	try_create_swapchain(Args... args) {
		vk::surface_format surface_format = elements::of_type<vk::surface_format&>::for_elements_of(args...);

		return elements::pass_satisfying_type_predicate<
			type::negated_predicate<type::is_same_as<vk::surface_format&>>
		>::for_function_and_elements_of([](auto... elements) {
			return try_create_swapchain(elements...);
		}, surface_format.format, surface_format.color_space, args...);
	}

	template<typename... Args>
	vk::swapchain create_swapchain(Args&&... args) {
		return try_create_swapchain(forward<Args>(args)...).template get<vk::swapchain>();
	}
}