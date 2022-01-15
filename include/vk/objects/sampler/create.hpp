#pragma once

#include <core/types/are_contain_one_type.hpp>
#include <core/types/are_may_contain_one_type.hpp>

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
			types::are_may_contain_one_type<vk::sampler_create_flags>::decay,
			types::are_contain_one_type<vk::mag_filter>::decay,
			types::are_contain_one_type<vk::min_filter>::decay,
			types::are_contain_one_type<vk::mipmap_mode>::decay,
			types::are_contain_one_type<vk::address_mode_u>::decay,
			types::are_contain_one_type<vk::address_mode_v>::decay,
			types::are_contain_one_type<vk::address_mode_w>::decay,
			types::are_contain_one_type<vk::mip_lod_bias>::decay,
			types::are_contain_one_type<vk::anisotropy_enable>::decay,
			types::are_may_contain_one_type<vk::max_anisotropy>::decay,
			types::are_contain_one_type<vk::compare_enable>::decay,
			types::are_contain_one_type<vk::compare_op>::decay,
			types::are_contain_one_type<vk::min_lod>::decay,
			types::are_contain_one_type<vk::max_lod>::decay,
			types::are_contain_one_type<vk::border_color>::decay,
			types::are_contain_one_type<vk::unnormalized_coordinates>::decay
		>::for_types_of<Args...>
		vk::expected<vk::handle<vk::sampler>>
		operator () (Args&&... args) const {
			vk::sampler_create_info ci {
				.mag_filter = elements::of_type<vk::mag_filter>::decay::for_elements_of(args...),
				.min_filter = elements::of_type<vk::min_filter>::decay::for_elements_of(args...),
				.mipmap_mode = elements::of_type<vk::mipmap_mode>::decay::for_elements_of(args...),
				.address_mode_u = elements::of_type<vk::address_mode_u>::decay::for_elements_of(args...),
				.address_mode_v = elements::of_type<vk::address_mode_v>::decay::for_elements_of(args...),
				.address_mode_w = elements::of_type<vk::address_mode_w>::decay::for_elements_of(args...),
				.mip_lod_bias = elements::of_type<vk::mip_lod_bias>::decay::for_elements_of(args...),
				.anisotropy_enable = elements::of_type<vk::anisotropy_enable>::decay::for_elements_of(args...),
				.compare_enable = elements::of_type<vk::compare_enable>::decay::for_elements_of(args...),
				.compare_op = elements::of_type<vk::compare_op>::decay::for_elements_of(args...),
				.min_lod = elements::of_type<vk::min_lod>::decay::for_elements_of(args...),
				.max_lod = elements::of_type<vk::max_lod>::decay::for_elements_of(args...),
				.border_color = elements::of_type<vk::border_color>::decay::for_elements_of(args...),
				.unnormalized_coordinates = elements::of_type<vk::unnormalized_coordinates>::decay::for_elements_of(args...),
			};

			if constexpr (types::are_contain_one_type<vk::sampler_create_flags>::decay::for_types_of<Args...>) {
				ci.flags = elements::of_type<vk::sampler_create_flags>::decay::for_elements_of(args...);
			}

			if constexpr (types::are_contain_one_type<vk::max_anisotropy>::decay::for_types_of<Args...>) {
				ci.max_anisotropy = elements::of_type<vk::max_anisotropy>::decay::for_elements_of(args...);
			}

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