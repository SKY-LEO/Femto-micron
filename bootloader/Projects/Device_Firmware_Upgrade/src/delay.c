#include "delay.h"


uint16_t  msTicks = 0;		// counts 1ms timeTicks

void delay_ms(uint32_t ms)
{
  SysTick_Config(7200);  // ��������� ������� �� ������ 1�� � ������
 // SysTick_Config(1000);  // ��������� ������� �� ������ 1�� � ������
  msTicks=0;
  while(msTicks < ms);	  // ���� ���� ������ ��������� �� ������� ��������
  SysTick->CTRL  = 0;     // ��������� ������
}