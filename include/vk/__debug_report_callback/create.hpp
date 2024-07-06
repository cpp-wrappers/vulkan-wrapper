#pragma once

#include "./handle.hpp"
#include "./create_info.hpp"
#include "../__internal/function.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__instance/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct create_debug_report_callback_function : vk::function<int32(*)(
		handle<vk::instance>::underlying_type instance,
		const vk::debug_report_callback_create_info* create_info,
		const void* allocator,
		handle<vk::debug_report_callback>::underlying_type* callback
	)> {
		static constexpr auto name = "vkCreateDebugReportCallbackEXT";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<vk::debug_report_flags> == 1,
		count_of_decayed_same_as<vk::debug_report_callback_type> == 1
	>
	vk::expected<handle<vk::debug_report_callback>>
	try_create_debug_report_callback(Args&&... args) {
		handle<vk::instance> instance = tuple{ args... }.template
			get_decayed_same_as<handle<vk::instance>>();

		auto flags = tuple{ args... }.template
			get_decayed_same_as<vk::debug_report_flags>();

		auto callback = tuple{ args... }.template
			get_decayed_same_as<vk::debug_report_callback_type>();

		debug_report_callback_create_info ci {
			.flags = flags,
			.callback = callback
		};

		handle<vk::debug_report_callback> debug_report_callback;

		vk::result result {
			vk::get_instance_function<
				vk::create_debug_report_callback_function
			>(instance)(
				instance.underlying(),
				&ci,
				nullptr,
				&debug_report_callback.underlying()
			)
		};

		if (result.error()) return result;

		return debug_report_callback;
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<vk::debug_report_flag> >= 0,
		count_of_decayed_same_as<vk::debug_report_callback_type> == 1
	>
	vk::expected<handle<vk::debug_report_callback>>
	try_create_debug_report_callback(Args&&... args) {
		tuple a { args... };

		vk::debug_report_flags flags{};

		a.template for_each([&]<typename Arg>(Arg& arg) {
			if constexpr(same_as<decay<Arg>, vk::debug_report_flag>) {
				flags.set(arg);
			}
		});

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		decltype(auto) callback = a.template
			get_decayed_same_as<vk::debug_report_callback_type>();

		return vk::try_create_debug_report_callback(
			instance,
			flags,
			callback
		);
	}

	template<typename... Args>
	handle<vk::debug_report_callback>
	create_debug_report_callback(Args&&... args) {
		vk::expected<handle<vk::debug_report_callback>> result
			= vk::try_create_debug_report_callback(forward<Args>(args)...);
		if (result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk