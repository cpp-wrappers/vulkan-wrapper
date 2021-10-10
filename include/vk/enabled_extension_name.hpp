#pragma once

#include <core/null_terminated_string_view.hpp>

namespace vk {

struct enabled_extension_name : null_terminated_string_view<size_is::undefined> {};

}