#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include "../result.hpp"
#include "../device/handle.hpp"

#include <core/meta/decayed_same_as.hpp>

extern "C" VK_ATTR int32 VK_CALL vkCreateSampler(
	handle<vk::device>             device,
	const vk::sampler_create_info* create_info,
	const void*                    allocator,
	handle<vk::sampler>*           sampler
);

namespace vk {

	template<>
	struct vk::create_t<vk::sampler> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<handle<vk::device>>,
			types::are_may_contain_one_decayed<vk::sampler_create_flags>,
			types::are_contain_one_decayed<vk::mag_filter>,
			types::are_contain_one_decayed<vk::min_filter>,
			types::are_contain_one_decayed<vk::mipmap_mode>,
			types::are_contain_one_decayed<vk::address_mode_u>,
			types::are_contain_one_decayed<vk::address_mode_v>,
			types::are_contain_one_decayed<vk::address_mode_w>,
			types::are_may_contain_one_decayed<vk::mip_lod_bias>,
			types::are_may_contain_one_decayed<vk::anisotropy_enable>,
			types::are_may_contain_one_decayed<vk::max_anisotropy>,
			types::are_may_contain_one_decayed<vk::compare_enable>,
			types::are_may_contain_one_decayed<vk::compare_op>,
			types::are_may_contain_one_decayed<vk::min_lod>,
			types::are_may_contain_one_decayed<vk::max_lod>,
			types::are_may_contain_one_decayed<vk::border_color>,
			types::are_may_contain_one_decayed<vk::unnormalized_coordinates>
		>::for_types<Args...>
		vk::expected<handle<vk::sampler>>
		operator () (Args&&... args) const {
			vk::sampler_create_info ci {
				.mag_filter = elements::decayed<vk::mag_filter>(args...),
				.min_filter = elements::decayed<vk::min_filter>(args...),
				.mipmap_mode = elements::decayed<vk::mipmap_mode>(args...),
				.address_mode_u = elements::decayed<
					vk::address_mode_u
				>(args...),
				.address_mode_v = elements::decayed<
					vk::address_mode_v
				>(args...),
				.address_mode_w = elements::decayed<
					vk::address_mode_w
				>(args...)
			};

			if constexpr (
				types::are_contain_one_decayed<
					vk::sampler_create_flags
				>::for_types<Args...>
			) {
				ci.flags = elements::decayed<vk::sampler_create_flags>(args...);
			}

			if constexpr (
				types::are_contain_one_decayed<
					vk::mip_lod_bias
				>::for_types<Args...>
			) {
				ci.mip_lod_bias = elements::decayed<vk::mip_lod_bias>(args...);
			}

			if constexpr (
				types::are_contain_one_decayed<
					vk::anisotropy_enable
				>::for_types<Args...>
			) {
				ci.anisotropy_enable = elements::decayed<
					vk::anisotropy_enable
				>(args...);
			}

			if constexpr (
				types::are_contain_one_decayed<
					vk::max_anisotropy
				>::for_types<Args...>
			) {
				ci.max_anisotropy = elements::decayed<
					vk::max_anisotropy
				>(args...);
			}

			if constexpr (
				types::are_contain_one_decayed<
					vk::compare_enable
				>::for_types<Args...>
			) {
				ci.compare_enable = elements::decayed<
					vk::compare_enable
				>(args...);
			}

			if constexpr (
				types::are_contain_one_decayed<
					vk::compare_op
				>::for_types<Args...>
			) {
				ci.compare_op = elements::decayed<vk::compare_op>(args...);
			}

			if constexpr (
				types::are_contain_one_decayed<
					vk::min_lod
				>::for_types<Args...>
			) {
				ci.min_lod = elements::decayed<vk::min_lod>(args...);
			}

			if constexpr (
				types::are_contain_one_decayed<
					vk::max_lod
				>::for_types<Args...>
			) {
				ci.max_lod = elements::decayed<vk::max_lod>(args...);
			}

			if constexpr (
				types::are_contain_one_decayed<
					vk::border_color
				>::for_types<Args...>
			) {
				ci.border_color = elements::decayed<vk::border_color>(args...);
			}

			if constexpr (
				types::are_contain_one_decayed<
					vk::unnormalized_coordinates
				>::for_types<Args...>
			) {
				ci.unnormalized_coordinates = elements::decayed<
					vk::unnormalized_coordinates
				>(args...);
			}

			auto device = elements::decayed<handle<vk::device>>(args...);

			handle<vk::sampler> sampler;

			vk::result result {
				vkCreateSampler(
					device,
					&ci,
					nullptr,
					&sampler
				)
			};

			if(result.error()) return result;

			return sampler;
		}

	}; // create_t<sampler>

} // vk