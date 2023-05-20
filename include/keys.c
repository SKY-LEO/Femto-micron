#include <stdio.h>
#include <string.h>
#include "main.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// +
void plus(uint32_t * param)
{
  if(Settings.AMODUL_mode > 0)
  {
    if(*param > modul_max_struct_index)
      return;
    if(*param == 0)
      return;

    //���� �������� ��������� ����������� ���������� ��������, �� ��������� �� �������
    if(*Modul_Menu_list[*param - 1].Parameter_value >= Modul_Menu_list[*param - 1].Max_limit)
    {
      *Modul_Menu_list[*param - 1].Parameter_value = Modul_Menu_list[*param - 1].Min_limit;
    } else
    {
      *Modul_Menu_list[*param - 1].Parameter_value = *Modul_Menu_list[*param - 1].Parameter_value + Modul_Menu_list[*param - 1].Plus_value;     // +
    }
  } else
  {
    if(*param > max_struct_index)
      return;
    if(*param == 0)
      return;

    //���� �������� ��������� ����������� ���������� ��������, �� ��������� �� �������
    if(*Menu_list[*param - 1].Parameter_value >= Menu_list[*param - 1].Max_limit)
    {
      *Menu_list[*param - 1].Parameter_value = Menu_list[*param - 1].Min_limit;
    } else
    {
      *Menu_list[*param - 1].Parameter_value = *Menu_list[*param - 1].Parameter_value + Menu_list[*param - 1].Plus_value;       //+
    }
  }
}

