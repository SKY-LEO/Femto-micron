#include "main.h"
/*
void dac_init()
{
  DAC_InitTypeDef DAC_InitStructure;
  //--------------------------------------------------------------------
  //������������� ������� �������������� �������
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

  DAC_StructInit(&DAC_InitStructure);
  DAC_InitStructure.DAC_Trigger = DAC_Trigger_Software;
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;

  DAC_Init(DAC_Channel_2, &DAC_InitStructure);
  DAC_Cmd(DAC_Channel_2, ENABLE);
  DAC_SetChannel2Data(DAC_Align_12b_R, ADCData.DAC_voltage_raw);        // Set DAC Channel2 DHR register: DAC_OUT2 = (1.224 * 128) / 256 = 0.612 V 

}

void dac_off()
{
  DAC_Cmd(DAC_Channel_2, DISABLE);
  //DAC_DeInit();
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, DISABLE);
}

void dac_on()
{
  //dac_init();
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
  DAC_Cmd(DAC_Channel_2, ENABLE);
}


void dac_reload()
{
  dac_init();
  ADCData.DAC_voltage_raw = 1;
  if(Settings.Geiger_voltage > 200)
  {
    // �1 = 200  - ������� �� ����� ��
    // �2 = 34   - ��������� ������������ �������� (1�+33�)/1�  (! �������� ������ 1/x)
    // �3 = 45   - ��������� ��������������� �������� 1000-(1000*(10��/(10��+470��))) (��������������� ��� ����������)
    // �4 = 11   - ��������� ������������� (10+1:1)
    // 1000 - ���������� � ������������, ��� ����������� ������ �������������� �������
    // ������ ����������� ������ � XLS ����� !!!
    // ADCData.DAC_voltage_raw=(((Settings.Geiger_voltage*(1000-K3 ))/K4)-K1 )/K2; 
    ADCData.DAC_voltage_raw = (((Settings.Geiger_voltage * (1000 - 21)) / 11) - 200) / 34;
  }

  ADCData.DAC_voltage_raw = (ADCData.DAC_voltage_raw * 1000) / ADCData.Calibration_bit_voltage; // ��������� �������� �� ���������� �����

  DAC_SetChannel2Data(DAC_Align_12b_R, ADCData.DAC_voltage_raw);        // Set DAC Channel2 DHR register: DAC_OUT2 = (1.224 * 128) / 256 = 0.612 V 
  DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);
}
*/
