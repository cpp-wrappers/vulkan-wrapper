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
		is_convertible_to<handle<vk::instance>> == 1,
		is_convertible_to<handle<vk::device>> == 1,
		is_same_as<vk::image_create_flags>.decayed <= 1,
		is_same_as<vk::format>.decayed == 1,
		(
			is_same_as<vk::extent<3>>.decayed == 1 ||
			is_same_as<vk::extent<2>>.decayed == 1
		),
		is_same_as<vk::image_type>.decayed <= 1,
		is_same_as<vk::mip_levels>.decayed <= 1,
		is_same_as<vk::array_layers>.decayed <= 1,
		is_same_as<vk::sample_count>.decayed <= 1,
		is_same_as<vk::image_tiling>.decayed == 1,
		(
			is_same_as<vk::image_usages>.decayed == 1 ||
			is_same_as<vk::image_usage>.decayed > 0
		),
		is_same_as<vk::sharing_mode>.decayed <= 1,
		is_range_of<is_same_as<vk::queue_family_index>.decayed> <= 1,
		is_same_as<vk::initial_layout>.decayed <= 1
	>
	vk::expected<handle<vk::image>>
	try_create_image(Args&&... args) {
		tuple a { args... };

		auto instance = (handle<vk::instance>) a.template
			get<is_convertible_to<handle<vk::instance>>>();

		auto device = (handle<vk::device>) a.template
			get<is_convertible_to<handle<vk::device>>>();

		vk::image_create_info ci{};

		ci.format = a.template get<is_same_as<vk::format>.decayed>();
		ci.tiling = a.template get<is_same_as<vk::image_tiling>.decayed>();

		if constexpr (
			(is_same_as<vk::extent<3>>.decayed > 0).for_types<Args...>()
		) {
			ci.extent = a.template get<is_same_as<vk::extent<3>>.decayed>();
			ci.image_type = vk::image_type::three_d;
		}
		if constexpr (
			(is_same_as<vk::extent<2>>.decayed > 0).for_types<Args...>()
		) {
			ci.extent = vk::extent<3> {
				a.template get<is_same_as<vk::extent<2>>.decayed>(),
				1
			};
			ci.image_type = vk::image_type::two_d;
		}
		if constexpr (
			(is_same_as<vk::image_type>.decayed > 0).for_types<Args...>()
		) {
			ci.image_type = a.template
				get<is_same_as<vk::image_type>.decayed>();
		}

		if constexpr (
			(is_same_as<vk::image_usages>.decayed > 0).for_types<Args...>()
		){
			ci.usages = a.template get<is_same_as<vk::image_usages>.decayed>();
		}
		a.template pass<is_same_as<vk::image_usage>.decayed>(
			[&](auto... usages) {
				(ci.usages.set(usages), ...);
			}
		);

		if constexpr (
			(is_same_as<vk::image_create_flags>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.flags = a.template
				get<is_same_as<vk::image_create_flags>.decayed>();
		}

		if constexpr (
			(is_same_as<vk::mip_levels>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.mip_levels = a.template
				get<is_same_as<vk::mip_levels>.decayed>();
		}

		if constexpr (
			(is_same_as<vk::array_layers>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.array_layers = a.template
				get<is_same_as<vk::array_layers>.decayed>();
		}

		if constexpr (
			(is_same_as<vk::sample_count>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.samples = a.template
				get<is_same_as<vk::sample_count>.decayed>();
		}

		if constexpr (
			(is_same_as<vk::sharing_mode>.decayed > 0)
			.for_types<Args...>()
		) {
			ci.sharing_mode = a.template
				get<is_same_as<vk::sharing_mode>.decayed>();
		}

		if constexpr (
			(is_same_as<vk::initial_layout>.decayed > 0).for_types<Args...>()
		) {
			ci.initial_layout = a.template
				get<is_same_as<vk::initial_layout>.decayed>();
		}

		if constexpr (types<Args...>::template
			count_of<is_range_of<
				is_same_as<vk::queue_family_index>.decayed
			>> > 0
		) {
			auto& queues = a.template
				get<is_range_of<is_same_as<vk::queue_family_index>.decayed>>();
			
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

		if (result.error()) return result;

		return image;

	};

	template<typename... Args>
	handle<vk::image> create_image(Args&&... args) {
		vk::expected<handle<vk::image>> result =
			vk::try_create_image(forward<Args>(args)...);
		if (result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk