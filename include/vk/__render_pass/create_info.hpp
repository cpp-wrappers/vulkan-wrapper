#pragma once

#include "./attachment_description.hpp"
#include "subpass_description.hpp"
#include "subpass_dependency.hpp"

namespace vk {

	struct render_pass_create_info {
		uint32                            structure_type = 38;
		const void*                       next;
		uint32                            flags;
		uint32                            attachment_count;
		const vk::attachment_description* attachments;
		uint32                            subpass_count;
		const vk::subpass_description*    subpasses;
		uint32                            dependency_count;
		const vk::subpass_dependency*     dependencies;
	};
}