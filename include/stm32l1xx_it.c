#include "stm32l1xx_it.h"
#include "main.h"

//extern __IO uint32_t CaptureNumber, PeriodValue;
//uint32_t IC1ReadValue1 = 0, IC1ReadValue2 = 0;

// ===============================================================================================
void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  while (1)
  {
  }
}

/**
* @brief  This function handles Memory Manage exception.
* @param  None
* @retval None
*/
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
* @brief  This function handles Bus Fault exception.
* @param  None
* @retval None
*/
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
* @brief  This function handles Usage Fault exception.
* @param  None
* @retval None
*/
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
* @brief  This function handles SVCall exception.
* @param  None
* @retval None
*/
void SVC_Handler(void)
{
}

/**
* @brief  This function handles Debug Monitor exception.
* @param  None
* @retval None
*/
void DebugMon_Handler(void)
{
}

/**
* @brief  This function handles PendSVC exception.
* @param  None
* @retval None
*/
void PendSV_Handler(void)
{
}

/**
* @brief  This function handles SysTick Handler.
* @param  None
* @retval None
*/
void SysTick_Handler(void)
{
  extern uint32_t msTicks;
  msTicks++;                    // инкремент счётчика времени
}

/******************************************************************************/
/*                 STM32L1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l1xx_xx.s).                                            */
/******************************************************************************/

/**
* @brief  This function handles PPP interrupt request.
* @param  None
* @retval None
*/
/*void PPP_IRQHandler(void)
{
}*/

/**
* @}
*/

// =======================================================
// Прерывание по нажатию кнопки 0
void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
  {
    if(!poweroff_state)
    {
      if(Alarm.Alarm_active && !Alarm.User_cancel)
      {
        Alarm.User_cancel = ENABLE;
        sound_deactivate();
      } else
      {
        if(Power.Display_active)
        {
          key |= 0x1;           // Кнопка Меnu
        }
      }
      Sound_key_pressed = ENABLE;
      Alarm.Tick_beep_count = 0;
      check_wakeup_keys();
    }
    EXTI_ClearITPendingBit(EXTI_Line1);
  }
}

// =======================================================
// Прерывание по нажатию кнопки 1
void EXTI2_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line2) != RESET)
  {
    if(!poweroff_state)
    {
      if(Power.Display_active)
      {
        key |= 0x4;             // Кнопка -
      }
      Sound_key_pressed = ENABLE;
      Alarm.Tick_beep_count = 0;
      check_wakeup_keys();
    }
    EXTI_ClearITPendingBit(EXTI_Line2);
  }
}

// =======================================================
// Прерывание по нажатию кнопки 2
void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line0);
    if(!poweroff_state)
    {
      if(Power.Display_active)
      {
        key |= 0x2;             // Кнопка +
      }
      Sound_key_pressed = ENABLE;
      Alarm.Tick_beep_count = 0;
      check_wakeup_keys();
    }
  }
}

// =======================================================
// Прерывание по импульсу от датчика 1 и USB
void EXTI9_5_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line5) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line5);
    if(!poweroff_state)
    {
      if(Settings.AB_mode < 2)
      {
        Detector_massive[Detector_massive_pointer]++;   // Добавляем пойманную частицу к счетчику  
        ram_Doze_massive[0]++;  // Увеличение суточного массива дозы
      } else
      {
        Detector_AB_massive[0]++;
      }

      if(Settings.Sound && !(Alarm.Alarm_active && !Alarm.User_cancel))
      {
        if(Power.Display_active)
        {
          if(Settings.AMODUL_mode == 0)
            sound_activate();
        }
      }
    }
  }

  if(EXTI_GetITStatus(EXTI_Line9) != RESET)     // Подключено USB
  {
    EXTI_ClearITPendingBit(EXTI_Line9);
    if(!poweroff_state)
    {
      sound_activate();
      Power.sleep_time = Settings.Sleep_time;
    }
  }

}

// =======================================================
// Прерывание по импульсу от датчика 2
void EXTI15_10_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line10) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line10);
    if(!poweroff_state)
    {
      if(Settings.AB_mode < 2)
      {
        Detector_massive[Detector_massive_pointer]++;   // Добавляем пойманную частицу к счетчику  
        ram_Doze_massive[0]++;  // Увеличение суточного массива дозы
      } else
      {
        Detector_AB_massive[0]++;
      }

      if(Settings.Sound && !(Alarm.Alarm_active && !Alarm.User_cancel))
      {
        if(Power.Display_active)
        {
          if(Settings.AMODUL_mode == 0)
            sound_activate();
        }
      }
    }
  }

}


