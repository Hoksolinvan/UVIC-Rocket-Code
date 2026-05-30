#include "main.h"
#include "i2c.h"
#include "bmp3.h"
#include "gpio.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>

void SystemClock_Config(void);


#define BMP3_I2C_ADDR (BMP3_ADDR_I2C_PRIM << 1)
#define BMP3_I2C_TIMEOUT 100

BMP3_INTF_RET_TYPE i2c_read(uint8_t reg_addr, uint8_t *data, uint32_t len, void *intf_ptr){

  if(HAL_I2C_Mem_Read(&hi2c2, BMP3_I2C_ADDR, 
  
}
