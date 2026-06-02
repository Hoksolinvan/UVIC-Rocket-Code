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

  if(HAL_I2C_Mem_Read(&hi2c2, BMP3_I2C_ADDR,reg_addr, I2C_MEMADD_SIZE_8BIT, data, (uint16_t)len,BMP3_I2C_TIMEOUT){
  return 0;
  }
  else{
    return -1
      }
    
  
}


BMP3_INTF_RET_TYPE i2c_write(uint8_t reg_addr,const uint8_t *data, uint32_t len, void *intf_ptr){

  if(HAL_I2C_Mem_Write(&hi2c2, BMP3_I2C_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT, data, (uint16_t)len,BMP3_I2C_TIMEOUT){
    return 0;
  }
  else{
    return -1}
  
}


void delay_us(uint32_t period, void *intf_ptr){
  return;}




int main(void){
HAL_Init();
SystemClock_Config();
MX_GPIO_Init();
MX_USART1_UART_Init();
MX_I2C2_Init();



struct bmp3_dev dev = {0};
struct bmp3_settings settings = {0};
struct bmp3_data data = {0};
struct bmp3_status status = {0};


  dev.intf = BMP3_I2C_INTF;
  dev.read = i2c_read;
  dev.write = i2c_write;
  dev.delay_us = delay_us;
  dev.intf_ptr = &hi2c2;

  rslt = bmp3_init(&dev);

  if(rslt != BMP3_OK){

    return 0;
  }
  settings.press_en = BMP3_ENABLE;
  settings.temp_en = BMP3_ENABLE;
  settings.odr_filter.press_os = BMP3_OVERSAMPLING_4X;
  settings.odr_filter.temp_os = BMP3_OVERSAMPLING_2X;
  settings.odr_filter.iir_filter = BMP3_IIR_FILTER_COEFF_3;
  settings.odr_filter.odr = BMP3_ODR_50_HZ;

  uint32_t settings_set = BMP3_SEL_PRESS_EN | BMP3_SEL_TEMP_EN | BMP3_SEL_PRESS_OS | BMP3_SEL_TEMP_OS | BMP3_SEL_IIR_FILTER | BMP3_SEL_ODR;

  rslt = bmp3_set_sensor_settings(settings_sel, &settings, &dev);
  settings.op_mode = BMP3_MODE_NORMAL;
  rslt = bmp3_set_op_mode(&settings, &dev);


  while(1){

  rslt = bmp3_get_sensor_data(BMP3_PRESS_TEMP, &data, &dev);
    snprintf(msg, sizeof(msg),"TEMP: %d C, Pressure: %d Pa \n",(int)data.temperature, (int)data.pressure);
    HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
    HAL_DELAY(500);
  }
  
}




void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    HAL_PWR_EnableBkUpAccess();
    __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_MSI;
    RCC_OscInitStruct.LSEState            = RCC_LSE_ON;
    RCC_OscInitStruct.MSIState            = RCC_MSI_ON;
    RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.MSIClockRange       = RCC_MSIRANGE_11;
    RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) Error_Handler();

    RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK3 | RCC_CLOCKTYPE_HCLK
                                     | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1
                                     | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_MSI;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.AHBCLK3Divider = RCC_SYSCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) Error_Handler();
}

void Error_Handler(void)
{
    __disable_irq();
    while (1) {}
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {}
#endif
