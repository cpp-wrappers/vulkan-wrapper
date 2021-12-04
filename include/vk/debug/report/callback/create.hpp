#pragma once

#include <core/elements/one_of.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/elements/of_type.hpp>

#include "handle.hpp"
#include "create_info.hpp"
#include "../../../shared/result.hpp"
#include "../../../shared/headers.hpp"
#include "../../../instance/handle.hpp"

namespace vk {

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::instance>::equals<1>,
			types::count_of_type<vk::debug_report_flags>::equals<1>,
			types::count_of_type<vk::debug_report_callback_type>::equals<1>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::debug_report_callback>
	try_create_debug_report_callback(Args... args) {
		vk::instance instance = elements::of_type<vk::instance&>::for_elements_of(args...);
		auto flags = elements::of_type<vk::debug_report_flags&>::for_elements_of(args...);
		auto callback = elements::of_type<vk::debug_report_callback_type&>::for_elements_of(args...);

		debug_report_callback_create_info ci {
			.flags = flags,
			.callback = callback
		};

		VkDebugReportCallbackEXT debug_report_callback;

		auto fn = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(
			(VkInstance) instance.handle,
			"vkCreateDebugReportCallbackEXT"
		);

		vk::result result {
			(int32) fn(
				(VkInstance) instance.handle,
				(VkDebugReportCallbackCreateInfoEXT*) &ci,
				(VkAllocationCallbacks*) nullptr,
				(VkDebugReportCallbackEXT*) &debug_report_callback
			)
		};

		if(result.success()) return vk::debug_report_callback{ debug_report_callback };

		return result;
	};

	template<typename... Args>
	vk::debug_report_callback
	create_debug_report_callback(Args&&... args) {
		auto result = try_create_debug_report_callback(forward<Args>(args)...);
		if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
		return result.template get<vk::debug_report_callback>();
	}

}