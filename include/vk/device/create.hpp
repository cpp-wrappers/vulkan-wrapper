#pragma once

namespace vk {

template<typename... Args>
requires()
vk::device& create_device(Args... args) const {
	vk::device_create_info ci{};
	ci.queue_create_info_count = types::of<Args...>::template count_of_same_as_type<vk::device_queue_create_info>;
	storage<10000> dqcis_storage[ci.queue_create_info_count];
	vk::device_queue_create_info* dqcis = (vk::device_queue_create_info*)dqcis_storage;
	ci.queue_create_infos = dqcis;
	std::size_t current = 0;
	tuple{ args... }
		.get([&](vk::device_queue_create_info dqci) {
			dqcis[current++] = dqci;
		})
		.get([&](vk::enabled_extension_count c) {
			ci.enabled_extension_count = c;
		})
		.get([&](vk::enabled_extension_names n) {
			ci.enabled_extension_names = n;
		})
	;
	vk::device* device;
	vk::throw_if_error(
		vkCreateDevice(
			(VkPhysicalDevice) this,
			(VkDeviceCreateInfo*) &ci,
			nullptr,
			(VkDevice*) &device
		)
	);
	return *device;
}
}