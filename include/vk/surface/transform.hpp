#pragma once

namespace vk {

	enum class surface_transform {
		identity                     = 0x00000001,
		rotate_90                    = 0x00000002,
		rotate_180                   = 0x00000004,
		rotate_270                   = 0x00000008,
		horizontal_mirror            = 0x00000010,
		horizontal_mirror_rotate_90  = 0x00000020,
		horizontal_mirror_rotate_180 = 0x00000040,
		horizontal_mirror_rotate_270 = 0x00000080,
		inherit                      = 0x00000100
	};

} // vk