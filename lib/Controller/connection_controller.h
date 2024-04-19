#pragma once
#include <stdbool.h>

typedef void (*server_callback)(char *);

void connection_control_callback();
bool connection_control_init(server_callback callback);
bool connection_controller_transmit(char *package, int length);