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

uint16_t key;                   // ������ ������� ������ [012]
uint8_t menu_key_long;//TEST
uint8_t key_long_timer_is_on;//TEST

uint16_t Detector_massive[Detector_massive_pointer_max + 1];
uint32_t ram_Doze_massive[doze_length + 1];     // 1 ������ = 10 �����, �� ���������� �����
uint32_t ram_max_fon_massive[doze_length + 1];  // 1 ������ = 10 �����, �� ���������� �����

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

uint32_t Detector_AB_massive[15];       // 1 ������, ����������� �� 4 ���

FunctionalState Sound_key_pressed = DISABLE;



/////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
	
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x3000);

  set_msi();
	
	// ���������� �������
  DBGMCU_Config(DBGMCU_SLEEP | DBGMCU_STANDBY | DBGMCU_STOP, DISABLE);

	set_bor();

  DataUpdate.Need_erase_flash = ENABLE;
  Data.main_menu_stat = 1;

  Settings.Geiger_voltage = 360;        // ���������� �� ������� 360 �����
  Settings.Pump_Energy = 350;   // ������� ������� 350 ���
  DataUpdate.current_flash_page = 0;

  io_init();                    // ������������� ������ ��
	
  eeprom_write_default_settings();      // ��������, �������� �� EEPROM
  eeprom_read_settings(MAIN_MENU);      // ������ �������� �� EEPROM
  eeprom_read_settings(MODUL_MENU);     // ������ �������� �� EEPROM
  reload_active_isotop_time();  // ������������ ������� ����� �� ��������
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
  //tim4_Config();//������ �
//--------------------------------------------------------------------
  RTC_Config();                 // ������������� ���� � ����
//--------------------------------------------------------------------
// ������������� �������
//--------------------------------------------------------------------
  delay_ms(50);                 // ��������� ��������� ����������
	display_on();
//--------------------------------------------------------------------
  adc_init();
  delay_ms(100);
  adc_calibration();
  delay_ms(10);
//--------------------------------------------------------------------
  EXTI9_Config();//TODO ����������� � USB TEST
  EXTI0_Config();
  EXTI1_Config();
  EXTI2_Config();
  EXTI5_Config(); // ������� �1
	//EXTI10_Config(); ������� �2 

  // ������������� �������
  PumpTimerConfig();


  DataUpdate.Need_batt_voltage_update = ENABLE;

  if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))
    hidden_menu = DISABLE;       // �������� ��������� ������� ����

  sound_activate();
  delay_ms(500);                // ��������� ��������� ����������
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
      sleep_mode(DISABLE);      // ���� ������� ��� ��������, � ������� ��� ��� �����������, ��������� ���������� � �������� �������

    if(Power.Display_active)
    {
      check_isotop_time();      // �������� ������� ����������
      if(Power.sleep_time == 0 && !Alarm.Alarm_active)
			{
				sleep_mode(ENABLE);     // ������� ��� �������� �� ����, � ������� ��� �������, �� ��������� ��� � �������� ����������
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
      usb_activate(0x0);        // ���� ������� USB ������ ���������� �������� USB
    }

    if(!Power.USB_active)       // ���� USB �� �������, ����� ������� � ���
    {
      if(bat_cal_running > 0)
				Power.sleep_time = Settings.Sleep_time; // � ������ ���������� ��� �� �����

      if((current_pulse_count < 30) && (Data.fon_level < 10000) && (Data.AB_fon < 10000))       // ���� ������� �� �����������, �� ����� ���� � ���
      {
        if(SystemCoreClock > 20000000)  // ���� ������� ���� 20 ���, �������� �������
          set_msi();

        if(!PumpData.Active && !Power.Sound_active && (Settings.AMODUL_mode == 0))
        {
          PWR_FastWakeUpCmd(ENABLE);
          PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI); // ��������� � ���
          PWR_FastWakeUpCmd(DISABLE);
        } else
        {
          //PWR_EnterSleepMode(PWR_Regulator_ON, PWR_SLEEPEntry_WFI);
        }
      } else
      {                         // ���� ��� ����� �������, ����������� ������� �� �� ��������
        if((ADCData.Power_voltage > 2800) && (SystemCoreClock < 20000000))      // ���� ������� ���� 20 ���, ������� �������
          set_pll_for_usb();
//        if(Settings.AMODUL_mode != 0)   // ���� ������� ������, ���������� � ����� SLEEP
//          PWR_EnterSleepMode(PWR_Regulator_ON, PWR_SLEEPEntry_WFI);

      }

    } else {
      USB_work();               // ���� USB �������, ����������� �������� ������
						
			if(Power.display_offed == DISABLE && Power.sleep_time == 0 && !Alarm.Alarm_active)
			{
				ssd1306_SetDisplayOn(0);
				Power.display_offed = ENABLE;
			}
		}
  }
/////////////////////////////////////////////////////////////////////////////// 
}
