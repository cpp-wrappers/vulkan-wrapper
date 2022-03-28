#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include "../../../instance/handle.hpp"
#include "../../../create_or_allocate.hpp"
#include "../../../unexpected_handler.hpp"
#include "../../../instance/get_proc_address.hpp"

#include <core/meta/decayed_same_as.hpp>

typedef int32 (VK_PTR* PFN_vkCreateDebugReportCallbackEXT)(
	handle<vk::instance> instance,
	const vk::debug_report_callback_create_info* create_info,
	const void* allocator,
	handle<vk::debug_report_callback>* callback
);

namespace vk {

	template<>
	struct vk::create_t<vk::debug_report_callback> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_possibly_guarded_handle_of<vk::instance>,
			types::are_contain_one_decayed<vk::debug_report_flags>,
			types::are_contain_one_decayed<vk::debug_report_callback_type>
		>::for_types<Args...>
		vk::expected<handle<vk::debug_report_callback>>
		operator () (Args&&... args) const {
			auto& instance = elements::possibly_guarded_handle_of<
				vk::instance
			>(args...);

			auto flags = elements::decayed<vk::debug_report_flags>(args...);
			auto& callback = elements::decayed<
				vk::debug_report_callback_type
			>(args...);

			debug_report_callback_create_info ci {
				.flags = flags,
				.callback = callback
			};

			handle<vk::debug_report_callback> debug_report_callback;

			auto fn =
				(PFN_vkCreateDebugReportCallbackEXT)
				vk::get_instance_proc_address(
					instance,
					"vkCreateDebugReportCallbackEXT"
				);

			if(fn == nullptr) vk::unexpected_handler();

			vk::result result {
				fn(
					vk::get_handle(instance),
					&ci,
					nullptr,
					&debug_report_callback
				)
			};

			if(result.error()) return result;

			return debug_report_callback;
		};

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_possibly_guarded_handle_of<vk::instance>,
			types::are_may_contain_decayed<vk::debug_report_flag>,
			types::are_contain_one_decayed<vk::debug_report_callback_type>
		>::for_types<Args...>
		vk::expected<handle<vk::debug_report_callback>>
		operator () (Args&&... args) const {
			vk::debug_report_flags flags{};

			elements::for_each_decayed<vk::debug_report_flag>(args...)(
				[&](auto flag) {
					flags.set(flag);
				}
			);

			auto& instance = elements::possibly_guarded_handle_of<vk::instance>(args...);
			auto& callback = elements::decayed<vk::debug_report_callback_type>(args...);

			return this->operator () (flags, instance, callback);
		}

	};

} // vk