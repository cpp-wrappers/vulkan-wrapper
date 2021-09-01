#pragma once

#include "headers.hpp"

namespace vk {

enum class attachment_store_op {
	store = VK_ATTACHMENT_STORE_OP_STORE,
	dont_care = VK_ATTACHMENT_STORE_OP_DONT_CARE
};

}