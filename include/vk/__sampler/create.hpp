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
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<vk::sampler_create_flags> <= 1,
		count_of_decayed_same_as<vk::mag_filter> == 1,
		count_of_decayed_same_as<vk::min_filter> == 1,
		count_of_decayed_same_as<vk::mipmap_mode> == 1,
		count_of_decayed_same_as<vk::address_mode_u> == 1,
		count_of_decayed_same_as<vk::address_mode_v> == 1,
		count_of_decayed_same_as<vk::address_mode_w> == 1,
		count_of_decayed_same_as<vk::mip_lod_bias> <= 1,
		count_of_decayed_same_as<vk::anisotropy_enable> <= 1,
		count_of_decayed_same_as<vk::max_anisotropy> <= 1,
		count_of_decayed_same_as<vk::compare_enable> <= 1,
		count_of_decayed_same_as<vk::compare_op> <= 1,
		count_of_decayed_same_as<vk::min_lod> <= 1,
		count_of_decayed_same_as<vk::max_lod> <= 1,
		count_of_decayed_same_as<vk::border_color> <= 1,
		count_of_decayed_same_as<vk::unnormalized_coordinates> <= 1
	>
	vk::expected<handle<vk::sampler>>
	try_create_sampler(Args&&... args) {
		tuple a { args... };

		vk::sampler_create_info ci {
			.mag_filter = a.template get_decayed_same_as<vk::mag_filter>(),
			.min_filter = a.template get_decayed_same_as<vk::min_filter>(),
			.mipmap_mode = a.template get_decayed_same_as<vk::mipmap_mode>(),
			.address_mode_u = a.template
				get_decayed_same_as<vk::address_mode_u>(),
			.address_mode_v = a.template
				get_decayed_same_as<vk::address_mode_v>(),
			.address_mode_w = a.template
				get_decayed_same_as<vk::address_mode_w>()
		};

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::sampler_create_flags> > 0
		) {
			ci.flags = a.template
				get_decayed_same_as<vk::sampler_create_flags>();
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::mip_lod_bias> > 0
		) {
			ci.mip_lod_bias = a.template
				get_decayed_same_as<vk::mip_lod_bias>();
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::anisotropy_enable> > 0
		) {
			ci.anisotropy_enable = a.template
				get_decayed_same_as<vk::anisotropy_enable>();
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::max_anisotropy> > 0
		) {
			ci.max_anisotropy = a.template
				get_decayed_same_as<vk::max_anisotropy>();
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::compare_enable> > 0
		) {
			ci.compare_enable = a.template
				get_decayed_same_as<vk::compare_enable>();
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::compare_op> > 0
		) {
			ci.compare_op = a.template
				get_decayed_same_as<vk::compare_op>();
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::min_lod> > 0
		) {
			ci.min_lod = a.template
				get_decayed_same_as<vk::min_lod>();
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::max_lod> > 0
		) {
			ci.max_lod = a.template
				get_decayed_same_as<vk::max_lod>();
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::border_color> > 0
		) {
			ci.border_color = a.template
				get_decayed_same_as<vk::border_color>();
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::unnormalized_coordinates> > 0
		) {
			ci.unnormalized_coordinates = a.template
				get_decayed_same_as<vk::unnormalized_coordinates>();
		}

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

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