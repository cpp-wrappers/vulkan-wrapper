#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__pipeline/bind_point.hpp"
#include "../__pipeline_layout/handle.hpp"
#include "../__descriptor_set/handle.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	class first_set {
		uint32 value_;
	public:
		first_set() = default;
		first_set(uint32 value) : value_ { value } {}
		operator uint32 () const { return value_; }
	};
	struct dynamic_offset { uint32 _; };

	struct cmd_bind_descriptor_sets_function : vk::function<void(*)(
		handle<vk::command_buffer>::underlying_type command_buffer,
		vk::pipeline_bind_point pipeline_bind_point,
		handle<vk::pipeline_layout>::underlying_type layout,
		uint32 first_set,
		uint32 descriptor_set_count,
		const handle<vk::descriptor_set>::underlying_type* descriptor_sets,
		uint32 dynamic_offset_count,
		const vk::dynamic_offset* dynamic_offsets
	)> {
		static constexpr auto name = "vkCmdBindDescriptorSets";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::command_buffer>> == 1,
		count_of_decayed_same_as<vk::pipeline_bind_point> == 1,
		count_of_decayed_same_as<handle<vk::pipeline_layout>> == 1,
		count_of_decayed_same_as<vk::first_set> <= 1,
		count_of_range_of_decayed<handle<vk::descriptor_set>> == 1,
		count_of_range_of_decayed<vk::dynamic_offset> <= 1
	>
	void cmd_bind_descriptor_sets(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();

		vk::pipeline_bind_point bind_point = a.template
			get_decayed_same_as<vk::pipeline_bind_point>();

		handle<vk::pipeline_layout> pipeline_layout = a.template
			get_decayed_same_as<handle<vk::pipeline_layout>>();

		vk::first_set first{};
		
		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::first_set> > 0
		) {
			first = a.template
				get_decayed_same_as<vk::first_set>();
		}

		auto& sets = a.template
			get_range_of_decayed<handle<vk::descriptor_set>>();

		uint32 dynamic_offset_count = 0;
		const vk::dynamic_offset* dynamic_offsets = nullptr;

		if constexpr (types<Args...>::template
			count_of_range_of_decayed<vk::dynamic_offset> > 0
		) {
			auto& offsets = a.template
				get_range_of_decayed<vk::dynamic_offset>();
			dynamic_offset_count = (uint32) offsets.size();
			dynamic_offsets = offsets.iterator();
		}

		vk::get_device_function<vk::cmd_bind_descriptor_sets_function>(
			instance, device
		)(
			command_buffer.underlying(),
			bind_point,
			pipeline_layout.underlying(),
			(uint32) first,
			(uint32) sets.size(),
			(const handle<vk::descriptor_set>::underlying_type*)
				sets.iterator(),
			dynamic_offset_count,
			dynamic_offsets
		);
	} // cmd_bind_descriptor_sets

} // vk