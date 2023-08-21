#include "main.h"

//************************************************************************************************************
void adc_check_event(void)
{
  if(DataUpdate.Need_batt_voltage_update)
  {
    while (PWR_GetFlagStatus(PWR_FLAG_VREFINTRDY) == DISABLE);
    adc_init();
    adc_calibration();
    ADC_Batt_Read();

    ADC_Cmd(ADC1, DISABLE);     // ����!
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, DISABLE);
    RCC_HSICmd(DISABLE);        // ��������� HSI
    ADCData.Batt_voltage = ((ADCData.Calibration_bit_voltage * ADCData.Batt_voltage_raw) / 1000) * 2;

    PumpPrescaler();

    DataUpdate.Need_batt_voltage_update = DISABLE;
  }
// -----------
}


//************************************************************************************************************
void adc_calibration(void)
{
  uint32_t i, x = 0;

  while (PWR_GetFlagStatus(PWR_FLAG_VREFINTRDY) == DISABLE);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_17, 1, ADC_SampleTime_384Cycles);  // ���������������� ������

  ADC_DelaySelectionConfig(ADC1, ADC_DelayLength_Freeze);       // �������� �� ������� ������ ������ �� ���

  ADC_PowerDownCmd(ADC1, ADC_PowerDown_Idle_Delay, ENABLE);     // ���������� ������� ��� � ���������� Idle � Delay

  ADC_Cmd(ADC1, ENABLE);        // ���!

  while (ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET);     // ���� ���� ������� ���

  for (i = 0; i < 10; i++)
  {
    ADC_SoftwareStartConv(ADC1);        // �������� ��������������
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);     // ���� ���� ���������� ��������������
    x += ADC_GetConversionValue(ADC1);
  }
  x /= 10;

  ADCData.Calibration_bit_voltage = ((Settings.VRef * 1000) / x);       // ������� �������� �����. ���������� ��������� 1.22�, �� ���� ��������� �������� ������������ ������������� 1 ���.
  ADCData.Power_voltage = ((ADCData.Calibration_bit_voltage * 4095) / 1000);

//  dac_reload();                 //������������� � ��� ����� ���������� ������� �������
}

//************************************************************************************************************
void adc_init(void)
{
  ADC_InitTypeDef ADC_InitStructure;
  uint32_t ccr = ADC->CCR;
  ccr &= ~ADC_CCR_ADCPRE;
  ccr |= ADC_CCR_ADCPRE_0;
  ADC->CCR = ccr;               // ������������� �������� �������������� ��� 500ksps ��� ������ ����������� �������

  RCC_HSICmd(ENABLE);           // �������� HSI

  while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);  // ���� ���� ����������� HSI


  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);  // ��������� ������������ ADC

  ADC_BankSelection(ADC1, ADC_Bank_B);

  ADC_StructInit(&ADC_InitStructure);
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;        // ���������� ��� 12 ���.
  ADC_InitStructure.ADC_ScanConvMode = DISABLE; // ����� ������������ ��������
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;   // ����������� �������������� - ����.
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;   // ������ ������������ ������ ���������
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        // ��������� ����� ����������
  ADC_InitStructure.ADC_NbrOfConversion = 1;    // ����� ��������������
  ADC_Init(ADC1, &ADC_InitStructure);

  ADC_DelaySelectionConfig(ADC1, ADC_DelayLength_Freeze);       // �������� �� ������� ������ ������ �� ���

  ADC_PowerDownCmd(ADC1, ADC_PowerDown_Idle_Delay, ENABLE);     // ���������� ������� ��� � ���������� Idle � Delay

  ADC_Cmd(ADC1, ENABLE);        // ���!

  while (ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET);     // ���� ���� ������� ���
}

//************************************************************************************************************
void ADC_Batt_Read(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  uint32_t i;
	//uint16_t temp, res;//test
	//uint16_t* c1 = ((uint16_t*)((uint32_t)0x1FF8007A));
	//uint16_t* c2 = ((uint16_t*)((uint32_t)0x1FF8007E));
	//uint16_t temp_c1 = *c1;
	//uint16_t temp_c2 = *c2;

  while (PWR_GetFlagStatus(PWR_FLAG_VREFINTRDY) == DISABLE);
  // ����� ��������� ���������� ���
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;    // ����� //���� ADC �� ���� ����! ������� �� PB12
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;  // ���������� �����
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;      // ��� ��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);        // ��������� ������������

  // ===============================================================================================  
  //����������� ���������� �������
	GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_18, 1, ADC_SampleTime_384Cycles);  // ���������������� ������
	GPIO_SetBits(GPIOB, GPIO_Pin_8);
  
  /*GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;    // �����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);        // ��������� ������������
  ADC_RegularChannelConfig(ADC1, ADC_Channel_20, 1, ADC_SampleTime_384Cycles);  // ���������������� ������

  GPIO_ResetBits(GPIOB, GPIO_Pin_15);   // ���������� ����������*/
	
  ADCData.Batt_voltage_raw = 0;
  for (i = 0; i < 10; i++)
  {
    ADC_SoftwareStartConv(ADC1);        // �������� ��������������
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);     // ���� ���� ���������� ��������������
    ADCData.Batt_voltage_raw += ADC_GetConversionValue(ADC1);
  }
  ADCData.Batt_voltage_raw /= 10;
  // ===============================================================================================  
  // ��������� ���������� ����
  /*GPIO_StructInit(&GPIO_InitStructure);
  //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOB, GPIO_InitStructure.GPIO_Pin);     // ���������� ����������*/
	
	  // �������
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;    // �����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);        // ��������� ������������
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM10);
	
	//===============================TEMPERATURE================
	
	/*ADC_TempSensorVrefintCmd(ENABLE); 
	delay_ms(100);//test
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_384Cycles);  // ���������������� ������
	temp = 0;
	for (i = 0; i < 10; i++)
  {
    ADC_SoftwareStartConv(ADC1);        // �������� ��������������
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);     // ���� ���� ���������� ��������������
    temp += ADC_GetConversionValue(ADC1);
  }
	temp /= 10;
	res = (80 / (temp_c2-temp_c1))*(temp-temp_c1) + 30;
	temp = res;
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_384Cycles);  // ���������������� ������*/
}
