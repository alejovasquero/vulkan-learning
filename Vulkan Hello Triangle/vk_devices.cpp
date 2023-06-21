#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <stdexcept>
#include "vk_queue.h"

std::vector<VkPhysicalDevice> get_vk_physical_devices(VkInstance& instance) {
	uint32_t n_devices = 0;

	vkEnumeratePhysicalDevices(instance, &n_devices, nullptr);


	if (n_devices == 0) {
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}

	std::vector<VkPhysicalDevice> query_devices(n_devices);
	printf("VECTOR POINTER %p\n", &query_devices);
	vkEnumeratePhysicalDevices(instance, &n_devices, query_devices.data());

	return query_devices;
}

bool is_suitable(VkPhysicalDevice& device) noexcept {
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
	
	printf("Evaluating device: %s\n", deviceProperties.deviceName);

	QueueFamilyIndexes indices = findQueueFamilies(device);

	return indices.isComplete();
}

void pick_physical_device(VkInstance& instance, std::vector<VkPhysicalDevice>* predefined_devices, VkPhysicalDevice* pdevice) {
	std::vector<VkPhysicalDevice> devices;

	if (predefined_devices == nullptr) {
		devices = get_vk_physical_devices(instance);
	}
	else {
		devices = *predefined_devices;
	}

	printf("VECTOR POINTER %p\n", &devices);

	VkPhysicalDevice* device = nullptr;

	for (auto& device_to_check : devices) {
		if (is_suitable(device_to_check)) {
			device = &device_to_check;
		}
	}

	if (device == nullptr) {
		throw std::runtime_error("Devices not suitable for engine.");
	}

	printf("Successfully picked device\n");
	*pdevice = std::move(*device);
}