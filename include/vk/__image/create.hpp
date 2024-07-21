#pragma once

#include "./handle.hpp"
#include "./create_info.hpp"
#include "../__internal/function.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"
#include "../__image/handle.hpp"
#include "../__instance/handle.hpp"
#include "../__internal/result.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct create_image_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		const vk::image_create_info* create_info,
		const void* allocator,
		handle<vk::image>::underlying_type* image
	)> {
		static constexpr auto name = "vkCreateImage";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<vk::image_create_flags>.decayed <= 1,
		is_same_as<vk::image_type>.decayed == 1,
		is_same_as<vk::format>.decayed == 1,
		is_same_as<vk::extent<3>>.decayed == 1,
		is_same_as<vk::mip_levels>.decayed <= 1,
		is_same_as<vk::array_layers>.decayed <= 1,
		is_same_as<vk::sample_count>.decayed <= 1,
		is_same_as<vk::image_tiling>.decayed == 1,
		is_same_as<vk::image_usages>.decayed == 1,
		is_same_as<vk::sharing_mode>.decayed <= 1,
		count_of_range_of_decayed<vk::queue_family_index> <= 1,
		is_same_as<vk::initial_layout>.decayed <= 1
	>
	vk::expected<handle<vk::image>>
	try_create_image(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		vk::image_create_info ci{};

		ci.image_type = a.template get_decayed_same_as<vk::image_type>();
		ci.format = a.template get_decayed_same_as<vk::format>();
		ci.extent = a.template get_decayed_same_as<vk::extent<3>>();
		ci.tiling = a.template get_decayed_same_as<vk::image_tiling>();
		ci.usages = a.template get_decayed_same_as<vk::image_usages>();

		if constexpr (
			(is_same_as<vk::image_create_flags>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.flags = a.template
				get_decayed_same_as<vk::image_create_flags>();
		}

		if constexpr (
			(is_same_as<vk::mip_levels>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.mip_levels = a.template
				get_decayed_same_as<vk::mip_levels>();
		}

		if constexpr (
			(is_same_as<vk::array_layers>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.array_layers = a.template
				get_decayed_same_as<vk::array_layers>();
		}

		if constexpr (
			(is_same_as<vk::sample_count>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.samples = a.template
				get_decayed_same_as<vk::sample_count>();
		}

		if constexpr (
			(is_same_as<vk::sharing_mode>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.sharing_mode = a.template
				get_decayed_same_as<vk::sharing_mode>();
		}

		if constexpr (
			(is_same_as<vk::initial_layout>.decayed > 0).for_types<Args...>()
		) {
			ci.initial_layout = a.template
				get_decayed_same_as<vk::initial_layout>();
		}

		if constexpr (types<Args...>::template
			count_of_range_of_decayed<vk::queue_family_index> > 0
		) {
			auto& queues = a.template
				get_range_of_decayed<vk::queue_family_index>();
			
			ci.queue_family_index_count = (uint32) queues.size();
			ci.queue_family_indices = queues.iterator();
		}

		handle<vk::image> image;

		vk::result result {
			vk::get_device_function<vk::create_image_function>(
				instance, device
			)(
				device.underlying(),
				&ci,
				nullptr,
				&image.underlying()
			)
		};

		if(result.error()) return result;

		return image;

	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<vk::image_create_flags>.decayed <= 1,
		is_same_as<vk::format>.decayed == 1,
		is_same_as<vk::extent<3>>.decayed == 1,
		is_same_as<vk::mip_levels>.decayed <= 1,
		is_same_as<vk::array_layers>.decayed <= 1,
		is_same_as<vk::sample_count>.decayed <= 1,
		is_same_as<vk::image_tiling>.decayed == 1,
		is_same_as<vk::image_usages>.decayed == 1,
		is_same_as<vk::sharing_mode>.decayed <= 1,
		count_of_range_of_decayed<vk::queue_family_index> <= 1,
		is_same_as<vk::initial_layout>.decayed <= 1
	>
	vk::expected<handle<vk::image>>
	try_create_image(Args&&... args) {
		return try_create_image(
			vk::image_type::three_d,
			forward<Args>(args)...
		);
	}

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<vk::image_create_flags>.decayed <= 1,
		is_same_as<vk::format>.decayed == 1,
		is_same_as<vk::extent<2>>.decayed == 1,
		is_same_as<vk::mip_levels>.decayed <= 1,
		is_same_as<vk::array_layers>.decayed <= 1,
		is_same_as<vk::sample_count>.decayed <= 1,
		is_same_as<vk::image_tiling>.decayed == 1,
		is_same_as<vk::image_usages>.decayed == 1,
		is_same_as<vk::sharing_mode>.decayed <= 1,
		count_of_range_of_decayed<vk::queue_family_index> <= 1,
		is_same_as<vk::initial_layout>.decayed <= 1
	>
	vk::expected<handle<vk::image>>
	try_create_image(Args&&... args) {
		tuple _args{ args... };

		vk::extent<2> extent_2
			= _args.template get_satisfying_predicate<
				is_same_as<vk::extent<2>>.decayed
			>();

		return _args.template pass_satisfying_predicate<
			!is_same_as<vk::extent<2>>.decayed
		>([&]<typename... _Args>(_Args&&... _args) {
			return try_create_image(
				vk::image_type::two_d,
				vk::extent<3>{ extent_2, 1 },
				forward<_Args>(_args)...
			);
		});
	}

	template<typename... Args>
	handle<vk::image> create_image(Args&&... args) {
		vk::expected<handle<vk::image>> result =
			vk::try_create_image(forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk