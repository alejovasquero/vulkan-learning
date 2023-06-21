#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>

std::vector<VkPhysicalDevice> get_vk_physical_devices(VkInstance& instance);

void pick_physical_device(VkInstance& instance, std::vector<VkPhysicalDevice>* predefined_devices, VkPhysicalDevice* pdevice);