#pragma once
#include "inttypes.h"

/// @brief Accepts a buffer and parses the request type.
void json_controller_parse(char* pkg);

/// @brief Packages sensor data into a JSON and transmits it.
void json_controller_pkg();

/// @brief Edits output percentage of flow rate.
void json_controller_edit_output(uint8_t percentage);