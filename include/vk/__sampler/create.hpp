#pragma once

#include "./handle.hpp"
#include "./create_info.hpp"
#include "../__internal/function.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"

namespace vk {

	struct create_sampler_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		const vk::sampler_create_info* create_info,
		const void* allocator,
		handle<vk::sampler>::underlying_type* sampler
	)> {
		static constexpr auto name = "vkCreateSampler";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<vk::sampler_create_flags>.decayed <= 1,
		is_same_as<vk::mag_filter>.decayed == 1,
		is_same_as<vk::min_filter>.decayed == 1,
		is_same_as<vk::mipmap_mode>.decayed == 1,
		is_same_as<vk::address_mode_u>.decayed == 1,
		is_same_as<vk::address_mode_v>.decayed == 1,
		is_same_as<vk::address_mode_w>.decayed == 1,
		is_same_as<vk::mip_lod_bias>.decayed <= 1,
		is_same_as<vk::anisotropy_enable>.decayed <= 1,
		is_same_as<vk::max_anisotropy>.decayed <= 1,
		is_same_as<vk::compare_enable>.decayed <= 1,
		is_same_as<vk::compare_op>.decayed <= 1,
		is_same_as<vk::min_lod>.decayed <= 1,
		is_same_as<vk::max_lod>.decayed <= 1,
		is_same_as<vk::border_color>.decayed <= 1,
		is_same_as<vk::unnormalized_coordinates>.decayed <= 1
	>
	vk::expected<handle<vk::sampler>>
	try_create_sampler(Args&&... args) {
		tuple a { args... };

		vk::sampler_create_info ci {
			.mag_filter = a.template get<is_same_as<vk::mag_filter>.decayed>(),
			.min_filter = a.template get<is_same_as<vk::min_filter>.decayed>(),
			.mipmap_mode = a.template get<is_same_as<vk::mipmap_mode>.decayed>(),
			.address_mode_u = a.template
				get<is_same_as<vk::address_mode_u>.decayed>(),
			.address_mode_v = a.template
				get<is_same_as<vk::address_mode_v>.decayed>(),
			.address_mode_w = a.template
				get<is_same_as<vk::address_mode_w>.decayed>()
		};

		if constexpr (
			(is_same_as<vk::sampler_create_flags>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.flags = a.template
				get<is_same_as<vk::sampler_create_flags>.decayed>();
		}

		if constexpr (
			(is_same_as<vk::mip_lod_bias>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.mip_lod_bias = a.template
				get<is_same_as<vk::mip_lod_bias>.decayed>();
		}

		if constexpr (
			(is_same_as<vk::anisotropy_enable>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.anisotropy_enable = a.template
				get<is_same_as<vk::anisotropy_enable>.decayed>();
		}

		if constexpr (
			(is_same_as<vk::max_anisotropy>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.max_anisotropy = a.template
				get<is_same_as<vk::max_anisotropy>.decayed>();
		}

		if constexpr (
			(is_same_as<vk::compare_enable>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.compare_enable = a.template
				get<is_same_as<vk::compare_enable>.decayed>();
		}

		if constexpr (
			(is_same_as<vk::compare_op>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.compare_op = a.template
				get<is_same_as<vk::compare_op>.decayed>();
		}

		if constexpr (
			(is_same_as<vk::min_lod>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.min_lod = a.template
				get<is_same_as<vk::min_lod>.decayed>();
		}

		if constexpr (
			(is_same_as<vk::max_lod>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.max_lod = a.template
				get<is_same_as<vk::max_lod>.decayed>();
		}

		if constexpr (
			(is_same_as<vk::border_color>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.border_color = a.template
				get<is_same_as<vk::border_color>.decayed>();
		}

		if constexpr (
			(is_same_as<vk::unnormalized_coordinates>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.unnormalized_coordinates = a.template
				get<is_same_as<vk::unnormalized_coordinates>.decayed>();
		}

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::sampler> sampler;

		vk::result result {
			vk::get_device_function<vk::create_sampler_function>(
				instance, device
			)(
				device.underlying(),
				&ci,
				nullptr,
				&sampler.underlying()
			)
		};

		if(result.error()) return result;

		return sampler;
	}

	template<typename... Args>
	handle<vk::sampler> create_sampler(Args&&... args) {
		vk::expected<handle<vk::sampler>> result
			= vk::try_create_sampler(forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk