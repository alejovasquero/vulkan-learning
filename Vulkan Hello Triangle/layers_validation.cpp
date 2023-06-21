#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <memory>
#include <string.h>
#include <stdlib.h>
#include <vector>

std::vector<char *> get_vk_available_validation_layers() {
	uint32_t layers_number;
	vkEnumerateInstanceLayerProperties(&layers_number, nullptr);

	std::vector<VkLayerProperties> properties = std::vector<VkLayerProperties>(layers_number);

	vkEnumerateInstanceLayerProperties(&layers_number, properties.data());

	printf("Validation layers available\n");
	std::vector<char *> layerNames = std::vector<char *>(layers_number);

	for (uint32_t i = 0; i < layers_number; i++) {
		printf("\t%s\n", properties[i].layerName);
		layerNames[i] = (char*)calloc(strlen(properties[i].layerName) + 1, sizeof(char));

		strcpy_s(layerNames[i], (strlen(properties[i].layerName) + 1) * sizeof(char), properties[i].layerName);
	}

	return layerNames;
}

bool validate_layers_existence(std::vector<const char*> layers) {
	std::vector<char *> supported_layers = get_vk_available_validation_layers();

	bool all_supported = true;

	for (auto i = 0; i < layers.size(); i++) {
		bool found = false;
		for (auto j = 0; j < supported_layers.size(); j++) {
			if (strcmp(layers[i], supported_layers[j]) == 0) {
				found = true;
			}
		}

		if (!found) {
			all_supported = false;
		}
	}

	for (uint32_t i = 0; i < supported_layers.size(); i++) {
		free(supported_layers[i]);
	}

	return all_supported;
}