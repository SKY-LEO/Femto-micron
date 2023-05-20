#include <stdio.h>
#include <stdint.h>
#include "STM32L1xx.h"          // Device header
#include "main.h"
#include "math.h"

#define DOR_OFFSET                 ((uint32_t)0x0000002C)

// ===============================================================================================

uint32_t precision_measure()
{
  uint32_t i = 0;
  uint32_t fail = 0;
  uint32_t avg = 0;             // Xштр
  uint32_t avg_summ = 0;
  uint32_t n = 0;               // n
  long int xshtr_xi_q[40];      // n
  long int xshtr_xi_q_summ = 0;
  float sxstrih = 0;
  float tkrit = 0;
  float delta_x = 0;
  float epsi = 0;

  avg = Data.fonmodule;

  //////////////////////////////////////////////////////////
  for (i = 1; i <= 30; i++)     // Поиск адекватных элементов массива
  {
    if((Data.AMODULE_fon[i] > (avg * 1.5)) || (Data.AMODULE_fon[i] < (avg / 1.5)))      // Если замер двухкрано превышает среднее число
    {
      fail++;
      if(fail > 1)              // если ошибочных замеров больше двух, пересчет.
      {
        break;
      }
    } else
    {
      if(Data.AMODULE_fon[i] == 0)
        break;

      n++;
    }
  }

  if(n < 2)
  {                             // Если недостаточно данных для вычисления
    Data.fonmodule = Data.AMODULE_fon[1];
  } else
  {
    for (i = 1; i <= n; i++)    // Расчет среднего
    {
      avg_summ += Data.AMODULE_fon[i];
    }

    avg = avg_summ / n;
    //////////////////////////////////////////////////////////
    // Вычисление массива (Xштр-Xi)^2
    for (i = 1; i <= n; i++)
    {
      xshtr_xi_q[i] = avg;
      xshtr_xi_q[i] -= Data.AMODULE_fon[i];
      xshtr_xi_q[i] *= xshtr_xi_q[i];
      xshtr_xi_q_summ += xshtr_xi_q[i];
    }
    //////////////////////////////////////////////////////////
    // Вычисление Sxштр
    sxstrih = xshtr_xi_q_summ;
    sxstrih /= (n * (n - 1));
    sxstrih = sqrt(sxstrih);

    //////////////////////////////////////////////////////////
    // Вычисление t-критерий Стьюдента для P=0.95
    switch (n)
    {
    case 2:
      tkrit = 12.70620474;
      break;
    case 3:
      tkrit = 4.30265273;
      break;
    case 4:
      tkrit = 3.182446305;
      break;
    case 5:
      tkrit = 2.776445105;
      break;
    case 6:
      tkrit = 2.570581836;
      break;
    case 7:
      tkrit = 2.446911851;
      break;
    case 8:
      tkrit = 2.364624252;
      break;
    case 9:
      tkrit = 2.306004135;
      break;
    case 10:
      tkrit = 2.262157163;
      break;
    case 11:
      tkrit = 2.228138852;
      break;
    case 12:
      tkrit = 2.20098516;
      break;
    case 13:
      tkrit = 2.17881283;
      break;
    case 14:
      tkrit = 2.160368656;
      break;
    case 15:
      tkrit = 2.144786688;
      break;
    case 16:
      tkrit = 2.131449546;
      break;
    case 17:
      tkrit = 2.119905299;
      break;
    case 18:
      tkrit = 2.109815578;
      break;
    case 19:
      tkrit = 2.10092204;
      break;
    case 20:
      tkrit = 2.093024054;
      break;
    case 21:
      tkrit = 2.085963447;
      break;
    case 22:
      tkrit = 2.079613845;
      break;
    case 23:
      tkrit = 2.073873068;
      break;
    case 24:
      tkrit = 2.06865761;
      break;
    case 25:
      tkrit = 2.063898562;
      break;
    case 26:
      tkrit = 2.059538553;
      break;
    case 27:
      tkrit = 2.055529439;
      break;
    case 28:
      tkrit = 2.051830516;
      break;
    case 29:
      tkrit = 2.048407142;
      break;
    case 30:
      tkrit = 2.045229642;
      break;
    default:
      tkrit = 2.045229642;
      break;
    }
    //////////////////////////////////////////////////////////
    // Вычисление Дельта-X
    delta_x = tkrit * sxstrih;

    //////////////////////////////////////////////////////////
    // Вычисление Э
    epsi = (delta_x / avg) * 100;

    Data.fonmodule = avg;

    return epsi * 10;
  }
  return 1000;
}

// ===============================================================================================



