#pragma once

bool validate_layers_existence(std::vector<const char*> layers);

std::vector<char*> get_vk_available_validation_layers();