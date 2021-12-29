#pragma once

#include "handle.hpp"
#include "create_info.hpp"
#include "../../../instance/handle.hpp"
#include "../../../shared/create.hpp"

namespace vk {

	template<>
	struct vk::try_create_t<vk::debug_report_callback> {

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::vk::contain_one<vk::instance>,
				types::count_of_type<vk::debug_report_flags>::equals<1>::ignore_const::ignore_reference,
				types::count_of_type<vk::debug_report_callback_type>::equals<1>
			>::for_types_of<Args...>
		)
		elements::one_of<vk::result, vk::handle<vk::debug_report_callback>>
		operator () (Args&&... args) const {
			auto& instance = elements::vk::of_type<vk::instance>::for_elements_of(args...);
			auto flags = elements::of_type<vk::debug_report_flags>::ignore_const::ignore_reference::for_elements_of(args...);
			auto& callback = elements::of_type<vk::debug_report_callback_type>::for_elements_of(args...);

			debug_report_callback_create_info ci {
				.flags = flags,
				.callback = callback
			};

			VkDebugReportCallbackEXT debug_report_callback;

			auto fn = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(
				(VkInstance) vk::get_handle_value(instance),
				"vkCreateDebugReportCallbackEXT"
			);

			if(fn == nullptr) throw;

			vk::result result {
				(int32) fn(
					(VkInstance) vk::get_handle_value(instance),
					(VkDebugReportCallbackCreateInfoEXT*) &ci,
					(VkAllocationCallbacks*) nullptr,
					(VkDebugReportCallbackEXT*) &debug_report_callback
				)
			};

			if(result.success()) return vk::handle<vk::debug_report_callback>{ debug_report_callback };

			return result;
		};
	};

}