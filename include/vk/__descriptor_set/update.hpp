#pragma once

#include "./write.hpp"
#include "./copy.hpp"
#include "../__internal/function.hpp"
#include "../__device/handle.hpp"

namespace vk {

	struct update_descriptor_sets_function : vk::function<void(*)(
		handle<vk::device>::underlying_type device,
		uint32 descriptor_write_count,
		const vk::write_descriptor_set* descriptor_writes,
		uint32 descriptor_copy_count,
		const vk::copy_descriptor_set* descriptor_copies
	)> {
		static constexpr auto name = "vkUpdateDescriptorSets";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_range_of<is_same_as<vk::write_descriptor_set>.decayed> <= 1,
		is_range_of<is_same_as<vk::copy_descriptor_set>.decayed> <= 1
	>
	void update_descriptor_sets(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		uint32 write_count{};
		const vk::write_descriptor_set* writes = nullptr;

		if constexpr (
			(is_range_of<is_same_as<vk::write_descriptor_set>.decayed> > 0)
			.for_types<Args...>()
		) {
			auto& writes0 = a.template
				get<is_range_of<is_same_as<vk::write_descriptor_set>.decayed>>();

			write_count = (uint32) writes0.size();
			writes = writes0.iterator();
		}

		uint32 copy_count{};
		const vk::copy_descriptor_set* copies = nullptr;

		if constexpr (
			(is_range_of<is_same_as<vk::copy_descriptor_set>.decayed> > 0)
			.for_types<Args...>()
		) {
			auto& copies0 = a.template
				get<is_range_of<is_same_as<vk::copy_descriptor_set>.decayed>>();

			copy_count = (uint32) copies0.size();
			copies = copies0.iterator();
		}

		vk::get_device_function<vk::update_descriptor_sets_function>(
			instance, device
		)(
			device.underlying(),
			write_count,
			writes,
			copy_count,
			copies
		);
	}

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>> == 1,
		is_same_as<handle<vk::device>> == 1,
		is_same_as<vk::write_descriptor_set> == 1
	>
	void update_descriptor_set(Args... args) {
		tuple<Args...> a { args... };
		return vk::update_descriptor_sets(
			a.template get<is_same_as<handle<vk::instance>>>(),
			a.template get<is_same_as<handle<vk::device>>>(),
			array {
				a.template get<is_same_as<vk::write_descriptor_set>>()
			}
		);
	}

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>> == 1,
		is_same_as<handle<vk::device>> == 1,
		is_same_as<vk::copy_descriptor_set> == 1
	>
	void update_descriptor_set(Args... args) {
		tuple<Args...> a { args... };
		return vk::update_descriptor_sets(
			a.template get<is_same_as<handle<vk::instance>>>(),
			a.template get<is_same_as<handle<vk::device>>>(),
			array {
				a.template get<is_same_as<vk::copy_descriptor_set>>()
			}
		);
	}

} // vk