#include "main.h"

uint32_t msTicks = 0;           // counts 1ms timeTicks

#pragma O0
void delay_ms(uint32_t ms)
{

  if(SysTick_Config(SystemCoreClock / 1000))
  {
    /* Capture error */
    while (1);
  }

  msTicks = 0;
  while (msTicks < ms);         // ���� ���� ������ ��������� �� ������� ��������
  SysTick->CTRL = 0;            // ��������� ������
}
