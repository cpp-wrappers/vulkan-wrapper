#pragma once

#include <core/forward.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/for_each_of_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/one_of.hpp>

#include "swapchain/create_info.hpp"
#include "shared/headers.hpp"
#include "shared/result.hpp"
//#include "image/view.hpp"

namespace vk {

	class device;

	class swapchain {
		void* m_swapchain;
		const device& m_device;
	public:
		swapchain() = delete;
		swapchain(const swapchain&) = delete;
		swapchain(swapchain&& other) : m_swapchain{ other.m_swapchain }, m_device{ other.m_device } { m_swapchain = nullptr; }

		swapchain(VkSwapchainKHR swapchain, const vk::device& device) : m_swapchain{ swapchain }, m_device{ device } {}

		~swapchain() {
			if(m_swapchain) {
				vkDestroySwapchainKHR(
					* (VkDevice*) & m_device,
					(VkSwapchainKHR) m_swapchain,
					nullptr
				);
				m_swapchain = nullptr;
			}
		}
	}; // swapchain

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
			.surface = *(void**) &surface, // TODO
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
				* (VkDevice*) & device,
				(VkSwapchainCreateInfoKHR*) &ci,
				nullptr,
				&swapchain
			)
		};
		if(!result.success()) return result;

		return vk::swapchain{ swapchain, device };
	}

	template<typename... Args>
	vk::swapchain create_swapchain(const Args&... args) {
		return try_create_swapchain(args...).template move<vk::swapchain>();
	}

} // vk

