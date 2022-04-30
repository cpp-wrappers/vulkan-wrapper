#pragma once

#include "create_info.hpp"

#include "../surface/handle.hpp"
#include "../surface/format.hpp"
#include "../create_or_allocate.hpp"
#include "../function.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/elements/pass_not_satisfying_type_predicate.hpp>

extern "C" VK_ATTR int32 VK_CALL vkCreateSwapchainKHR(
	handle<vk::device>               device,
	const vk::swapchain_create_info* create_info,
	const void*                      allocator,
	handle<vk::swapchain>*           swapchain
);

namespace vk {

	template<>
	struct vk::create_t<vk::swapchain> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<handle<vk::device>>,
			types::are_contain_one_decayed<handle<vk::surface>>,
			types::are_may_contain_one_decayed<handle<vk::swapchain>>,
			types::are_may_contain_decayed<vk::swapchain_create_flag>,
			types::are_contain_one_decayed<vk::min_image_count>,
			types::are_contain_one_decayed<vk::format>,
			types::are_contain_one_decayed<vk::color_space>,
			types::are_contain_one_decayed<vk::extent<2>>,
			types::are_contain_one_decayed<vk::image_usages>,
			types::are_contain_one_decayed<vk::sharing_mode>,
			types::are_may_contain_range_of<vk::queue_family_index>,
			types::are_may_contain_decayed<vk::surface_transform>,
			types::are_may_contain_decayed<vk::composite_alpha>,
			types::are_contain_one_decayed<vk::present_mode>,
			types::are_contain_one_decayed<vk::clipped>
		>::for_types<Args...>
		vk::expected<handle<vk::swapchain>>
		operator () (Args&&... args) const {
			auto surface {
				elements::decayed<handle<vk::surface>>(args...)
			};

			vk::swapchain_create_info ci {
				.surface = surface,
				.min_image_count = elements::decayed<
					vk::min_image_count
				>(args...),
				.format = elements::decayed<vk::format>(args...),
				.color_space = elements::decayed<vk::color_space>(args...),
				.extent = elements::decayed<vk::extent<2>>(args...),
				.usage = elements::decayed<vk::image_usages>(args...),
				.sharing_mode = elements::decayed<vk::sharing_mode>(args...),
				.present_mode = elements::decayed<vk::present_mode>(args...),
				.clipped = elements::decayed<vk::clipped>(args...)
			};

			elements::for_each_decayed<vk::swapchain_create_flag>(args...)(
				[&](auto f) { ci.flags.set(f); }
			);

			elements::for_each_decayed<vk::surface_transform>(args...)(
				[&](auto f) { ci.pre_transform.set(f); }
			);

			elements::for_each_decayed<vk::composite_alpha>(args...)(
				[&](auto f) { ci.composite_alpha.set(f); }
			);

			if constexpr (
				types::are_contain_range_of<
					vk::queue_family_index
				>::for_types<Args...>
			) {
				auto& family_indices =
					elements::range_of<vk::queue_family_index>(args...);

				ci.queue_family_index_count =
					vk::queue_family_index_count {
						(uint32) family_indices.size()
					};

				ci.queue_family_indices =
					vk::queue_family_indices{ family_indices.data() };
			}

			if constexpr (
				types::are_contain_one_decayed<
					handle<vk::swapchain>
				>::for_types<Args...>
			) {
				ci.old_swapchain = {
					elements::decayed<handle<vk::swapchain>>(args...)
				};
			}

			auto device {
				elements::decayed<handle<vk::device>>(args...)
			};

			handle<vk::swapchain> swapchain;

			vk::result result {
				vkCreateSwapchainKHR(
					device,
					&ci,
					nullptr,
					&swapchain
				)
			};

			if(result.error()) return result;

			return swapchain;

		} // operator ()

		template<typename... Args>
		requires types::are_contain_one_decayed<
			vk::surface_format
		>::for_types<Args...>
		vk::expected<handle<vk::swapchain>>
		operator () (Args&&... args) const {
			vk::surface_format surface_format =
				elements::decayed<vk::surface_format>(args...);

			return elements::pass_not_satisfying_type_predicate<
				type::is_decayed<vk::surface_format>
			>(
				surface_format.format,
				surface_format.color_space,
				forward<Args>(args)...
			)(vk::create_t<vk::swapchain>{});

		} // operator ()

	}; // create_t<swapchain>

} // vk