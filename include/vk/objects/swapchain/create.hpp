#pragma once

#include "../../object/create_or_allocate.hpp"
#include "../surface/handle.hpp"
#include "../surface/format.hpp"
#include "handle.hpp"
#include "create_info.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::swapchain> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::surface>,
			types::vk::are_may_contain_one_possibly_guarded_handle_of<vk::swapchain>,
			types::count_of_type<vk::swapchain_create_flag>::greater_or_equals<0>,
			types::count_of_type<vk::min_image_count>::equals<1>,
			types::count_of_type<vk::format>::equals<1>,
			types::count_of_type<vk::color_space>::equals<1>,
			types::count_of_type<vk::extent<2>>::equals<1>,
			types::count_of_type<vk::image_usages>::equals<1>,
			types::count_of_type<vk::sharing_mode>::equals<1>,
			types::count_of_ranges_of_value_type<vk::queue_family_index>::less_or_equals<1>,
			types::count_of_type<vk::surface_transform>::greater_or_equals<0>,
			types::count_of_type<vk::composite_alpha>::greater_or_equals<0>,
			types::count_of_type<vk::present_mode>::equals<1>,
			types::count_of_type<vk::clipped>::equals<1>
		>::for_types_of<decay<Args>...>
		vk::expected<vk::handle<vk::swapchain>>
		operator () (Args&&... args) const {
			auto& surface = elements::vk::possibly_guarded_handle_of<vk::surface>(args...);

			vk::swapchain_create_info ci {
				.surface = vk::get_handle(surface),
				.min_image_count = elements::of_type<vk::min_image_count>(args...),
				.format = elements::of_type<vk::format>(args...),
				.color_space = elements::of_type<vk::color_space>(args...),
				.extent = elements::of_type<vk::extent<2>>(args...),
				.usage = elements::of_type<vk::image_usages>(args...),
				.sharing_mode = elements::of_type<vk::sharing_mode>(args...),
				.present_mode = elements::of_type<vk::present_mode>(args...),
				.clipped = elements::of_type<vk::clipped>(args...)
			};

			elements::for_each_of_type<vk::swapchain_create_flag>::function {
				[&](auto f) { ci.flags.set(f); }
			}.for_elements_of(args...);

			elements::for_each_of_type<vk::surface_transform>::function {
				[&](auto f) { ci.pre_transform.set(f); }
			}.for_elements_of(args...);

			elements::for_each_of_type<vk::composite_alpha>::function {
				[&](auto f) { ci.composite_alpha.set(f); }
			}.for_elements_of(args...);

			if constexpr(types::are_contain_range_of_value_type<vk::queue_family_index>::for_types_of<Args...>) {
				auto& family_indices = elements::range_of_value_type<vk::queue_family_index>(args...);
				ci.queue_family_index_count = vk::queue_family_index_count{ (uint32) family_indices.size() };
				ci.queue_family_indices = vk::queue_family_indices{ family_indices.data() };
			}

			if constexpr(types::vk::are_contain_one_possibly_guarded_handle_of<vk::swapchain>::for_types_of<Args...>) {
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
		requires types::count_of_type<vk::surface_format>::equals<1>::for_types_of<decay<Args>...>
		vk::expected<vk::handle<vk::swapchain>>
		operator () (Args&&... args) const {
			vk::surface_format surface_format = elements::of_type<vk::surface_format>(args...);

			return elements::pass_satisfying_type_predicate<
				type::modified_predicate<type::negated_predicate<type::is_same_as<vk::surface_format>>, type::decay>
			>::function {
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

} // vk