// ========================================================
// генерация звука на динамик
void TIM3_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    if(!poweroff_state)
    {
      if(Alarm.Alarm_active && !Alarm.User_cancel)
      {
        Alarm.Alarm_beep_count++;
        if(Alarm.Alarm_beep_count == 100)
          TIM_SetAutoreload(TIM10, 32);
        if(Alarm.Alarm_beep_count == 200)
        {
          TIM_SetAutoreload(TIM10, 16);
          Alarm.Alarm_beep_count = 0;
        }
      }

      if((Alarm.Alarm_active && Alarm.User_cancel) || !Alarm.Alarm_active)
      {
        if(Power.Sound_active == ENABLE)
        {
          if(Sound_key_pressed) // нажатие кнопки
          {
            if(Alarm.Tick_beep_count > 80)
            {
              Alarm.Tick_beep_count = 0;
              sound_deactivate();
            } else
              Alarm.Tick_beep_count++;


          } else if(((Alarm.Tick_beep_count > 6) && (Settings.AMODUL_mode == 0)) || ((Alarm.Tick_beep_count > 1) && (Settings.AMODUL_mode != 0)))       // тик датчика или тик модуля
          {
            Alarm.Tick_beep_count = 0;
            sound_deactivate();
          } else
            Alarm.Tick_beep_count++;
        } else
          sound_deactivate();
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Модуль-А
// =======================================================
// Прерывание по нажатию кнопки 0
/*void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
  {
    if(!poweroff_state)
    {
      if(Settings.AMODUL_mode == 0)     // Если модуль-А выключен, активируем его
        plus_amodul_engage(0x00);

      Data.AMODULE_fon[0]++;
      Data.AMODULE_find[0]++;
      if(Isotop_counts >= Settings.Isotop_counts)
      {
        sound_activate();
        Isotop_counts = 0;
      } else
      {
        Isotop_counts++;
      }
    }
    EXTI_ClearITPendingBit(EXTI_Line1);
  }
}
*/
////////////////////////
void TIM4_IRQHandler(void)
{
  uint32_t i = 0;
  if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

    if(Settings.AMODUL_mode != 0)
    {

      Data.AMODULE_find_summ = Data.AMODULE_find[0];
      for (i = 9; i > 0; i--)
      {
        Data.AMODULE_find_summ += Data.AMODULE_find[i];
        Data.AMODULE_find[i] = Data.AMODULE_find[i - 1];
      }
      Data.AMODULE_find[0] = 0;

      if(Settings.AMODUL_unit == 2)
        DataUpdate.Need_display_update = ENABLE;

      if(Settings.AMODUL_Alarm_level > 0)
        if(Data.AMODULE_find_summ > Settings.AMODUL_Alarm_level_raw)
        {
          if(Alarm.Alarm_active == DISABLE)
            Alarm.User_cancel = DISABLE;

          Alarm.Alarm_active = ENABLE;
          sound_activate();

        } else
        {
          if(Alarm.Alarm_active == ENABLE)
          {
            sound_deactivate();
            Power.Sound_active = DISABLE;
            Alarm.Alarm_active = DISABLE;
            Alarm.User_cancel = DISABLE;
            Alarm.Alarm_beep_count = 0;
          }
        }
    }
  }
}




////////////////////////////////////////
// Секундный тик
////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RTC_Alarm_IRQHandler(void)
{                               // Тик каждые 4 секунды
  int i;

  EXTI_ClearITPendingBit(EXTI_Line17);

  // Модуль-А
  if(RTC_GetITStatus(RTC_IT_ALRB) != RESET)
  {
    RTC_ClearITPendingBit(RTC_IT_ALRB);

    if(!poweroff_state)
    {
      Set_next_B_alarm_wakeup();        // установить таймер просыпания на +1 секунду

      if(Settings.AMODUL_mode != 0)     // Если модуль-А активирован, обрабатываем его массив
      {
        for (i = 59; i > 0; i--)
        {
          Data.AMODULE_fon[i] = Data.AMODULE_fon[i - 1];
        }

        Data.AMODULE_fon[0] = 0;

        if((Data.AMODULE_fon[0] == 0) && (Data.AMODULE_fon[1] == 0) && (Data.AMODULE_fon[2] == 0))      // Если от модуля-А не поступает данных три цыкла, деактивируем его.
        {

          Settings.AMODUL_mode = 0;
          Data.modul_menu_select = 0;
          Data.menu_select = 0;
          Settings.AMODUL_menu = 0;
          Data.enter_menu_item = DISABLE;

          RTC_AlarmCmd(RTC_Alarm_B, DISABLE);
          RTC_ITConfig(RTC_IT_ALRB, DISABLE);
          RTC_ClearFlag(RTC_FLAG_ALRBF);

          TIM_ITConfig(TIM4, TIM_IT_Update, DISABLE);
          TIM_Cmd(TIM4, DISABLE);
          RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, DISABLE);


        }
        DataUpdate.Need_display_update = ENABLE;
      }

      Power.sleep_time = Settings.Sleep_time;
    }

  }
  // Основной счет времени
  if(RTC_GetITStatus(RTC_IT_ALRA) != RESET)
  {
    RTC_ClearITPendingBit(RTC_IT_ALRA);
    if(!poweroff_state)
    {
      Set_next_alarm_wakeup();  // установить таймер просыпания на +4 секунды

      if(Settings.AMODUL_mode == 0)
        DataUpdate.Need_display_update = ENABLE;

      // Калибровка 4 интервала счета
      if(Settings.Cal_mode == 1)
      {
        if(Cal_count < 20)
        {
          if(Settings.Second_count > Cal_count_time)
          {
            Cal_count_time += 4;
            Data.Cal_count_mass[Cal_count] += Detector_massive[Detector_massive_pointer];
          } else
          {
            Cal_count_time = 0;
            Cal_count++;
          }
        }
      }

      if(Power.USB_active)
      {
        Data.USB_not_active++;  // Счетчик неактивности USB
        if(Settings.AB_mode < 2)
          Data.madorc_impulse += Detector_massive[Detector_massive_pointer];    // Счетчик импульсов для передачи по USB
      }
      // Счетчик времени для обновления напряжения АКБ (каждые 4 минуты)
      if(DataUpdate.Batt_update_time_counter > 75)
      {
        DataUpdate.Need_batt_voltage_update = ENABLE;
        DataUpdate.Batt_update_time_counter = 0;
      } else
        DataUpdate.Batt_update_time_counter++;

      if((DataUpdate.Batt_update_time_counter > 2) && (Power.Display_active == ENABLE)) // Если дисплей активен, обновлять каждые 12 секунд
      {
        DataUpdate.Batt_update_time_counter = 0;
        DataUpdate.Need_batt_voltage_update = ENABLE;
      }
      // Счетчик времени для обновления счетчика импульсов накачки
      if(DataUpdate.pump_counter_update_time > 14)
      {
        if(!Power.USB_active)
          Data.madorc_impulse = 0;

        PumpData.pump_counter_avg_impulse_by_1sec[1] = PumpData.pump_counter_avg_impulse_by_1sec[0];
        PumpData.pump_counter_avg_impulse_by_1sec[0] = 0;
        DataUpdate.pump_counter_update_time = 0;

      } else
        DataUpdate.pump_counter_update_time++;

      // Счетчик дней
      if(DataUpdate.days_sec_count >= 24600)    // каждые 24 часа минут
      {
        DataUpdate.days_sec_count = 0;
        Data.working_days++;
				if(flash_read_massive(doze_length_day, dose_select) > 0)        // День
        {
					Data.Doze_all_time += (Data.Doze_day_count * (Settings.Second_count >> 2)) / 900; 
        }

      } else
        DataUpdate.days_sec_count++;
      // Сдвиг массива дозы
      if(DataUpdate.doze_sec_count >= 150)      // каждые 10 минут (150)
      {
        if(bat_cal_running > 0) // Запись калибровки АКБ
          cal_write();

        if(DataUpdate.Need_erase_flash == ENABLE)
        {
          full_erase_flash();
          DataUpdate.Need_erase_flash = DISABLE;
        }
        DataUpdate.Need_update_mainscreen_counters = ENABLE;

        // -----------------------------------------------------
        DataUpdate.doze_count++;
        if(DataUpdate.doze_count >= doze_length)        // Запись страницы во Flash
          //if(DataUpdate.doze_count>1) // Запись страницы во Flash
        {
          DataUpdate.doze_count = 0;
          flash_write_page(DataUpdate.current_flash_page);
          DataUpdate.current_flash_page++;
          if(DataUpdate.current_flash_page > (FLASH_MAX_PAGE))  // если за границами диапазона
            DataUpdate.current_flash_page = 0;
        }
        // -----------------------------------------------------

        for (i = doze_length; i > 0; i--)
        {
          ram_Doze_massive[i] = ram_Doze_massive[i - 1];        // сдвиг массива дозы
          ram_max_fon_massive[i] = ram_max_fon_massive[i - 1];  // сдвиг массива максимального фона
        }
        ram_Doze_massive[0] = 0;
        ram_max_fon_massive[0] = 0;
        DataUpdate.doze_sec_count = 1;  //// !!!!! 0

      } else
        DataUpdate.doze_sec_count++;
      ////////////////////////////////////////////////////    

      if(Settings.AB_mode == 2)
      {
        Data.AB_fon = calc_ab();

        for (i = 14; i > 0; i--)
        {
          Detector_AB_massive[i] = Detector_AB_massive[i - 1];
        }
        Detector_AB_massive[0] = 0;
      }
      ////////////////////////////////////////////////////    
      // Ускорение
      if(Settings.AB_mode < 2)
        if(Detector_massive[Detector_massive_pointer] >= 10 && Settings.Speedup == 1)
        {
          Data.auto_speedup_factor = 1;
          if(Detector_massive[Detector_massive_pointer] > 300)  // деление на 9 при фоне более 10 000
          {
            if(Data.auto_speedup_factor != 99)
              Data.auto_speedup_factor = 99;
          } else
          {
            if(Detector_massive[Detector_massive_pointer] > 199)        // деление на 9 при фоне более 10 000
            {
              if(Data.auto_speedup_factor != 30)
                Data.auto_speedup_factor = 30;
            } else
            {
              if(Detector_massive[Detector_massive_pointer] > 99)       // деление на 5 при фоне более 5 000
              {
                if(Data.auto_speedup_factor != 10)
                  Data.auto_speedup_factor = 10;
              } else
              {
                if(Detector_massive[Detector_massive_pointer] > 19)     // деление на 3 при фоне более 1 000
                {
                  if(Data.auto_speedup_factor != 4)
                    Data.auto_speedup_factor = 4;
                } else
                {               // деление на 2 при фоне более 500
                  if(Data.auto_speedup_factor != 2)
                    Data.auto_speedup_factor = 2;
                }
              }
            }
          }

          if(Data.auto_speedup_factor > (Settings.Second_count >> 3))
            Data.auto_speedup_factor = (Settings.Second_count >> 3);    // пересчет фона, если активированно ускорение
          if(Data.auto_speedup_factor != 1)
            recalculate_fon();  // пересчет фона, если активированно ускорение

        } else
        {                       // если ускорение не требуется
          if(Data.auto_speedup_factor != 1)
          {
            Data.auto_speedup_factor = 1;
            recalculate_fon();
          } else
          {
            if(Settings.AB_mode < 2)
              Data.fon_level += Detector_massive[Detector_massive_pointer];
          }
        }

      if(Settings.AB_mode < 2)
      {
        Detector_massive_pointer++;
        if(Detector_massive_pointer >= (Settings.Second_count >> 2))
        {
          if(Data.auto_speedup_factor == 1)
            Data.fon_level -= Detector_massive[0];
          Detector_massive[0] = 0;
          Detector_massive_pointer = 0;
        } else
        {
          if(Data.auto_speedup_factor == 1)
            Data.fon_level -= Detector_massive[Detector_massive_pointer];
          Detector_massive[Detector_massive_pointer] = 0;
        }
        if(Data.fon_level > ram_max_fon_massive[0])
          ram_max_fon_massive[0] = Data.fon_level;      // заполнение массива максимального фона
      }
      DataUpdate.Need_fon_update = ENABLE;
      ////////////////////////////////////////////////////

      if(Power.sleep_time > 4)
      {
        Power.sleep_time -= 4;
      } else
      {
        Power.sleep_time = 0;
      }
    }
/*    if(Pump_on_alarm == ENABLE)
    {
      if(Settings.Pump_aggressive == ENABLE)
      {
        Pump_now(ENABLE);
      } else
      {
        if(Pump_on_alarm_count > 1)
        {
          Pump_now(ENABLE);     // оптимизируем накачку вынося из вейкап таймера
          Pump_on_alarm_count = 0;
        } else
        {
          Pump_on_alarm_count++;
        }
      }
    }
*/
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/*******************************************************************************
* Function Name  : USB_IRQHandler
* Description    : This function handles USB Low Priority interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_LP_IRQHandler(void)
{
  USB_Istr();
}

/*******************************************************************************
* Function Name  : USB_FS_WKUP_IRQHandler
* Description    : This function handles USB WakeUp interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void USB_FS_WKUP_IRQHandler(void)
{
  EXTI_ClearITPendingBit(EXTI_Line18);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