void minus(uint32_t * param)    // -
{
  if(Settings.AMODUL_mode > 0)
  {
    if(*param > modul_max_struct_index)
      return;
    if(*param == 0)
      return;

    //���� �������� ��������� ���������� ���������� ��������, �� ��������� �� ��������
    if(*Modul_Menu_list[*param - 1].Parameter_value <= Modul_Menu_list[*param - 1].Min_limit)
    {
      *Modul_Menu_list[*param - 1].Parameter_value = Modul_Menu_list[*param - 1].Max_limit;
    } else
    {
      *Modul_Menu_list[*param - 1].Parameter_value = *Modul_Menu_list[*param - 1].Parameter_value - Modul_Menu_list[*param - 1].Minus_value;    // -
    }
  } else
  {
    if(*param > max_struct_index)
      return;
    if(*param == 0)
      return;

    //���� �������� ��������� ���������� ���������� ��������, �� ��������� �� ��������
    if(*Menu_list[*param - 1].Parameter_value <= Menu_list[*param - 1].Min_limit)
    {
      *Menu_list[*param - 1].Parameter_value = Menu_list[*param - 1].Max_limit;
    } else
    {
      *Menu_list[*param - 1].Parameter_value = *Menu_list[*param - 1].Parameter_value - Menu_list[*param - 1].Minus_value;      // -
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���������� ���
void plus_batcal(uint32_t * param)
{

  bat_cal_running = 1;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� ������ �������
void plus_alarm(uint32_t * param)       // +
{
  if(*param > max_struct_index)
    return;
  if(*param == 0)
    return;

  if((*Menu_list[*param - 1].Parameter_value >= 1000) && (*Menu_list[*param - 1].Parameter_value < 9999))
    *Menu_list[*param - 1].Parameter_value += 500;
  if((*Menu_list[*param - 1].Parameter_value >= 100) && (*Menu_list[*param - 1].Parameter_value < 1000))
    *Menu_list[*param - 1].Parameter_value += 100;
  if(*Menu_list[*param - 1].Parameter_value < 100)
    *Menu_list[*param - 1].Parameter_value += 25;
  if(*Menu_list[*param - 1].Parameter_value > 9999)
    *Menu_list[*param - 1].Parameter_value = 0;

}

void minus_alarm(uint32_t * param)      // -
{
  if(*param > max_struct_index)
    return;
  if(*param == 0)
    return;

  if(*Menu_list[*param - 1].Parameter_value <= 100)
    *Menu_list[*param - 1].Parameter_value -= 25;
  if((*Menu_list[*param - 1].Parameter_value > 100) && (*Menu_list[*param - 1].Parameter_value <= 1000))
    *Menu_list[*param - 1].Parameter_value -= 100;
  if((*Menu_list[*param - 1].Parameter_value > 1000) && (*Menu_list[*param - 1].Parameter_value < 9999))
    *Menu_list[*param - 1].Parameter_value -= 500;
  if(*Menu_list[*param - 1].Parameter_value > 9999)
    *Menu_list[*param - 1].Parameter_value = 9500;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� ������ ���
void plus_sleep(uint32_t * param)       //+
{
  if(*param > max_struct_index)
    return;
  if(*param == 0)
    return;

  //���� �������� ��������� ����������� ���������� ��������, �� ��������� �� �������
  if(*Menu_list[*param - 1].Parameter_value >= Menu_list[*param - 1].Max_limit)
  {
    *Menu_list[*param - 1].Parameter_value = Menu_list[*param - 1].Min_limit;
  } else
  {
    *Menu_list[*param - 1].Parameter_value = *Menu_list[*param - 1].Parameter_value * 2;        //*2
  }
}

void minus_sleep(uint32_t * param)      //-
{
  if(*param > max_struct_index)
    return;
  if(*param == 0)
    return;

  if(*Menu_list[*param - 1].Parameter_value <= Menu_list[*param - 1].Min_limit)
  {
    *Menu_list[*param - 1].Parameter_value = Menu_list[*param - 1].Max_limit;
  } else
  {
    *Menu_list[*param - 1].Parameter_value = *Menu_list[*param - 1].Parameter_value / 2;        // /2
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���-����
void plus_on(uint32_t * param)  // ���
{
  if(*param > max_struct_index)
    return;
  if(*param == 0)
    return;

  *Menu_list[*param - 1].Parameter_value = 1;
}

void minus_off(uint32_t * param)        // ����
{
  if(*param > max_struct_index)
    return;
  if(*param == 0)
    return;

  *Menu_list[*param - 1].Parameter_value = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����� ������ � ����
void plus_rad_reset(uint32_t * param)
{
  int i;

  for (i = Detector_massive_pointer_max; i > 0; i--)
  {
    Detector_massive[i] = 0;
  }
  Detector_massive_pointer = 1;

  recalculate_fon();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����� �����-����
void ab_meas_on()
{
  uint32_t i;
  Settings.AB_mode = 2;
  for (i = 0; i < 15; i++)
    Detector_AB_massive[i] = 0; // ������� ��������� �� ������
  Data.AB_fon = 0;

}

void ab_meas_off()
{
  Settings.AB_mode = 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void plus_ab_engage(uint32_t * param)
{
  uint32_t i;

  Settings.AB_mode = 1;
  for (i = 0; i < 15; i++)
    Detector_AB_massive[i] = 0; // ������� ��������� �� ������
  Data.AB_fon = 0;
  Data.menu_select = 0;
  Data.enter_menu_item = DISABLE;
  Data.screen = 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void plus_amodul_engage(uint32_t * param)
{
  int i;

  Settings.AMODUL_Alarm_level_raw = (Settings.AMODUL_Alarm_level * Settings.ACAL_count) / 100;
  Settings.AMODUL_mode = 1;

  // ������ ��������� ������
  tim4_Config();

  for (i = 99; i > 0; i--)
  {
    Data.AMODULE_fon[i] = 0;
  }
  Data.AMODULE_fon[0] = 0;

  Set_next_B_alarm_wakeup();
  RTC_ITConfig(RTC_IT_ALRB, ENABLE);
  RTC_AlarmCmd(RTC_Alarm_B, ENABLE);
  RTC_ClearFlag(RTC_FLAG_ALRBF);

  Data.menu_select = 0;
  Data.modul_menu_select = 0;
  Data.enter_menu_item = DISABLE;
  Data.screen = 1;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����� ������� ����
void plus_doze_reset(uint32_t * param)  // ����� ����
{
  int i;

  for (i = doze_length; i > 0; i--)
  {
    ram_Doze_massive[i] = 0;
    ram_max_fon_massive[i] = 0;
    Data.Doze_hour_count += ram_Doze_massive[i];
    Data.Doze_day_count += ram_Doze_massive[i];
    Data.Doze_week_count += ram_Doze_massive[i];
  }
  Data.Doze_hour_count = 0;
  Data.Doze_day_count = 0;
  Data.Doze_week_count = 0;
  DataUpdate.doze_sec_count = 0;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� ���������
void minus_one_ref(uint32_t * param)
{
  if(*param > max_struct_index)
    return;
  if(*param == 0)
    return;


  if(Settings.VRef <= Menu_list[*param - 1].Min_limit)
  {
    Settings.VRef = Menu_list[*param - 1].Max_limit;
  } else
  {
    Settings.VRef--;;           // -1
  }

  DataUpdate.Need_batt_voltage_update = ENABLE;
  adc_check_event();
}

void plus_one_ref(uint32_t * param)
{
  if(*param > max_struct_index)
    return;
  if(*param == 0)
    return;

  if(Settings.VRef >= Menu_list[*param - 1].Max_limit)
  {
    Settings.VRef = Menu_list[*param - 1].Min_limit;
  } else
  {
    Settings.VRef++;            //+1
  }

  DataUpdate.Need_batt_voltage_update = ENABLE;
  adc_check_event();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������������ � ����������
void plus_reboot(uint32_t * param)      // ������������
{
  if(Power.USB_active)
    USB_off();
  LcdClear_massive();
  sprintf(lcd_buf, LANG_REBOOTPR);      // ����� � ����� �������� ��������
  LcdString(1, 5);              // // ������� ������� ������� ���������� ������
  sprintf(lcd_buf, LANG_DONTOTO1);      // ����� � ����� �������� ��������
  LcdString(1, 7);              // // ������� ������� ������� ���������� ������
  sprintf(lcd_buf, LANG_DONTOTO2);      // ����� � ����� �������� ��������
  LcdString(1, 8);              // // ������� ������� ������� ���������� ������

  LcdUpdate();                  // ���������� ������ �� ��������������� �����-������ �� �������
  delay_ms(3000);
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
  IWDG_SetPrescaler(IWDG_Prescaler_4);
  IWDG_SetReload(2);
  IWDG_ReloadCounter();
  IWDG_Enable();
  while (1);
}

void minus_poweroff(uint32_t * param)   // ����������
{
  NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;

  if(Power.USB_active)
    USB_off();
  LcdClear_massive();
  sprintf(lcd_buf, LANG_POWEROFF);      // ����� � ����� �������� ��������
  LcdString(1, 5);              // // ������� ������� ������� ���������� ������
  sprintf(lcd_buf, LANG_DONTOTO1);      // ����� � ����� �������� ��������
  LcdString(1, 7);              // // ������� ������� ������� ���������� ������
  sprintf(lcd_buf, LANG_DONTOTO2);      // ����� � ����� �������� ��������
  LcdString(1, 8);              // // ������� ������� ������� ���������� ������

  LcdUpdate();                  // ���������� ������ �� ��������������� �����-������ �� �������

  RTC_WriteBackupRegister(RTC_BKP_DR0, 0x0);
  delay_ms(3000);

  sleep_mode(ENABLE);
  poweroff_state = ENABLE;
//  Pump_now(DISABLE);
// =======================================================
// ��-������������� ���������� ������� 1

  EXTI_InitStructure.EXTI_Line = EXTI_Line8;    // ����� EXTI
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;   // ����� ����������
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;        // ������� �� ������������ ������
  EXTI_InitStructure.EXTI_LineCmd = DISABLE;    // ��������
  EXTI_Init(&EXTI_InitStructure);       // ���������� ������������

  // ��������� ����� ����������
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;    // �����
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
  NVIC_Init(&NVIC_InitStructure);
// =======================================================
  NVIC_InitStructure.NVIC_IRQChannel = COMP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
  NVIC_Init(&NVIC_InitStructure);


/////////////////////////////////////////////////////
  /* Enable the alarm  A */
  RTC_AlarmCmd(RTC_Alarm_A, DISABLE);

  /* Clear the RTC Alarm Flag */
  RTC_ClearFlag(RTC_FLAG_ALRAF);

  /* Clear the EXTI Line 17 Pending bit (Connected internally to RTC Alarm) */
  EXTI_ClearITPendingBit(EXTI_Line17);

  /* RTC Alarm A Interrupt Configuration */
  /* EXTI configuration ******************************************************** */
  EXTI_ClearITPendingBit(EXTI_Line17);
  EXTI_InitStructure.EXTI_Line = EXTI_Line17;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable the RTC Alarm Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
  NVIC_Init(&NVIC_InitStructure);

  // EXTI configuration
  EXTI_ClearITPendingBit(EXTI_Line20);
  EXTI_InitStructure.EXTI_Line = EXTI_Line20;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  EXTI_Init(&EXTI_InitStructure);

  // Enable the RTC Wakeup Interrupt
  NVIC_InitStructure.NVIC_IRQChannel = RTC_WKUP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
  NVIC_Init(&NVIC_InitStructure);

  RTC_AlarmCmd(RTC_Alarm_A, DISABLE);
  RTC_ClearFlag(RTC_FLAG_ALRAF);

  while (RTC_WakeUpCmd(DISABLE) != SUCCESS);
  RTC_ITConfig(RTC_IT_WUT, DISABLE);
  RTC_ITConfig(RTC_IT_ALRA, DISABLE);
  PWR_RTCAccessCmd(DISABLE);
  RCC_RTCCLKCmd(DISABLE);

  RCC_LSEConfig(RCC_LSE_OFF);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, DISABLE);
/////////////////////////////////////////////////////

  while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6))
  {
    PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);       // ��������� � ���
  }

  sleep_mode(DISABLE);

  LcdClear_massive();
  sprintf(lcd_buf, LANG_REBOOTPR);      // ����� � ����� �������� ��������
  LcdString(1, 5);              // // ������� ������� ������� ���������� ������
  sprintf(lcd_buf, LANG_DONTOTO1);      // ����� � ����� �������� ��������
  LcdString(1, 7);              // // ������� ������� ������� ���������� ������
  sprintf(lcd_buf, LANG_DONTOTO2);      // ����� � ����� �������� ��������
  LcdString(1, 8);              // // ������� ������� ������� ���������� ������

  LcdUpdate();                  // ���������� ������ �� ��������������� �����-������ �� �������


  delay_ms(6000);
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
  IWDG_SetPrescaler(IWDG_Prescaler_4);
  IWDG_SetReload(2);
  IWDG_ReloadCounter();
  IWDG_Enable();
  while (1);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� USB
void usb_activate(uint32_t * param)     // ��������� USB
{
  Data.USB_not_active = 0;
  if(!Power.USB_active)
  {
    USB_on();
//      LcdClear_massive();
//      sprintf (lcd_buf, LANG_USBON); // ����� � ����� �������� ��������
//      LcdString(1,5); // // ������� ������� ������� ���������� ������
//  LcdUpdate(); // ���������� ������ �� ��������������� �����-������ �� �������
//  delay_ms(1000);
  }
}

void usb_deactivate(uint32_t * param)   // ���������� USB
{
  if(Power.USB_active)
  {
    USB_off();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//              LcdClear_massive();
//              sprintf (lcd_buf, LANG_USBOFF); // ����� � ����� �������� ��������
//              LcdString(1,5); // // ������� ������� ������� ���������� ������
//              LcdUpdate(); // ���������� ������ �� ��������������� �����-������ �� �������
//              delay_ms(1000);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� ������
void keys_proccessing(void)
{
  extern uint16_t key;
  extern SettingsDef Settings;
//  int i;

  /////////////////////////////////
  if(key & 0x2)                 // ������ +
  {
    while (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3));
    while (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4));
    while (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6));
    delay_ms(10);
    DataUpdate.Need_display_update = ENABLE;

    if((Settings.AMODUL_mode > 0) && (Settings.AMODUL_menu == 0))
    {
      if(Settings.AMODUL_unit < 2)
      {
      } else
      {
        Data.AMODULE_page++;
        if(Data.AMODULE_page >= 5)
          Data.AMODULE_page = 0;
      }
    }

    if(Settings.AB_mode > 0)
    {
      ab_meas_on();
      key = 0;
    } else
    {

      if((Data.screen == 2 && Data.enter_menu_item == DISABLE) && (Settings.AMODUL_menu == 0))
        Data.menu_select--;
      if((Settings.AMODUL_menu > 0) && (Data.enter_menu_item == DISABLE))
        Data.modul_menu_select--;
      if(Data.screen == 1)
        Data.main_menu_stat++;
      if(Data.screen == 3)
      {
        if(Data.stat_screen_number == 1)
        {
          Data.stat_screen_number = 0;
        } else
        {
          Data.stat_screen_number++;
        }
      }
      if(hidden_menu)
      {
        if(Data.menu_select > max_struct_index)
          Data.menu_select = max_struct_index;
      } else
      {
        if(Data.menu_select > max_public_string_count)
          Data.menu_select = max_public_string_count;
      }
      if(Data.modul_menu_select > modul_max_struct_index)
        Data.modul_menu_select = modul_max_struct_index;


      key = 0;

      ///////////
      if((Data.enter_menu_item == ENABLE) && (Settings.AMODUL_menu == 0))
      {

        if(Data.menu_select > max_struct_index)
          return;
        if(Data.menu_select == 0)
          return;

        if(Menu_list[Data.menu_select - 1].Plus_reaction != 0x00)       // ���� ����� ������� ����������, �� ��������� ��.
        {
          (*Menu_list[Data.menu_select - 1].Plus_reaction) (&Data.menu_select); // ������  ������� - �������� ���� ��� :)
        }
      }
      ///////////
      if((Settings.AMODUL_menu > 0) && (Data.enter_menu_item == ENABLE))
      {

        if(Data.modul_menu_select > modul_max_struct_index)
          return;
        if(Data.modul_menu_select == 0)
          return;

        if(Modul_Menu_list[Data.modul_menu_select - 1].Plus_reaction != 0x00)   // ���� ����� ������� ����������, �� ��������� ��.
        {
          (*Modul_Menu_list[Data.modul_menu_select - 1].Plus_reaction) (&Data.modul_menu_select);       // ������  ������� - �������� ���� ��� :)
        }
      }
    }
  }
  /////////////////////////////////
  if(key & 0x4)                 // ������ -
  {
    while (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3));
    while (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4));
    while (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6));
    delay_ms(10);
    DataUpdate.Need_display_update = ENABLE;

    if((Settings.AMODUL_mode > 0) && (Settings.AMODUL_menu == 0))
    {
      Settings.AMODUL_unit++;
/*      if(Settings.AMODUL_unit == 3)
      {
        for (i = 0; i < 100; i++)
          Data.AMODULE_len[i] = 0;
      }
*/
      if(Settings.AMODUL_unit > 2)
        Settings.AMODUL_unit = 0;
    }

    if(Settings.AB_mode > 0)
    {
      ab_meas_off();
      key = 0;
    } else
    {
      if((Data.screen == 2 && Data.enter_menu_item == DISABLE) && (Settings.AMODUL_menu == 0))
        Data.menu_select++;
      if((Settings.AMODUL_menu != 0) && (Data.enter_menu_item == DISABLE))
        Data.modul_menu_select++;
      if(Data.screen == 1)
        Data.main_menu_stat--;
      if(Data.screen == 3)
      {
        if(Data.stat_screen_number == 0)
        {

          Data.stat_screen_number = 1;
        } else
        {
          Data.stat_screen_number--;
        }
      }
      if(hidden_menu)
      {
        if(Data.menu_select > max_struct_index)
          Data.menu_select = 0;
      } else
      {
        if(Data.menu_select > max_public_string_count)
          Data.menu_select = 0;
      }
      if(Data.modul_menu_select > modul_max_struct_index)
        Data.modul_menu_select = 0;

      key = 0;

      ///////////
      if((Data.enter_menu_item == ENABLE) && (Settings.AMODUL_menu == 0))
      {
        if(Data.menu_select > max_struct_index)
          return;
        if(Data.menu_select == 0)
          return;

        if(Menu_list[Data.menu_select - 1].Minus_reaction != 0x00)      // ���� ����� ������� ����������, �� ��������� ��.
        {
          (*Menu_list[Data.menu_select - 1].Minus_reaction) (&Data.menu_select);        // ������  ������� - �������� ���� ��� :)
        }
      }
      ///////////
      if((Settings.AMODUL_menu != 0) && (Data.enter_menu_item == ENABLE))
      {
        if(Data.modul_menu_select > modul_max_struct_index)
          return;
        if(Data.modul_menu_select == 0)
          return;

        if(Modul_Menu_list[Data.modul_menu_select - 1].Minus_reaction != 0x00)  // ���� ����� ������� ����������, �� ��������� ��.
        {
          (*Modul_Menu_list[Data.modul_menu_select - 1].Minus_reaction) (&Data.modul_menu_select);      // ������  ������� - �������� ���� ��� :)
        }
      }
    }
  }
  /////////////////////////////////
  if(key & 0x1)                 // ������ ��nu
  {
    while (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3));
    while (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4));
    while (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6));

    DataUpdate.Need_display_update = ENABLE;
    LcdClear();                 // ������� ����� ����� � �������

    delay_ms(10);
    key = 0;

    ///////////

    if(Settings.AMODUL_mode > 0)
    {
//      ���� ������ ������ � ������ ������-�

      if(Data.modul_menu_select > 0)
      {
        if(Data.enter_menu_item == DISABLE)
        {
          Data.enter_menu_item = ENABLE;
        } else
        {
          Data.enter_menu_item = DISABLE;
          eeprom_write_settings(MODUL_MENU);    //��������� ���������
        }
      } else
      {
        Settings.AMODUL_menu++;
        if(Settings.AMODUL_menu > 1)
          Settings.AMODUL_menu = 0;
      }


    } else
    {
      if(Settings.AB_mode > 0)
      {
        Settings.AB_mode = 0;   // ������ ������ �����-����
        Data.AB_fon = 0;
      } else
      {
        if(Data.menu_select > 0)
        {
          if(Data.enter_menu_item == DISABLE)
          {
            Data.enter_menu_item = ENABLE;
          } else
          {
            Data.enter_menu_item = DISABLE;
            eeprom_write_settings(MAIN_MENU);   //��������� ���������
          }
        }
      }
      if(Data.menu_select == 0)
        Data.screen++;
    }
  }
  if(Data.screen > 3)
    Data.screen = 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
