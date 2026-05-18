#include "stm32wlxx_hal_adc.h"



int main(){
	 HAL_Init();
	  SystemClock_Config();


  	ADC_HandleTypeDef ADC_handle;
  	ADC_handle.Instance = ADC;
  	ADC_handle.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  	ADC_handle.Init.Resolution = ADC_RESOLUTION_12B;
  	ADC_handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  	ADC_handle.Init.ScanConvMode = ADC_SCAN_DISABLE;
  	ADC_handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  	ADC_handle.Init.LowPowerAutoWait = DISABLE;
  	ADC_handle.Init.LowPowerAutoPowerOff = DISABLE;
  	ADC_handle.Init.ContinuousConvMode = ENABLE;
  	ADC_handle.Init.NbrOfConversion = 1;
  	ADC_handle.Init.DiscontinuousConvMode = DISABLE;
  	ADC_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  	ADC_handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  	ADC_handle.Init.DMAContinuousRequests = ENABLE;
  	ADC_handle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  	ADC_handle.Init.SamplingTimeCommon1 = ADC_SAMPLETIME_7CYCLES_5;
  	ADC_handle.Init.SamplingTimeCommon2 = ADC_SAMPLETIME_7CYCLES_5;
  	ADC_handle.Init.OversamplingMode = DISABLE;
  	ADC_handle.Init.TriggerFrequencyMode = ADC_TRIGGER_FREQ_HIGH;
  	HAL_ADC_Init(&ADC_handle);
  	HAL_ADC_Start(&ADC_handle);



	 while (1)
    {
      /* USER CODE END WHILE */
//	   char *msg = "Place holder text goes here brrr\r\n";

	    // Transmit message via UART
	    // Parameters: UART handle, data pointer, data size, timeout (ms)

	  HAL_ADC_PollForConversion(&ADC_handle,100);
	  uint32_t temp = HAL_ADC_GetValue(&ADC_handle);
	  if(temp<=3.5){
		  // exit
		  HAL_PWREx_EnterSHUTDOWNMode();

	  }


	    // Wait 1 second before sending again

      /* USER CODE BEGIN 3 */
    }
}
