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
			types::are_may_contain_one_type<vk::sampler_create_flags>,
			types::are_contain_one_type<vk::mag_filter>,
			types::are_contain_one_type<vk::min_filter>,
			types::are_contain_one_type<vk::mipmap_mode>,
			types::are_contain_one_type<vk::address_mode_u>,
			types::are_contain_one_type<vk::address_mode_v>,
			types::are_contain_one_type<vk::address_mode_w>,
			types::are_contain_one_type<vk::mip_lod_bias>,
			types::are_contain_one_type<vk::anisotropy_enable>,
			types::are_may_contain_one_type<vk::max_anisotropy>,
			types::are_contain_one_type<vk::compare_enable>,
			types::are_contain_one_type<vk::compare_op>,
			types::are_contain_one_type<vk::min_lod>,
			types::are_contain_one_type<vk::max_lod>,
			types::are_contain_one_type<vk::border_color>,
			types::are_contain_one_type<vk::unnormalized_coordinates>
		>::for_types_of<decay<Args>...>
		vk::expected<vk::handle<vk::sampler>>
		operator () (Args&&... args) const {
			vk::sampler_create_info ci {
				.mag_filter = elements::of_type<vk::mag_filter>(args...),
				.min_filter = elements::of_type<vk::min_filter>(args...),
				.mipmap_mode = elements::of_type<vk::mipmap_mode>(args...),
				.address_mode_u = elements::of_type<vk::address_mode_u>(args...),
				.address_mode_v = elements::of_type<vk::address_mode_v>(args...),
				.address_mode_w = elements::of_type<vk::address_mode_w>(args...),
				.mip_lod_bias = elements::of_type<vk::mip_lod_bias>(args...),
				.anisotropy_enable = elements::of_type<vk::anisotropy_enable>(args...),
				.compare_enable = elements::of_type<vk::compare_enable>(args...),
				.compare_op = elements::of_type<vk::compare_op>(args...),
				.min_lod = elements::of_type<vk::min_lod>(args...),
				.max_lod = elements::of_type<vk::max_lod>(args...),
				.border_color = elements::of_type<vk::border_color>(args...),
				.unnormalized_coordinates = elements::of_type<vk::unnormalized_coordinates>(args...),
			};

			if constexpr (types::are_contain_one_type<vk::sampler_create_flags>::for_types_of<decay<Args>...>) {
				ci.flags = elements::of_type<vk::sampler_create_flags>(args...);
			}

			if constexpr (types::are_contain_one_type<vk::max_anisotropy>::for_types_of<decay<Args>...>) {
				ci.max_anisotropy = elements::of_type<vk::max_anisotropy>(args...);
			}

			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);

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