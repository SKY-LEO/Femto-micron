#include "delay.h"


volatile uint32_t msTicks = 0;		// counts 1ms timeTicks

void delay_ms(volatile uint32_t ms)
{
  //SysTick_Config(7200);  // ��������� ������� �� ������ 1�� � ������
  //SysTick_Config(1000);  // ��������� ������� �� ������ 1�� � ������
	SysTick_Config(SystemCoreClock / 1000);  // ��������� ������� �� ������ 1�� � ������
  msTicks=0;
  while(msTicks < ms);	  // ���� ���� ������ ��������� �� ������� ��������
  SysTick->CTRL = 0;     // ��������� ������
}
