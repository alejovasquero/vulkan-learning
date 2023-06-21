#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdexcept>
#include <vector>


std::vector<const char*> get_glfw_required_extensions(bool enable_validation_layers) {
    uint32_t required_extensions_number;
    const char** extension_list;
    extension_list = glfwGetRequiredInstanceExtensions(&required_extensions_number);

    std::vector<const char*> extensions_required(extension_list, extension_list + required_extensions_number);

    if (enable_validation_layers) {
        extensions_required.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions_required;
}

std::vector<char*> get_vulkan_supported_extensions() {
    uint32_t vulkan_supported_extensions;

    vkEnumerateInstanceExtensionProperties(nullptr, &vulkan_supported_extensions, nullptr);


    std::vector<VkExtensionProperties> properties(vulkan_supported_extensions);

    vkEnumerateInstanceExtensionProperties(nullptr, &vulkan_supported_extensions, properties.data());

    std::vector<char*> extensions_required(vulkan_supported_extensions);

    for (uint32_t i = 0; i < vulkan_supported_extensions; i++) {
        extensions_required[i] = (char*) malloc(sizeof(char) * (strlen(properties[i].extensionName) + 1));
        strcpy_s(extensions_required[i], sizeof(char)*(strlen(properties[i].extensionName) + 1) ,properties[i].extensionName);
    }

    return extensions_required;
}



void validate_vk_extension_satisfied(bool enable_validation_layers) {
    printf("Validating extensions for instance\n");

    std::vector<const char*> required_extensions = get_glfw_required_extensions(true);

    printf("GLWF extension required:\n");
    for (auto& ext : required_extensions) {
        printf("\t%s\n", ext);
    }


    std::vector<char*> vulkan_supported_extensions = get_vulkan_supported_extensions();

    printf("VULKAN supported extensions:\n");
    for (auto& ext : vulkan_supported_extensions) {
        printf("\t%s\n", ext);
    }

    for (auto i = 0; i < required_extensions.size(); i++) {
        bool found = false;


        for (auto j = 0; j < vulkan_supported_extensions.size(); j++) {
            if (strcmp(required_extensions[i], vulkan_supported_extensions[j]) == 0) {
                found = true;
            }

        }

        if (!found) {
            throw std::runtime_error("Extension not supported");
        }
    }


    for (auto i = 0; i < vulkan_supported_extensions.size(); i++) {
        delete vulkan_supported_extensions[i];
    }

}

