#pragma once

#include "headers.hpp"
#include "shader_module_create_info.hpp"
#include <functional>
#include "result.hpp"
#include <core/named.hpp>

namespace vk {

struct code_size : named<uint32_t>{};
struct code : named<uint32_t*>{};

struct shader_module {

};

} // vk