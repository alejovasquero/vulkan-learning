#include "vk_queue.h"
#include <vector>

bool QueueFamilyIndexes::isComplete() {
    return graphicsFamily.has_value();
}


QueueFamilyIndexes findQueueFamilies(VkPhysicalDevice device) {
    QueueFamilyIndexes indices;


    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        i++;
    }

    return indices;
}