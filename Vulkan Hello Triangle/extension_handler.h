#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include<vector>


void validate_vk_extension_satisfied(bool enable_validation_layers);

std::vector<const char*> get_glfw_required_extensions(bool enable_validation_layers);

std::vector<const char*> get_vulkan_supported_extensions();