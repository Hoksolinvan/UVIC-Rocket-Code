#pragma once

#include <stdint.h>

void spi_cs_low(void);
void spi_cs_high(void);


void spi_transfer(const uint8_t *tx, uint8_t *rx, uint32_t len);

