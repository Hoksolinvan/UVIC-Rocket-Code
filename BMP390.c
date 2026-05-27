/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "app_subghz_phy.h"
#include "bmp3.h"
#include "gpio.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
#define BMP3_I2C_ADDR (BMP3_ADDR_I2C_PRIM << 1)
#define BMP3_I2C_TIMEOUT 100

BMP3_INTF_RET_TYPE i2c_read(uint8_t reg_addr, uint8_t *data, uint32_t len, void *intf_ptr)
{
    HAL_I2C_Master_Transmit(&hi2c1, BMP3_I2C_ADDR, &reg_addr, 1, BMP3_I2C_TIMEOUT);
    HAL_I2C_Master_Receive(&hi2c1, BMP3_I2C_ADDR, data, len, BMP3_I2C_TIMEOUT);
    return 0;
}

BMP3_INTF_RET_TYPE i2c_write(uint8_t reg_addr, const uint8_t *data, uint32_t len, void *intf_ptr)
{
    HAL_I2C_Mem_Write(&hi2c1, BMP3_I2C_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT,
                      (uint8_t *)data, len, BMP3_I2C_TIMEOUT);
    return 0;
}

void delay_us(uint32_t period, void *intf_ptr)
{
    HAL_Delay((period + 999) / 1000);
}
int main(void)
{

  /* USER CODE BEGIN 1 */
	// create ADC device
	int8_t rslt;
	char msg[64];

	rslt = bmp3_init(&dev);
	snprintf(msg, sizeof(msg), "bmp3_init result: %d\r\n", rslt);
	HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);





  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */


  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SubGHz_Phy_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


  struct bmp3_dev dev;
     struct bmp3_settings settings = { 0 };
     struct bmp3_data data = { 0 };
     struct bmp3_status status = { 0 };

     dev.intf     = BMP3_I2C_INTF;
     dev.read     = i2c_read;
     dev.write    = i2c_write;
     dev.delay_us = delay_us;
     dev.intf_ptr = NULL;

     bmp3_init(&dev);

     settings.press_en = BMP3_ENABLE;
     settings.temp_en  = BMP3_ENABLE;
     settings.odr_filter.press_os   = BMP3_OVERSAMPLING_4X;
     settings.odr_filter.temp_os    = BMP3_OVERSAMPLING_2X;
     settings.odr_filter.iir_filter = BMP3_IIR_FILTER_COEFF_3;
     settings.odr_filter.odr        = BMP3_ODR_50_HZ;

     uint32_t settings_sel = BMP3_SEL_PRESS_EN   |
                             BMP3_SEL_TEMP_EN    |
                             BMP3_SEL_PRESS_OS   |
                             BMP3_SEL_TEMP_OS    |
                             BMP3_SEL_IIR_FILTER |
                             BMP3_SEL_ODR;

     bmp3_set_sensor_settings(settings_sel, &settings, &dev);

     settings.op_mode = BMP3_MODE_NORMAL;
     bmp3_set_op_mode(&settings, &dev);



     while (1)
     {
         rslt = bmp3_get_sensor_data(BMP3_PRESS_TEMP, &data, &dev);
         snprintf(msg, sizeof(msg), "read result: %d, Temp: %d, Press: %d\r\n",
                  rslt, (int)data.temperature, (int)data.pressure);
         HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
         HAL_Delay(500);
     }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_11;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK3|RCC_CLOCKTYPE_HCLK
                              |RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1
                              |RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK3Divider = RCC_SYSCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
