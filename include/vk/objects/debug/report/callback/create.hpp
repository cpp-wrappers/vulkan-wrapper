#pragma once

#include "handle.hpp"
#include "create_info.hpp"
#include "../../../instance/handle.hpp"
#include "../../../../object/create_or_allocate.hpp"

#include <core/meta/types/are_contain_decayed_same_as.hpp>

namespace vk {

	template<>
	struct vk::create_t<vk::debug_report_callback> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::instance>,
			types::are_contain_one_decayed_same_as<vk::debug_report_flags>,
			types::are_contain_one_decayed_same_as<vk::debug_report_callback_type>
		>::for_types<Args...>
		vk::expected<vk::handle<vk::debug_report_callback>>
		operator () (Args&&... args) const {
			auto& instance = elements::vk::possibly_guarded_handle_of<vk::instance>(args...);
			auto flags = elements::decayed_same_as<vk::debug_report_flags>(args...);
			auto& callback = elements::decayed_same_as<vk::debug_report_callback_type>(args...);

			debug_report_callback_create_info ci {
				.flags = flags,
				.callback = callback
			};

			vk::handle<vk::debug_report_callback> debug_report_callback;

			auto fn = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(
				(VkInstance) vk::get_handle_value(instance),
				"vkCreateDebugReportCallbackEXT"
			);

			if(fn == nullptr) default_unexpected_handler();

			vk::result result {
				(int32) fn(
					(VkInstance) vk::get_handle_value(instance),
					(VkDebugReportCallbackCreateInfoEXT*) &ci,
					(VkAllocationCallbacks*) nullptr,
					(VkDebugReportCallbackEXT*) &debug_report_callback
				)
			};

			if(result.error()) return result;

			return debug_report_callback;
		};

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::instance>,
			types::are_may_contain_decayed_same_as<vk::debug_report_flag>,
			types::are_contain_one_decayed_same_as<vk::debug_report_callback_type>
		>::for_types<Args...>
		vk::expected<vk::handle<vk::debug_report_callback>>
		operator () (Args&&... args) const {
			vk::debug_report_flags flags{};

			elements::for_each_decayed_same_as<vk::debug_report_flag>(args...)(
				[&](auto flag) {
					flags.set(flag);
				}
			);

			auto& instance = elements::vk::possibly_guarded_handle_of<vk::instance>(args...);
			auto& callback = elements::decayed_same_as<vk::debug_report_callback_type>(args...);

			return this->operator () (flags, instance, callback);
		}

	};

} // vk