// ===============================================================================================
void check_isotop_time()
{
  if(Settings.Second_count == 0)
  {
    eeprom_read_settings(MAIN_MENU);    // Чтение
    Settings.Isotop = 0;
    Settings.Second_count = Settings.Isotop_count_cs137;
    Settings.ACAL_count = Settings.Isotop_ACAL_cs137;
    eeprom_write_settings(MAIN_MENU);   // Запись

    sprintf(lcd_buf, LANG_ERRISO);      // Пишем в буфер значение счетчика
    LcdString(1, 5);            // // Выводим обычным текстом содержание буфера
    sprintf(lcd_buf, LANG_ERRISO2);     // Пишем в буфер значение счетчика
    LcdString(1, 6);            // // Выводим обычным текстом содержание буфера
    sprintf(lcd_buf, LANG_ERRISO3);     // Пишем в буфер значение счетчика
    LcdString(1, 7);            // // Выводим обычным текстом содержание буфера

    LcdUpdate();                // записываем данные из сформированного фрейм-буфера на дисплей
    delay_ms(3000);

  }
}

// ===============================================================================================



// ===============================================================================================
void reload_active_isotop_time()
{
  switch (Settings.Isotop)
  {
  case 0x0:
    Settings.Second_count = Settings.Isotop_count_cs137;
    Settings.ACAL_count = Settings.Isotop_ACAL_cs137;
    break;
  case 0x1:
    Settings.Second_count = Settings.Isotop_count_eu152;
    Settings.ACAL_count = Settings.Isotop_ACAL_eu152;
    break;
  case 0x2:
    Settings.Second_count = Settings.Isotop_count_na22;
    Settings.ACAL_count = Settings.Isotop_ACAL_na22;
    break;
  case 0x3:
    Settings.Second_count = Settings.Isotop_count_cd109;
    Settings.ACAL_count = Settings.Isotop_ACAL_cd109;
    break;
  case 0x4:
    Settings.Second_count = Settings.Isotop_count_am241;
    Settings.ACAL_count = Settings.Isotop_ACAL_am241;
    break;
  case 0x5:
    Settings.Second_count = Settings.Isotop_count_y88;
    Settings.ACAL_count = Settings.Isotop_ACAL_y88;
    break;
  case 0x6:
    Settings.Second_count = Settings.Isotop_count_ti44;
    Settings.ACAL_count = Settings.Isotop_ACAL_ti44;
    break;
  case 0x7:
    Settings.Second_count = Settings.Isotop_count_ba133;
    Settings.ACAL_count = Settings.Isotop_ACAL_ba133;
    break;
  case 0x8:
    Settings.Second_count = Settings.Isotop_count_th228;
    Settings.ACAL_count = Settings.Isotop_ACAL_th228;
    break;
  }

  Settings.AMODUL_Alarm_level_raw = (Settings.AMODUL_Alarm_level * Settings.ACAL_count) / 100;

  plus_rad_reset(0x00);
}

// ===============================================================================================


void check_wakeup_keys(void)
{
  if((!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)
      && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) && !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)) || Power.Display_active)
  {
    if((Settings.Sound == 1) || (Settings.Sound == 2))
      sound_activate();
    Power.sleep_time = Settings.Sleep_time;
  }

}

// ===============================================================================================
// лицухи
//----------------------------------------------------------------
/*
FunctionalState check_license(void)
{
	#define lic_num 14
	const uint32_t license[lic_num] = {
																0x42C86A97, // Shodan handmade black 	0D473130 35383935 00490032
																0x43B26A93, // Shodan handmade black 	0E473130 35383935 0033002E
																0x44B26AAA, // Shodan handmade white 	0F473130 35383935 00330045
																0x43A86A98, // Shodan handmade white 	0E473130 35383935 00290033
																0x43A96A98, // Nusik1975             	0E473130 35383935 002A0033
																0x44C36A84, // Nusik1975 						 	0F473130 35383935 0044001F
																0x44AD6A8F, // Nusik1975 							0F473130 35383935 002E002A
																0x41F062A9, // Nusik1975 							18473034 29313236 0078003F
																0x47A06C84, // FullName 							13473330 34363934 00230020
																0x4AC46791, // FullName 							17473334 33353436 00480027	
																0x4AC46790, // FullName 							17473334 33353436 00480026
																0x4A9E67AC, // FullName 							17473334 33353436 00220042
																0x47A06C88, // FullName 							13473330 34363934 00230024
																0x42C06A9E  // Ivanjust              	0D473130 35383935 00410039
															 };

	uint32_t i=0, CPU_serial=0, EEPROM_serial=0, tmp=0;
	FunctionalState found=DISABLE;
	
	CPU_serial+=U_ID_0;
	CPU_serial+=U_ID_1;
	CPU_serial+=U_ID_2;

	tmp=Settings.serial0 & 0xff;
	tmp=tmp<<24;
	EEPROM_serial+=tmp;

	tmp=Settings.serial1 & 0xff;
	tmp=tmp<<16;
	EEPROM_serial+=tmp;

	tmp=Settings.serial2 & 0xff;
	tmp=tmp<<8;
	EEPROM_serial+=tmp;

	tmp=Settings.serial3 & 0xff;
	EEPROM_serial+=tmp;

	if (CPU_serial == EEPROM_serial)
	{
		found=ENABLE;
	} 
	else
	{
		for (i=0;i<lic_num;i++) if( CPU_serial == license[i]) found=ENABLE;
	}
	
	return found;
	
}

*/
// ===============================================================================================
float convert_mkr_sv(uint32_t mkrn)
{
  float sv = 0;
  sv = mkrn;
  sv *= 0.0098;
  return sv;
}




