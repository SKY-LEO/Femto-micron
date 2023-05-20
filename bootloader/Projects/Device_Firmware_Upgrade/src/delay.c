#include "delay.h"


uint16_t  msTicks = 0;		// counts 1ms timeTicks

void delay_ms(uint32_t ms)
{
  SysTick_Config(7200);  // настройка таймера на период 1мс и запуск
 // SysTick_Config(1000);  // настройка таймера на период 1мс и запуск
  msTicks=0;
  while(msTicks < ms);	  // Ждем пока таймер досчитает до нужного значения
  SysTick->CTRL  = 0;     // Отключаем таймер
}