#pragma once

#include "../shared/create_or_allocate.hpp"
#include "../surface/handle.hpp"
#include "../surface/format.hpp"
#include "../shared/guarded_handle.hpp"
#include "handle.hpp"
#include "create_info.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::swapchain> {

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::vk::contain_one<vk::device>,
				types::vk::contain_one<vk::surface>,
				types::vk::may_contain_one<vk::swapchain>,
				types::count_of_type<vk::swapchain_create_flag>::greater_or_equals<0>::ignore_reference,
				types::count_of_type<vk::min_image_count>::equals<1>::ignore_reference,
				types::count_of_type<vk::format>::equals<1>::ignore_reference,
				types::count_of_type<vk::color_space>::equals<1>::ignore_reference,
				types::count_of_type<vk::extent<2>>::equals<1>::ignore_reference,
				types::count_of_type<vk::image_usages>::equals<1>::ignore_reference,
				types::count_of_type<vk::sharing_mode>::equals<1>::ignore_reference,
				types::count_of_ranges_of_value_type<vk::queue_family_index>::less_or_equals<1>,
				types::count_of_type<vk::surface_transform>::greater_or_equals<0>::ignore_reference,
				types::count_of_type<vk::composite_alpha>::greater_or_equals<0>::ignore_reference,
				types::count_of_type<vk::present_mode>::equals<1>::ignore_reference,
				types::count_of_type<vk::clipped>::equals<1>::ignore_reference
			>::for_types_of<Args...>
		)
		vk::expected<vk::handle<vk::swapchain>>
		operator () (Args&&... args) const {
			auto& surface = elements::vk::of_type<vk::surface>::for_elements_of(args...);

			vk::swapchain_create_info ci {
				.surface = vk::get_handle(surface),
				.min_image_count = elements::of_type<vk::min_image_count&>::for_elements_of(args...),
				.format = elements::of_type<vk::format&>::for_elements_of(args...),
				.color_space = elements::of_type<vk::color_space&>::for_elements_of(args...),
				.extent = elements::of_type<vk::extent<2>&>::for_elements_of(args...),
				.usage = elements::of_type<vk::image_usages&>::for_elements_of(args...),
				.sharing_mode = elements::of_type<vk::sharing_mode&>::for_elements_of(args...),
				.present_mode = elements::of_type<vk::present_mode&>::for_elements_of(args...),
				.clipped = elements::of_type<vk::clipped&>::for_elements_of(args...)
			};

			elements::for_each_of_type<vk::swapchain_create_flag>::ignore_const::ignore_reference::function {
				[&](auto f) { ci.flags.set(f); }
			}.for_elements_of(args...);

			elements::for_each_of_type<vk::surface_transform>::ignore_const::ignore_reference::function {
				[&](auto f) { ci.pre_transform.set(f); }
			}.for_elements_of(args...);

			elements::for_each_of_type<vk::composite_alpha>::ignore_const::ignore_reference::function {
				[&](auto f) { ci.composite_alpha.set(f); }
			}.for_elements_of(args...);

			if constexpr(types::are_contain_range_of_value_type<vk::queue_family_index>::for_types_of<Args...>) {
				auto& family_indices = elements::range_of_value_type<vk::queue_family_index>::for_elements_of(args...);
				ci.queue_family_index_count = vk::queue_family_index_count{ (uint32) family_indices.size() };
				ci.queue_family_indices = vk::queue_family_indices{ family_indices.data() };
			}

			if constexpr(types::vk::contain_one<vk::swapchain>::for_types_of<Args...>) {
				ci.old_swapchain = vk::get_handle(elements::vk::of_type<vk::swapchain>::for_elements_of(args...));
			}

			auto& device = elements::vk::of_type<vk::device>::for_elements_of(args...);
			VkSwapchainKHR swapchain;

			vk::result result {
				(int32) vkCreateSwapchainKHR(
					(VkDevice) vk::get_handle_value(device),
					(VkSwapchainCreateInfoKHR*) &ci,
					nullptr,
					(VkSwapchainKHR*) &swapchain
				)
			};

			if(result.success()) return vk::handle<vk::swapchain>{ swapchain };

			return result;
		}

		template<typename... Args>
		requires(types::count_of_type<vk::surface_format>::equals<1>::ignore_reference::for_types_of<Args...>)
		vk::expected<vk::handle<vk::swapchain>>
		operator () (Args&&... args) const {
			vk::surface_format surface_format = elements::of_type<vk::surface_format&>::for_elements_of(args...);

			return elements::pass_satisfying_type_predicate<
				type::negated_predicate<type::is_same_as<vk::surface_format>::ignore_reference>
			>::to_function {
				[this]<typename... Others>(Others&&... others) {
					return this->operator ()(forward<Others>(others)...);
				}
			}.for_elements_of(
				surface_format.format,
				surface_format.color_space,
				forward<Args>(args)...
			);
		}

	};
}