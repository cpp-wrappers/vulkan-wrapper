export module vk.device_queue_create_info;

import vk_headers;
export import <cinttypes>;
export import <cxx_util/bitmask_from_enum.hpp>;
export import <cxx_util/int.hpp>;

export namespace vk {

enum class device_queue_create_flag { рrotected };

class device_queue_create_info {
	const u::int_with_size<sizeof(VkStructureType)> m_type = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	const void* m_next;
	u::bitmask_from_enum<device_queue_create_flag> m_flags;
	uint32_t m_queue_family_index;
	uint32_t m_queue_queue_count;
	const float* m_queue_priorities;
public:

	template<typename... Args>
	device_queue_create_info(Args&&... args) {
		
	}
};

}

static_assert(sizeof(vk::device_queue_create_info) == sizeof(VkDeviceQueueCreateInfo));