#include <stdio.h>
#include <stdint.h>
#include "STM32L1xx.h"          // Device header
#include "main.h"

DataUpdateDef DataUpdate;
ADCDataDef ADCData;
SettingsDef Settings;
AlarmDef Alarm;
PowerDef Power;
DataDef Data;
PumpDataDef PumpData;

uint16_t key;                   // массив нажатых кнопок [012]
uint8_t menu_key_long;//TEST
uint8_t key_long_timer_is_on;//TEST

uint16_t Detector_massive[Detector_massive_pointer_max + 1];
uint32_t ram_Doze_massive[doze_length + 1];     // 1 ячейка = 10 минут, на протяжении суток
uint32_t ram_max_fon_massive[doze_length + 1];  // 1 ячейка = 10 минут, на протяжении суток

uint16_t USB_maxfon_massive_pointer = 0;
uint16_t USB_doze_massive_pointer = 0;
uint16_t current_pulse_count = 0;
uint16_t eeprom_address = 0;
uint8_t Pump_on_alarm_count = 0;


uint16_t Detector_massive_pointer = 0;
uint32_t Cal_count = 0;
uint32_t Cal_count_time = 0;
FunctionalState pump_on_impulse = DISABLE;
uint32_t Isotop_counts = 0;

FunctionalState poweroff_state = DISABLE;
FunctionalState hidden_menu = ENABLE;
FunctionalState Pump_on_alarm = DISABLE;

FunctionalState spect_impulse = DISABLE;

uint16_t bat_cal_running = 0;

uint32_t Detector_AB_massive[15];       // 1 минута, интервалами по 4 сек

FunctionalState Sound_key_pressed = DISABLE;



/////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
	
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x3000);

  set_msi();
	
	// Отключение отладки
  DBGMCU_Config(DBGMCU_SLEEP | DBGMCU_STANDBY | DBGMCU_STOP, DISABLE);

	set_bor();

  DataUpdate.Need_erase_flash = ENABLE;
  Data.main_menu_stat = 1;

  Settings.Geiger_voltage = 360;        // Напряжение на датчике 360 вольт
  Settings.Pump_Energy = 350;   // энергия накачки 350 мТл
  DataUpdate.current_flash_page = 0;

  io_init();                    // Инициализация потров МК
	
  eeprom_write_default_settings();      // Проверка, заполнен ли EEPROM
  eeprom_read_settings(MAIN_MENU);      // Чтение настроек из EEPROM
  eeprom_read_settings(MODUL_MENU);     // Чтение настроек из EEPROM
  reload_active_isotop_time();  // Перезагрузка времени счета по изотопам
  Data.screen = 1;
  Data.AB_fon = 0;
  Power.USB_active = DISABLE;
  Power.sleep_time = Settings.Sleep_time;
  Power.Display_active = ENABLE;
	Power.charging = DISABLE;
	
	Power.display_offed = DISABLE;
	Power.display_just_onned = DISABLE;

  timer10_Config();
  tim3_Config();
  //tim4_Config();//модуль А
//--------------------------------------------------------------------
  RTC_Config();                 // Конфигурируем часы с нуля
//--------------------------------------------------------------------
// инициализация дисплея
//--------------------------------------------------------------------
  delay_ms(50);                 // подождать установки напряжения
	display_on();
//--------------------------------------------------------------------
  adc_init();
  delay_ms(100);
  adc_calibration();
  delay_ms(10);
//--------------------------------------------------------------------
  EXTI9_Config();//TODO разобраться с USB TEST
  EXTI0_Config();
  EXTI1_Config();
  EXTI2_Config();
  EXTI5_Config(); // счетчик №1
	//EXTI10_Config(); счетчик №2 

  // Инициализация накачки
  PumpTimerConfig();


  DataUpdate.Need_batt_voltage_update = ENABLE;

  if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))
    hidden_menu = DISABLE;       // Закрытие сервисных пунктов меню

  sound_activate();
  delay_ms(500);                // подождать установки напряжения
  sound_deactivate();

  while (1)
/////////////////////////////////
  {
    //if(DataUpdate.RTC_tick_update==ENABLE)        RTC_tick_processing();
    if(DataUpdate.Need_fon_update == ENABLE)
      geiger_calc_fon();
    if(key > 0)
		{
			if(Power.display_just_onned == ENABLE)
			{
				delay_ms(300);
				Power.display_just_onned = DISABLE;
				key = 0;
			}else
			{
				keys_proccessing();
			}
		}
    if(DataUpdate.Need_batt_voltage_update)
      adc_check_event();

    ////////////////////////////////////////////////////

    if((Power.sleep_time > 0) && (!Power.Display_active))
      sleep_mode(DISABLE);      // Если дисплей еще выключен, а счетчик сна уже отсчитывает, поднимаем напряжение и включаем дисплей

    if(Power.Display_active)
    {
      check_isotop_time();      // Проверка наличия калибровки
      if(Power.sleep_time == 0 && !Alarm.Alarm_active)
			{
				sleep_mode(ENABLE);     // Счетчик сна досчитал до нуля, а дисплей еще активен, то выключаем его и понижаем напряжение
			}
      if(DataUpdate.Need_display_update == ENABLE)
      {
        DataUpdate.Need_display_update = DISABLE;
        LcdClear_massive();
        if(Data.screen == 1)
          main_screen();
        if(Data.screen == 2)
          menu_screen(NORMAL_menu_mode);
        if(Data.screen == 3)
          stat_screen();
      }
///////////////////////////////////////////////////////////////////////////////
    }
    if((!Power.USB_active) && (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)))
    {
			Power.charging = ENABLE;
			activate_charge_gpio();//TEST
      usb_activate(0x0);        // Если питание USB начало подаваться включаем USB
    }

    if(!Power.USB_active)       // если USB не активен, можно уходить в сон
    {
      if(bat_cal_running > 0)
				Power.sleep_time = Settings.Sleep_time; // В режиме калибровки АКБ не спать

      if((current_pulse_count < 30) && (Data.fon_level < 10000) && (Data.AB_fon < 10000))       // Если счетчик не зашкаливает, то можно уйти в сон
      {
        if(SystemCoreClock > 20000000)  // Если частота выше 20 мгц, понизить частоту
          set_msi();

        if(!PumpData.Active && !Power.Sound_active && (Settings.AMODUL_mode == 0))
        {
          PWR_FastWakeUpCmd(ENABLE);
          PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI); // Переходим в сон
          PWR_FastWakeUpCmd(DISABLE);
        } else
        {
          //PWR_EnterSleepMode(PWR_Regulator_ON, PWR_SLEEPEntry_WFI);
        }
      } else
      {                         // Если фон очень высокий, переключаем частоту МК на максимум
        if((ADCData.Power_voltage > 2800) && (SystemCoreClock < 20000000))      // Если частота ниже 20 мгц, поднять частоту
          set_pll_for_usb();
//        if(Settings.AMODUL_mode != 0)   // Если включен модуль, переходить в режим SLEEP
//          PWR_EnterSleepMode(PWR_Regulator_ON, PWR_SLEEPEntry_WFI);

      }

    } else {
      USB_work();               // если USB активен, попробовать передать данные
						
			if(Power.display_offed == DISABLE && Power.sleep_time == 0 && !Alarm.Alarm_active)
			{
				ssd1306_SetDisplayOn(0);
				Power.display_offed = ENABLE;
			}
		}
  }
/////////////////////////////////////////////////////////////////////////////// 
}