// ===============================================================================================
uint32_t calc_ab(void)
{
  uint32_t i;
  float gamma_level = 0;
  float AB_level = 0;
  float pi4 = 0.78539815;       // Пи/4
  float S = 0;                  //
  float S_multipiller = 0;      //
// fon_level - гамма фон мкР/ч
// fon_level/(Settings.Second_count/60) - частиц в минуту по гамме
  for (i = 0; i < 15; i++)
  {
    AB_level += Detector_AB_massive[i]; // подсчет импульсов за минуту
  }
  gamma_level = (float) Data.fon_level / ((float) Settings.Second_count / 60);  // 198 имп/м

  if(AB_level <= gamma_level)
    return 0;

  AB_level -= gamma_level;

  // Компенсация процента регистрации счетчика
  AB_level *= 100;
  AB_level = AB_level / (float) Settings.Beta_procent;


  S = pi4 * ((float) Settings.Beta_window / 10) * ((float) Settings.Beta_window / 10);  //площадь отверстия
  S_multipiller = 100 / S;      // на сколько надо умножить частицы чтобы выйки на "частиц на см2 за минуту"
  S = AB_level * S_multipiller;

  return (uint32_t) S;
}


// ===============================================================================================
void recalculate_fon(void)
{
  uint32_t i, pointer;
  uint32_t massive_len = Settings.Second_count >> 2;    // 50@200 62@250
  uint32_t recalc_len = massive_len / Data.auto_speedup_factor; // 62/9 = 6.8

  Data.fon_level = 0;

  for (i = 0; i < recalc_len; i++)
  {
    if(Detector_massive_pointer >= i)
    {
      pointer = Detector_massive_pointer - i;
    } else
    {
      pointer = massive_len - (i - Detector_massive_pointer);
    }
    Data.fon_level += Detector_massive[pointer];
  }

  Data.fon_level = (Data.fon_level * Data.auto_speedup_factor) + ((Data.fon_level / recalc_len) * (massive_len % Data.auto_speedup_factor));    // фон 6-ти ячеек * 9 + ячейка 24000/6=4000; остаток от деления 8
  // (4000/9*)8=3552; 24000+3552=27552
}


// ===============================================================================================
void sleep_mode(FunctionalState sleep)
{
  if(Settings.Sleep_time > 0 && !Power.USB_active)
  {
/*    Power.Pump_deny = ENABLE;
    if(Power.Pump_active)
      Pump_now(DISABLE);
*/
    set_msi();
    if(sleep)
    {
      RTC_ITConfig(RTC_IT_WUT, DISABLE);

      GPIO_SetBits(GPIOC, GPIO_Pin_13); // Выключаем подсветку                                  

      display_off();            // выключить дисплей
      GPIO_ResetBits(GPIOA, GPIO_Pin_7);        // Фиксируем режим 1.8 вольта, с низким потреблением ножки

      delay_ms(1000);           // подождать установки напряжения
      DataUpdate.Need_batt_voltage_update = ENABLE;     // разрешить работу АЦП
      adc_check_event();        // запустить преобразование
      delay_ms(100);            // подождать установки напряжения

      //PWR_FastWakeUpCmd(ENABLE);
      PWR_UltraLowPowerCmd(ENABLE);
      PWR_PVDCmd(DISABLE);
      RTC_ITConfig(RTC_IT_WUT, ENABLE);
    } else
    {
      RTC_ITConfig(RTC_IT_WUT, DISABLE);
      GPIO_SetBits(GPIOA, GPIO_Pin_7);  // Переключаем в режим 3 вольта
      delay_ms(400);            // подождать установки напряжения
      display_on();             // включить дисплей
      DataUpdate.Need_batt_voltage_update = ENABLE;     // разрешить работу АЦП
      DataUpdate.Need_display_update = ENABLE;
      adc_check_event();        // запустить преобразование
      RTC_ITConfig(RTC_IT_WUT, ENABLE);
      sound_deactivate();
    }
//    Power.Pump_deny = DISABLE;
  }
}



// ===============================================================================================
void geiger_calc_fon(void)
{
  DataUpdate.Need_fon_update = DISABLE;
  DataUpdate.Need_display_update = ENABLE;
  if(Data.fon_level > Settings.Alarm_level && Settings.Alarm_level > 0 && Alarm.Alarm_active == DISABLE)
  {
    Alarm.Alarm_active = ENABLE;
    Alarm.User_cancel = DISABLE;
    if(Power.Display_active == DISABLE)
    {
      Data.screen = 1;
      Power.sleep_time = Settings.Sleep_time;
      sleep_mode(DISABLE);
      sound_activate();
    } else
      sound_activate();

  }
  if((Alarm.Alarm_active && Data.fon_level < Settings.Alarm_level) || (Alarm.Alarm_active && Settings.Alarm_level == 0))
  {
    sound_deactivate();
    Power.Sound_active = DISABLE;
    Alarm.Alarm_active = DISABLE;
    Alarm.User_cancel = DISABLE;
    Alarm.Alarm_beep_count = 0;

  }
}

// ===============================================================================================
