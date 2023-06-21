#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <optional>

struct QueueFamilyIndexes {
    std::optional<uint32_t> graphicsFamily;

    bool isComplete();
};


QueueFamilyIndexes findQueueFamilies(VkPhysicalDevice device);