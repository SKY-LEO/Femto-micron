#include "stm32l1xx_tim.h"
#include "main.h"

/////////////////////////////////////////////////////////////////////////////////
void sound_activate(void)
{
  if(!Power.USB_active)
  {
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    if(Power.Display_active == ENABLE)
    {
      if(!Sound_key_pressed)
        Alarm.Tick_beep_count = 0;
      TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
      TIM10->EGR |= 0x0001;     // Устанавливаем бит UG для принудительного сброса счетчика
      TIM3->EGR |= 0x0001;      // Устанавливаем бит UG для принудительного сброса счетчика
      TIM_CCxCmd(TIM10, TIM_Channel_1, TIM_CCx_Enable); // разрешить подачу импульсов
      TIM_Cmd(TIM3, ENABLE);
      Power.Sound_active = ENABLE;
      if((Settings.Vibro == 1) || ((Settings.Vibro > 1) && (Alarm.Alarm_active == ENABLE)))
        GPIO_SetBits(GPIOA, GPIO_Pin_15);       // Активируем вибромотор
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
void sound_deactivate(void)
{

  TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
  TIM_Cmd(TIM3, DISABLE);

  TIM_CCxCmd(TIM10, TIM_Channel_1, TIM_CCx_Disable);    // запретить подачу импульсов

  TIM_SetAutoreload(TIM10, 16);

  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, DISABLE);

  Alarm.Tick_beep_count = 0;
  Power.Sound_active = DISABLE;
  Sound_key_pressed = DISABLE;

  GPIO_ResetBits(GPIOA, GPIO_Pin_15);   // де-активируем вибромотор

}

/////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////
void reset_TIM_prescallers_and_Compare(void)
{
  SystemCoreClockUpdate();

  TIM_PrescalerConfig(TIM10, (uint32_t) (SystemCoreClock / (Settings.Beep_freq * 16)) - 1, TIM_PSCReloadMode_Immediate);        // частота таймера 128 кГц
  TIM_PrescalerConfig(TIM3, (uint32_t) (SystemCoreClock / 800) - 1, TIM_PSCReloadMode_Immediate);       // Делитель (1 тик = 1.25мс)
  TIM_PrescalerConfig(TIM4, (uint32_t) (SystemCoreClock / 100) - 1, TIM_PSCReloadMode_Immediate);       // Делитель (1 тик = 10мс)
}

/////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////
void timer10_Config(void)       // генерация звука
{
  TIM_TimeBaseInitTypeDef TIM_BaseConfig;
  TIM_OCInitTypeDef TIM_OCConfig;
  GPIO_InitTypeDef GPIO_InitStructure;

  TIM_TimeBaseStructInit(&TIM_BaseConfig);
  TIM_OCStructInit(&TIM_OCConfig);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);

  TIM_BaseConfig.TIM_ClockDivision = 0;
  TIM_BaseConfig.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_OCConfig.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCConfig.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCConfig.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_BaseConfig.TIM_Prescaler = (uint32_t) (SystemCoreClock / (Settings.Beep_freq * 16)) - 1;  // частота таймера 16 кГц
  TIM_BaseConfig.TIM_Period = 16;       // ~8 кГц
  TIM_OCConfig.TIM_Pulse = 8;   // Скваженность ~50% 
  // Как я понял - автоматическая перезарядка таймера, если неправ - поправте.

  TIM_DeInit(TIM10);            // Де-инициализируем таймер №10

  TIM_OC1PreloadConfig(TIM10, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM10, ENABLE);

// ===============================================================================================  
  // Динамик
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;    // Ножка
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);        // Загружаем конфигурацию
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_TIM10);
// ===============================================================================================  

  TIM_TimeBaseInit(TIM10, &TIM_BaseConfig);
  TIM_OC1Init(TIM10, &TIM_OCConfig);    // Инициализируем первый выход таймера

  TIM_CCxCmd(TIM10, TIM_Channel_1, TIM_CCx_Enable);     // Запретить выдачу звука
  TIM_Cmd(TIM10, ENABLE);
}

///////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////
void tim3_Config()
{
  TIM_TimeBaseInitTypeDef TIM_BaseConfig;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  TIM_TimeBaseStructInit(&TIM_BaseConfig);

  TIM_BaseConfig.TIM_Prescaler = (uint16_t) (SystemCoreClock / 800) - 1;        // Делитель (1 тик = 1,25мс)
  TIM_BaseConfig.TIM_ClockDivision = 0;
  TIM_BaseConfig.TIM_Period = 1;        // Общее количество тиков
  TIM_BaseConfig.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_ARRPreloadConfig(TIM3, ENABLE);
  TIM_TimeBaseInit(TIM3, &TIM_BaseConfig);

  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

  TIM3->EGR |= 0x0001;          // Устанавливаем бит UG для принудительного сброса счетчика
  TIM_Cmd(TIM3, ENABLE);

}

/////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
void tim4_Config()              // Модуль-А - поиск
{
  TIM_TimeBaseInitTypeDef TIM_BaseConfig;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  TIM_TimeBaseStructInit(&TIM_BaseConfig);

  TIM_BaseConfig.TIM_Prescaler = (uint16_t) (SystemCoreClock / 100) - 1;        // Делитель (1 тик = 10мс)
  TIM_BaseConfig.TIM_ClockDivision = 0;
  TIM_BaseConfig.TIM_Period = 10;       // Общее количество тиков
  TIM_BaseConfig.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_ARRPreloadConfig(TIM4, ENABLE);
  TIM_TimeBaseInit(TIM4, &TIM_BaseConfig);

  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

  TIM4->EGR |= 0x0001;          // Устанавливаем бит UG для принудительного сброса счетчика
  TIM_Cmd(TIM4, ENABLE);

}

/////////////////////////////////////////////////////////////////////////////////
