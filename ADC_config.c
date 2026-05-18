int main(){

ADC_InitTypeDef ADC_first;
	ADC_first.ClockPrescaler =	ADC_CLOCK_SYNC_PCLK_DIV2;
	ADC_first.Resolution = ADC_RESOLUTION_12B;
	ADC_first.DataAlign = ADC_DATAALIGN_RIGHT;
	ADC_first.ScanConvMode = ADC_SCAN_DISABLE;
	ADC_first.EOCSelection = ADC_EOC_SINGLE_CONV;
	ADC_first.LowPowerAutoWait = DISABLE;
	ADC_first.LowPowerAutoPowerOff = DISABLE;
	ADC_first.ContinuousConvMode = ENABLE;
	ADC_first.NbrOfConversion = 1;
	ADC_first.DiscontinuousConvMode = DISABLE;
	ADC_first.ExternalTrigConv = ADC_SOFTWARE_START;
	ADC_first.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	ADC_first.DMAContinuousRequests = ENABLE;
	ADC_first.Overrun = ADC_OVR_DATA_OVERWRITTEN;
	ADC_first.SamplingTimeCommon1 = ADC_SAMPLETIME_7CYCLES_5;
	ADC_first.SamplingTimeCommon2 = ADC_SAMPLETIME_7CYCLES_5;
	ADC_first.OversamplingMode = DISABLE;
	ADC_first.Oversampling.Ratio = ADC_OVERSAMPLING_RATIO_16;
	ADC_first.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_4;
	ADC_first.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;
	ADC_first.TriggerFrequencyMode = ADC_TRIGGER_FREQ_HIGH;

}
