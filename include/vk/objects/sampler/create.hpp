#pragma once

#include "handle.hpp"
#include "create_info.hpp"
#include "../device/handle.hpp"
#include "../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../elements/possibly_guarded_handle_of.hpp"
#include "../../object/create_or_allocate.hpp"
#include "../../shared/result.hpp"

#include <core/meta/decayed_same_as.hpp>

namespace vk {

	template<>
	struct vk::create_t<vk::sampler> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_may_contain_one_decayed_same_as<vk::sampler_create_flags>,
			types::are_contain_one_decayed_same_as<vk::mag_filter>,
			types::are_contain_one_decayed_same_as<vk::min_filter>,
			types::are_contain_one_decayed_same_as<vk::mipmap_mode>,
			types::are_contain_one_decayed_same_as<vk::address_mode_u>,
			types::are_contain_one_decayed_same_as<vk::address_mode_v>,
			types::are_contain_one_decayed_same_as<vk::address_mode_w>,
			types::are_may_contain_one_decayed_same_as<vk::mip_lod_bias>,
			types::are_may_contain_one_decayed_same_as<vk::anisotropy_enable>,
			types::are_may_contain_one_decayed_same_as<vk::max_anisotropy>,
			types::are_may_contain_one_decayed_same_as<vk::compare_enable>,
			types::are_may_contain_one_decayed_same_as<vk::compare_op>,
			types::are_may_contain_one_decayed_same_as<vk::min_lod>,
			types::are_may_contain_one_decayed_same_as<vk::max_lod>,
			types::are_may_contain_one_decayed_same_as<vk::border_color>,
			types::are_may_contain_one_decayed_same_as<vk::unnormalized_coordinates>
		>::for_types<Args...>
		vk::expected<vk::handle<vk::sampler>>
		operator () (Args&&... args) const {
			vk::sampler_create_info ci {
				.mag_filter = elements::decayed_same_as<vk::mag_filter>(args...),
				.min_filter = elements::decayed_same_as<vk::min_filter>(args...),
				.mipmap_mode = elements::decayed_same_as<vk::mipmap_mode>(args...),
				.address_mode_u = elements::decayed_same_as<vk::address_mode_u>(args...),
				.address_mode_v = elements::decayed_same_as<vk::address_mode_v>(args...),
				.address_mode_w = elements::decayed_same_as<vk::address_mode_w>(args...)
			};

			if constexpr (types::are_contain_one_decayed_same_as<vk::sampler_create_flags>::for_types<Args...>) {
				ci.flags = elements::decayed_same_as<vk::sampler_create_flags>(args...);
			}
			if constexpr (types::are_contain_one_decayed_same_as<vk::mip_lod_bias>::for_types<Args...>) {
				ci.mip_lod_bias = elements::decayed_same_as<vk::mip_lod_bias>(args...);
			}
			if constexpr (types::are_contain_one_decayed_same_as<vk::anisotropy_enable>::for_types<Args...>) {
				ci.anisotropy_enable = elements::decayed_same_as<vk::anisotropy_enable>(args...);
			}
			if constexpr (types::are_contain_one_decayed_same_as<vk::max_anisotropy>::for_types<Args...>) {
				ci.max_anisotropy = elements::decayed_same_as<vk::max_anisotropy>(args...);
			}
			if constexpr (types::are_contain_one_decayed_same_as<vk::compare_enable>::for_types<Args...>) {
				ci.compare_enable = elements::decayed_same_as<vk::compare_enable>(args...);
			}
			if constexpr (types::are_contain_one_decayed_same_as<vk::compare_op>::for_types<Args...>) {
				ci.compare_op = elements::decayed_same_as<vk::compare_op>(args...);
			}
			if constexpr (types::are_contain_one_decayed_same_as<vk::min_lod>::for_types<Args...>) {
				ci.min_lod = elements::decayed_same_as<vk::min_lod>(args...);
			}
			if constexpr (types::are_contain_one_decayed_same_as<vk::max_lod>::for_types<Args...>) {
				ci.max_lod = elements::decayed_same_as<vk::max_lod>(args...);
			}
			if constexpr (types::are_contain_one_decayed_same_as<vk::border_color>::for_types<Args...>) {
				ci.border_color = elements::decayed_same_as<vk::border_color>(args...);
			}
			if constexpr (types::are_contain_one_decayed_same_as<vk::unnormalized_coordinates>::for_types<Args...>) {
				ci.unnormalized_coordinates = elements::decayed_same_as<vk::unnormalized_coordinates>(args...);
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