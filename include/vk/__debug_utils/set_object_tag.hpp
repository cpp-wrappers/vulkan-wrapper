#pragma once

#include "./object_tag_info.hpp"
#include "../__internal/function.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"

namespace vk::debug_utils {

	struct set_object_tag_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		const vk::debug_utils::object_tag_info* pTagInfo
	)> {
		static constexpr auto name = "vkSetDebugUtilsObjectTagEXT";
	};

}