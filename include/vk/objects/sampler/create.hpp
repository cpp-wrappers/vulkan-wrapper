#pragma once

#include "../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../elements/possibly_guarded_handle_of.hpp"
#include "../../object/create_or_allocate.hpp"
#include "../../shared/result.hpp"
#include "../device/handle.hpp"
#include "handle.hpp"
#include "create_info.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::sampler> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::count_of_type<vk::sampler_create_flags>::less_or_equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::mag_filter>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::min_filter>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::mipmap_mode>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::address_mode_u>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::address_mode_v>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::address_mode_w>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::mip_lod_bias>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::anisotropy_enable>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::max_anisotropy>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::compare_enable>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::compare_op>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::min_lod>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::max_lod>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::border_color>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::unnormalized_coordinates>::equals<1>::ignore_const::ignore_reference
		>::for_types_of<Args...>
		vk::expected<vk::handle<vk::sampler>>
		operator () (Args&&... args) const {
			vk::sampler_create_info ci {
				.flags = elements::of_type<vk::sampler_create_flags>::ignore_const::ignore_reference::for_elements_of(args...),
				.mag_filter = elements::of_type<vk::mag_filter>::ignore_const::ignore_reference::for_elements_of(args...),
				.min_filter = elements::of_type<vk::min_filter>::ignore_const::ignore_reference::for_elements_of(args...),
				.mipmap_mode = elements::of_type<vk::mipmap_mode>::ignore_const::ignore_reference::for_elements_of(args...),
				.address_mode_u = elements::of_type<vk::address_mode_u>::ignore_const::ignore_reference::for_elements_of(args...),
				.address_mode_v = elements::of_type<vk::address_mode_v>::ignore_const::ignore_reference::for_elements_of(args...),
				.address_mode_w = elements::of_type<vk::address_mode_w>::ignore_const::ignore_reference::for_elements_of(args...),
				.mip_lod_bias = elements::of_type<vk::mip_lod_bias>::ignore_const::ignore_reference::for_elements_of(args...),
				.anisotropy_enable = elements::of_type<vk::anisotropy_enable>::ignore_const::ignore_reference::for_elements_of(args...),
				.max_anisotropy = elements::of_type<vk::max_anisotropy>::ignore_const::ignore_reference::for_elements_of(args...),
				.compare_enable = elements::of_type<vk::compare_enable>::ignore_const::ignore_reference::for_elements_of(args...),
				.compare_op = elements::of_type<vk::compare_op>::ignore_const::ignore_reference::for_elements_of(args...),
				.min_lod = elements::of_type<vk::min_lod>::ignore_const::ignore_reference::for_elements_of(args...),
				.max_lod = elements::of_type<vk::max_lod>::ignore_const::ignore_reference::for_elements_of(args...),
				.border_color = elements::of_type<vk::border_color>::ignore_const::ignore_reference::for_elements_of(args...),
				.unnormalized_coordinates = elements::of_type<vk::unnormalized_coordinates>::ignore_const::ignore_reference::for_elements_of(args...),
			};

			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);

			vk::handle<vk::sampler> sampler;

			vk::result result {
				(int32) vkCreateSampler(
					(VkDevice) vk::get_handle_value(device),
					(VkSamplerCreateInfo*) &ci,
					(VkAllocationCallbacks*) nullptr,
					(VkSampler*) &sampler
				)
			};

			if(result.error()) return result;

			return sampler;
		}

	};

} // vk