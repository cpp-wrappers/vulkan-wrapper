#pragma once

#include "handle.hpp"
#include "create_info.hpp"
#include "../surface/handle.hpp"
#include "../surface/format.hpp"
#include "../../object/create_or_allocate.hpp"

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/elements/pass_not_satisfying_type_predicate.hpp>

namespace vk {

	template<>
	struct vk::create_t<vk::swapchain> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::surface>,
			types::vk::are_may_contain_one_possibly_guarded_handle_of<vk::swapchain>,
			types::are_may_contain_decayed_same_as<vk::swapchain_create_flag>,
			types::are_contain_one_decayed_same_as<vk::min_image_count>,
			types::are_contain_one_decayed_same_as<vk::format>,
			types::are_contain_one_decayed_same_as<vk::color_space>,
			types::are_contain_one_decayed_same_as<vk::extent<2>>,
			types::are_contain_one_decayed_same_as<vk::image_usages>,
			types::are_contain_one_decayed_same_as<vk::sharing_mode>,
			types::are_may_contain_one_range_of_value_type<vk::queue_family_index>,
			types::are_may_contain_decayed_same_as<vk::surface_transform>,
			types::are_may_contain_decayed_same_as<vk::composite_alpha>,
			types::are_contain_one_decayed_same_as<vk::present_mode>,
			types::are_contain_one_decayed_same_as<vk::clipped>
		>::for_types<Args...>
		vk::expected<vk::handle<vk::swapchain>>
		operator () (Args&&... args) const {
			auto& surface = elements::vk::possibly_guarded_handle_of<vk::surface>(args...);

			vk::swapchain_create_info ci {
				.surface = vk::get_handle(surface),
				.min_image_count = elements::decayed_same_as<vk::min_image_count>(args...),
				.format = elements::decayed_same_as<vk::format>(args...),
				.color_space = elements::decayed_same_as<vk::color_space>(args...),
				.extent = elements::decayed_same_as<vk::extent<2>>(args...),
				.usage = elements::decayed_same_as<vk::image_usages>(args...),
				.sharing_mode = elements::decayed_same_as<vk::sharing_mode>(args...),
				.present_mode = elements::decayed_same_as<vk::present_mode>(args...),
				.clipped = elements::decayed_same_as<vk::clipped>(args...)
			};

			elements::for_each_decayed_same_as<vk::swapchain_create_flag>(args...)(
				[&](auto f) { ci.flags.set(f); }
			);

			elements::for_each_decayed_same_as<vk::surface_transform>(args...)(
				[&](auto f) { ci.pre_transform.set(f); }
			);

			elements::for_each_decayed_same_as<vk::composite_alpha>(args...)(
				[&](auto f) { ci.composite_alpha.set(f); }
			);

			if constexpr(types::are_contain_range_of_value_type<vk::queue_family_index>::for_types<Args...>) {
				auto& family_indices = elements::range_of_value_type<vk::queue_family_index>(args...);
				ci.queue_family_index_count = vk::queue_family_index_count{ (uint32) family_indices.size() };
				ci.queue_family_indices = vk::queue_family_indices{ family_indices.data() };
			}

			if constexpr(types::vk::are_contain_one_possibly_guarded_handle_of<vk::swapchain>::for_types<Args...>) {
				ci.old_swapchain = vk::get_handle(elements::vk::possibly_guarded_handle_of<vk::swapchain>(args...));
			}

			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);
			vk::handle<vk::swapchain> swapchain;

			vk::result result {
				(int32) vkCreateSwapchainKHR(
					(VkDevice) vk::get_handle_value(device),
					(VkSwapchainCreateInfoKHR*) &ci,
					(VkAllocationCallbacks*) nullptr,
					(VkSwapchainKHR*) &swapchain
				)
			};

			if(result.error()) return result;

			return swapchain;
		}

		template<typename... Args>
		requires types::are_contain_one_decayed_same_as<vk::surface_format>::for_types<Args...>
		vk::expected<vk::handle<vk::swapchain>>
		operator () (Args&&... args) const {
			vk::surface_format surface_format = elements::decayed_same_as<vk::surface_format>(args...);

			return elements::pass_not_satisfying_type_predicate<type::is_decayed_same_as<vk::surface_format>>(
				surface_format.format,
				surface_format.color_space,
				forward<Args>(args)...
			)(
				[]<typename... Others>(Others&&... others) {
					return vk::create_t<vk::swapchain>{}(forward<Others>(others)...);
				}
			);
		}

	};

} // vk