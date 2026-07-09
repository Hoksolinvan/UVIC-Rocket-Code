#pragma once

#include <stdint.h>
#include <stdbool.h>

#define CHIP_ERASE 0xC7
#define WRITE_ENABLE 0x06


void send_write_enable(void);
