#pragma once

#include <core/integer.hpp>

#define VK_DEFINE_NON_DISPATCHABLE_HANDLE(object) typedef uint64 object;

#include <vulkan/vulkan.h>