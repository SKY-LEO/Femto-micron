#include "main.h"



// =======================================================
// Инициализация прерывания датчика 1
void EXTI5_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;

  // Описываем ножку
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);   // Подаем тактирование на порт
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // Режим ножки "вход"
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;      // Без подтяжки
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;     // Номер ножки в порту
  GPIO_Init(GPIOB, &GPIO_InitStructure);        // записиваем конфигурацию

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);        // Подаем тактирование на SYSCFG
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource5); // Подключаем EXTI к ножке

  // Описываем EXTI
  EXTI_InitStructure.EXTI_Line = EXTI_Line5;    // Номер EXTI
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;   // Режим прерывания
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;        // Триггер по нарастающему фронту
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;     // Включаем
  EXTI_Init(&EXTI_InitStructure);       // записиваем конфигурацию

  // Описываем канал прерывания
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;    // канал
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

// =======================================================
// Инициализация прерывания датчика 2
void EXTI10_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;

  // Описываем ножку
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);   // Подаем тактирование на порт
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // Режим ножки "вход"
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;      // Без подтяжки
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;     // Номер ножки в порту
  GPIO_Init(GPIOB, &GPIO_InitStructure);        // записиваем конфигурацию

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);        // Подаем тактирование на SYSCFG
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource10); // Подключаем EXTI к ножке

  // Описываем EXTI
  EXTI_InitStructure.EXTI_Line = EXTI_Line10;    // Номер EXTI
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;   // Режим прерывания
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;        // Триггер по нарастающему фронту
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;     // Включаем
  EXTI_Init(&EXTI_InitStructure);       // записиваем конфигурацию

  // Описываем канал прерывания
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;    // канал
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

// =======================================================
// Инициализация прерывания детектора USB
void EXTI9_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;

  // Описываем ножку
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);   // Подаем тактирование на порт
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // Режим ножки "вход"
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;      // Без подтяжки
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;     // Номер ножки в порту
  GPIO_Init(GPIOA, &GPIO_InitStructure);        // записиваем конфигурацию

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);        // Подаем тактирование на SYSCFG
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource9); // Подключаем EXTI к ножке

  // Описываем EXTI
  EXTI_InitStructure.EXTI_Line = EXTI_Line9;    // Номер EXTI
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;   // Режим прерывания
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;        // Триггер по нарастающему фронту
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;     // Включаем
  EXTI_Init(&EXTI_InitStructure);       // записиваем конфигурацию

  // Описываем канал прерывания
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;    // канал
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

// =======================================================
// Инициализация прерывания по нажатию кнопки 0 (Menu)
void EXTI1_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;

  // Описываем ножку
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);   // Подаем тактирование на порт
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // Режим ножки "вход"
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // Подтяжка к +
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;     // Номер ножки в порту
  GPIO_Init(GPIOB, &GPIO_InitStructure);        // записиваем конфигурацию

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);        // Подаем тактирование на SYSCFG
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource1); // Подключаем EXTI к ножке

  // Описываем EXTI
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;    // Номер EXTI
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;   // Режим прерывания
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;       // Триггер по спадающему фронту
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;     // Включаем
  EXTI_Init(&EXTI_InitStructure);       // записиваем конфигурацию

  // Описываем канал прерывания
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;      // канал
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


// =======================================================
// Инициализация прерывания по модулю-А
/*void EXTI1_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;

  // Описываем ножку
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);   // Подаем тактирование на порт
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // Режим ножки "вход"
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;        // Подтяжка к +
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;     // Номер ножки в порту
  GPIO_Init(GPIOA, &GPIO_InitStructure);        // записиваем конфигурацию

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);        // Подаем тактирование на SYSCFG
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource3); // Подключаем EXTI к ножке

  // Описываем EXTI
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;    // Номер EXTI
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;   // Режим прерывания
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;        // Триггер по спадающему фронту
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;     // Включаем
  EXTI_Init(&EXTI_InitStructure);       // записиваем конфигурацию

  // Описываем канал прерывания
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;      // канал
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}*/

// =======================================================
// Инициализация прерывания по нажатию кнопки 1 (-)
void EXTI2_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;

  // Описываем ножку
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);   // Подаем тактирование на порт
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // Режим ножки "вход"
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // Подтяжка к +
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;     // Номер ножки в порту
  GPIO_Init(GPIOB, &GPIO_InitStructure);        // записиваем конфигурацию

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);        // Подаем тактирование на SYSCFG
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource2); // Подключаем EXTI к ножке

  // Описываем EXTI
  EXTI_InitStructure.EXTI_Line = EXTI_Line2;    // Номер EXTI
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;   // Режим прерывания
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;       // Триггер по спадающему фронту
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;     // Включаем
  EXTI_Init(&EXTI_InitStructure);       // записиваем конфигурацию

  // Описываем канал прерывания
  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;      // канал
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


// =======================================================
// Инициализация прерывания по нажатию кнопки 2 (+)
void EXTI0_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;

  // Описываем ножку
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);   // Подаем тактирование на порт
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // Режим ножки "вход"
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // Подтяжка к +
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;     // Номер ножки в порту
  GPIO_Init(GPIOB, &GPIO_InitStructure);        // записиваем конфигурацию

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);        // Подаем тактирование на SYSCFG
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource0); // Подключаем EXTI к ножке

  // Описываем EXTI
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;    // Номер EXTI
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;   // Режим прерывания
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;       // Триггер по спадающему фронту
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;     // Включаем
  EXTI_Init(&EXTI_InitStructure);       // записиваем конфигурацию

  // Описываем канал прерывания
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;    // канал
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
