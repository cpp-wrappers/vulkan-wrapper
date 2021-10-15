#pragma once

namespace vk {

struct image;

struct image_view {
	image_view() = delete;
	image_view(const image_view&) = delete;
};

}