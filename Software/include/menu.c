#include <stdio.h>
#include <string.h>
#include "main.h"
/* *INDENT-OFF* */
MenuItem Menu_list[max_struct_index] = {
  
//Сервис Адрес  Текст		Если значение 0		Если 1		если больше чем 1	Откуда брать само значение		минимум		максимум	дефолт	Реакция на увеличение	на уменьшение 
{0x00, 0x00, 		LANG_ALARM,			LANG_OFF,			"",				LANG_UMKR,			&Settings.Alarm_level,			0,			10000,	50,			&plus_alarm,			0x00,			&minus_alarm,			0x00},
{0x00, 0x04, 		LANG_SLEEP,			LANG_OFF,			"",				LANG_USEC,			&Settings.Sleep_time,				10,			10240,	80,			&plus_sleep,			0x00,			&minus_sleep,			0x00},
{0x00, 0x18, 		LANG_SOUND,			LANG_OFF,			LANG_ON,	LANG_KEY,				&Settings.Sound,						0,			2,			2,			&plus,						1,				&minus,						1},
{0x00, 0x50, 		LANG_VIBRO,			LANG_OFF,			LANG_ON,	LANG_ALARM2,		&Settings.Vibro,						0,			2,			2,			&plus,						1,				&minus,					1},
{0x00, 0xFFFF,  LANG_CLEARDO,		"*",					"*",			"*",						0x00,												0x00,		0x00,		0x00,		&plus_doze_reset,	0x00,			0x00,							0x00},
{0x00, 0xFFFF,  LANG_REBOOT,		"*",					"*",			"*",						0x00,												0x00,		0x00,		0x00,		&plus_reboot,			0x00,			&minus_poweroff,	0x00},
{0x00, 0x58,		LANG_UNITS,			LANG_UR,			LANG_UZV,	"",							&Settings.units,						0x00,		0x01,		0x01,		&plus,						1,				&minus,						0x00},
{0x00, 0xFFFF,  LANG_CLEAR_FON,	"*",					"*", 			"*",						0x00,												0x00,		0x00,		0x00,		&plus_rad_reset,	0x00,			0x00,							0x00},
{0x00, 0x7C,		LANG_SPEED,		LANG_OFF,			LANG_ON,	"",								&Settings.Speedup,					0x00,		0x01,		0x01,		&plus,						1,				&minus,						1},
// Заплатка на изотоп if(menu_struct_index == 9) ! Исправить в коде при изменении порядка пунктов меню!
{0x00, 0x80,		LANG_ISOTOP,		"",			      "",	    "",								&Settings.Isotop,						0x00,		0x08,		0x00,		&plus,						1,				&minus,						1},

// Приватные пункты меню
{0x01, 0xFFFF,  LANG_BETA_MEAS,	"*",					"*",			"*",						0x00,												0x00,		0x00,		0x00,		&plus_ab_engage,	0x00,			0x00,							0x00},
{0x01, 0x0C, 		LANG_CONTRAST,	"",						"",				"%u",						&Settings.contrast,					1,			25,			10,			&plus,						1,				&minus,						1},
{0x01, 0x08, 		LANG_REVERSE,		LANG_OFF,			LANG_ON,	"",						  &Settings.Display_reverse,	0x00,		0x01,		0x00,		&plus,						1,				&minus,						1},
{0x01, 0xF4, 		LANG_INVERSE,		LANG_OFF,			LANG_ON,	"",						  &Settings.Display_inverse,	0x00,		0x01,		0x00,		&plus,						1,				&minus,						1},
{0x01, 0x54, 		LANG_V4PUMP,		"",						"",				LANG_UV4PUMP,		&Settings.v4_target_pump,		4,			14,			8,			&plus,						1,				&minus,						1},
{0x01, 0x30, 		LANG_VOLTAGE,		"",						"",				LANG_UV,				&Settings.Geiger_voltage,		300,		450,		380,		&plus,						10,				&minus,						10},
// Заплатка на бета окно if(menu_struct_index == 16) ! Исправить в коде при изменении порядка пунктов меню!
{0x01, 0x6C,		LANG_BWINDOW,		"",						"",				LANG_BWINDOW_,	&Settings.Beta_window,			1,			100,		20,			&plus,						1,				&minus,						1},
{0x01, 0x70,		LANG_BPROCENT,	"",						"",				LANG_BPROCENT_,	&Settings.Beta_procent,			1,			100,		37,			&plus,						1,				&minus,						1},
{0x01, 0xFFFF,	LANG_REF_VOLT,	"",						"",				LANG_REF_VOLT_,	&ADCData.Power_voltage,			1202,		1242,		1224,		&plus_one_ref,		0x00,			&minus_one_ref,		0x00},
{0x01, 0xFFFF,  LANG_BAT_CAL,		"*",					"*",			"*",						0x00,												0x00,		0x00,		0x00,		&plus_batcal,			0x00,			0x00,							0x00},
{0x01, 0xF0,		LANG_SOUND,	  	"",  					"",				LANG_UHZ2,			&Settings.Beep_freq,				1000,	  20000,	8000,		&plus,						500,			&minus,						500},
{0x01, 0x78,		LANG_PUMP_AGR,	LANG_OFF,			LANG_ON,	"",	            &Settings.Pump_aggressive,	0,	    1,  		0,  		&plus,				   	1,				&minus,						1},
};
//////////////////////////////////////////////////////////////////////////////////////////////////
MenuItem Modul_Menu_list[modul_max_struct_index] = {
  
//Сервис   Текст		Если значение 0		Если 1		если больше чем 1	Откуда брать само значение	        	минимум		максимум	дефолт	Реакция на увеличение	на уменьшение 
{0x00, 0xEC,		LANG_ALARM,				LANG_OFF,		"",			LANG_UMKZV,				&Settings.AMODUL_Alarm_level,			0,				10000,	60,		&plus,				5,				&minus,						5},
{0x00, 0xFFFF,  LANG_ISOTOP,			"",			   	"",	    "",								&Settings.Isotop,			        		0x00,			0x08,		0x00,	&plus,				1,				&minus,						1},
{0x00, 0xE8,		LANG_ISOTOP_COUNTS,"", 	LANG_ISOTOP_COUNTS_, LANG_ISOTOP_COUNTS_,	&Settings.Isotop_counts,1,	   		20,			1,		&plus,				1,				&minus,						1},

{0x00, 0x94,		LANG_ISOTOP_CS137,"",					"",			LANG_ACAL,				&Settings.Isotop_ACAL_cs137,			10,	    	1450,		250,	&plus,				10,				&minus,						10},
{0x00, 0x98,		LANG_ISOTOP_EU152,"",					"",			LANG_ACAL,				&Settings.Isotop_ACAL_eu152,			10,	    	1450,		250,	&plus,				10,				&minus,						10},
{0x00, 0x9C,		LANG_ISOTOP_NA22, "",					"",			LANG_ACAL,				&Settings.Isotop_ACAL_na22,	   		10,	    	1450,		250,	&plus,				10,				&minus,						10},
{0x00, 0xA0,		LANG_ISOTOP_CD109,"",					"",			LANG_ACAL,				&Settings.Isotop_ACAL_cd109,			10,	    	1450,		250,	&plus,				10,				&minus,						10},
{0x00, 0xC4,		LANG_ISOTOP_AM241,"",					"",			LANG_ACAL,				&Settings.Isotop_ACAL_am241,			10,	    	1450,		250,	&plus,				10,				&minus,						10},
{0x00, 0xD4,		LANG_ISOTOP_TI44, "",					"",			LANG_ACAL,				&Settings.Isotop_ACAL_ti44,	   		10,	    	1450,		250,	&plus,				10,				&minus,						10},
{0x00, 0xCC,		LANG_ISOTOP_Y88,  "",					"",			LANG_ACAL,				&Settings.Isotop_ACAL_y88,		   	10,	    	1450,		250,	&plus,				10,				&minus,						10},
{0x00, 0xDC,		LANG_ISOTOP_BA133,"",					"",			LANG_ACAL,				&Settings.Isotop_ACAL_ba133,			10,	    	1450,		250,	&plus,				10,				&minus,						10},
{0x00, 0xE4,		LANG_ISOTOP_TH228,"",					"",			LANG_ACAL,				&Settings.Isotop_ACAL_th228,			10,	    	1450,		250,	&plus,				10,				&minus,						10}
/*
{0x00, 0xA4,		LANG_SPECT_START,"",				  "",			"%u",	    				&Settings.AMODUL_spect_start,			10,	    	20000,	1000,	&plus,				100,			&minus,						100},
{0x00, 0xA8,		LANG_SPECT_MULTIP,"",			  	"",			"%u",		    			&Settings.AMODUL_spect_multi,			1,	    	200,	 	70,	  &plus,				1,				&minus,						1},
{0x00, 0xAC,		LANG_SPECT_MARK1,"",				  "",			"%u",	    				&Settings.AMODUL_spect_mark1,			1,	    	100,		10, 	&plus,				1,				&minus,						1},
{0x00, 0xB0,		LANG_SPECT_MARK2,"",				  "",			"%u",	  	  			&Settings.AMODUL_spect_mark2,			1,	    	100,		20,	  &plus,				1,				&minus,						1},
{0x00, 0xB4,		LANG_SPECT_MARK3,"",				  "",			"%u",		    			&Settings.AMODUL_spect_mark3,			1,	    	100,		30,	  &plus,				1,				&minus,						1},
{0x00, 0xB8,		LANG_SPECT_MARK4,"",				  "",			"%u",	    				&Settings.AMODUL_spect_mark4,			1,	    	100,		40,	  &plus,				1,				&minus,						1},
{0x00, 0xBC,		LANG_SPECT_MARK5,"",				  "",			"%u",	    				&Settings.AMODUL_spect_mark5,			1,	    	100,		50,	  &plus,				1,				&minus,						1}
*/
};
//////////////////////////////////////////////////////////////////////////////////////////////////
/* *INDENT-ON* */


void main_screen()
{
  RTC_TimeTypeDef RTC_TimeStructure;
  RTC_DateTypeDef RTC_DateStructure;


  uint32_t battery_procent, i = 0, x = 0;
  //uint32_t i = 0, x = 0;

  if(Settings.AMODUL_mode == 0)
  {
    // Индикация батарейки и выключение питания при разряде
    if(Settings.AB_mode == 0)
    {
      if(ADCData.Batt_voltage < 3500)
				minus_poweroff(0x00);   // Если меньше 3.5В выключаем прибор.
			
#ifdef DISPLAY_SSD1306
			
			#ifdef STM_15XCBX
			if(Data.main_menu_stat != 0x0A)
			#endif
			
			#ifdef STM_15XCCX
			if(Data.main_menu_stat != 0x0D)
			#endif
			
			{
				battery_procent = ADCData.Batt_voltage;
				battery_procent -= 3500;
				battery_procent /= 5;
				LcdBatt(104, 2, 104 + 10, 2 + 19, battery_procent); //LcdBatt(84, 19, 84 + 10, 19 + 19, battery_procent); TEST
			}
#endif
			
		}
		
#ifdef DISPLAY_CH1115
				battery_procent = ADCData.Batt_voltage;
				battery_procent -= 3500;
				battery_procent /= 5;
				LcdBatt(104, 2, 104 + 10, 2 + 19, battery_procent); //LcdBatt(84, 19, 84 + 10, 19 + 19, battery_procent); TEST
#endif

    if(Data.main_menu_stat > num_of_main_menu_stat)
		{
      Data.main_menu_stat = 1;
		}
    if(Data.main_menu_stat < 1)
		{
      Data.main_menu_stat = num_of_main_menu_stat;
		}

    if(DataUpdate.Need_update_mainscreen_counters == ENABLE)    // Если требуется обновление счетчиков
    {
      DataUpdate.Need_update_mainscreen_counters = DISABLE;
      Data.Max_fon = 0;
      Data.Doze_day_count = 0;
      Data.Doze_week_count = 0;
      Data.Doze_month_count = 0;
      Data.Doze_hour_count = 0;
      Data.Doze_2month_count = 0;
			
#ifdef STM_15XCCX
			Data.Doze_3month_count = 0;
			Data.Doze_4month_count = 0;
			Data.Doze_5month_count = 0;
			//Data.Doze_6month_count = 0;
#endif

      for (i = doze_length_5month; i > 0; i--)
      {
        if(i < doze_length_hour)
          Data.Doze_hour_count += flash_read_massive(i, dose_select);   // расчет недельной дозы
        if(i < doze_length_day)
          Data.Doze_day_count += flash_read_massive(i, dose_select);    // расчет дневной дозы
        if(i < doze_length_week)
        {
          Data.Doze_week_count += flash_read_massive(i, dose_select);   // расчет недельной дозы
          x = flash_read_massive(i, max_fon_select);
          if(x > Data.Max_fon)
            Data.Max_fon = x;   // расчет максимального фона
        }
        if(i < doze_length_month)
          Data.Doze_month_count += flash_read_massive(i, dose_select);  // расчет месячной дозы
        if(i < doze_length_2month)
          Data.Doze_2month_count += flash_read_massive(i, dose_select); // расчет месячной дозы

#ifdef STM_15XCCX
				if(i < doze_length_3month)
          Data.Doze_3month_count += flash_read_massive(i, dose_select); // расчет месячной дозы
				if(i < doze_length_4month)
          Data.Doze_4month_count += flash_read_massive(i, dose_select); // расчет месячной дозы
				if(i < doze_length_5month)
          Data.Doze_5month_count += flash_read_massive(i, dose_select); // расчет месячной дозы
				//if(i < doze_length_6month)
        //  Data.Doze_6month_count += flash_read_massive(i, dose_select); // расчет месячной дозы
#endif
				
      }
    }

    if((Settings.AB_mode == 0) && (Settings.AMODUL_mode == 0))
    {
      switch (Data.main_menu_stat)
      {
      case 0x01:
#ifdef DISPLAY_CH1115
				sprintf(lcd_buf, LANG_TIME);    // Пишем в буфер значение счетчика
        LcdString(1, 4);        // // Выводим обычным текстом содержание буфера
        sprintf(lcd_buf, LANG_DATE);    // Пишем в буфер значение счетчика
        LcdString(1, 5);        // // Выводим обычным текстом содержание буфера
#endif
        //sprintf(lcd_buf, LANG_TIME);    // Пишем в буфер значение счетчика
        //LcdString(1, 4);        // // Выводим обычным текстом содержание буфера
        //sprintf(lcd_buf, LANG_DATE);    // Пишем в буфер значение счетчика
        //LcdString(1, 5);        // // Выводим обычным текстом содержание буфера

        RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
        RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);

#ifdef DISPLAY_SSD1306
				sprintf(lcd_buf, "%0.2d:%0.2d:%0.2d,", RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes, RTC_TimeStructure.RTC_Seconds);
        LcdString(1, 4);        // // Выводим обычным текстом содержание буфера
        sprintf(lcd_buf, "%0.2d.%0.2d.%0.4d", RTC_DateStructure.RTC_Date, RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Year+2000);
        LcdString(11, 4);        // // Выводим обычным текстом содержание буфера
#endif
			
#ifdef DISPLAY_CH1115
				sprintf(lcd_buf, "%0.2d:%0.2d:%0.2d", RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes, RTC_TimeStructure.RTC_Seconds);
        LcdString(9, 4);        // // Выводим обычным текстом содержание буфера
				sprintf(lcd_buf, "%0.2d.%0.2d.%0.2d", RTC_DateStructure.RTC_Date, RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Year);
        LcdString(9, 5);        // // Выводим обычным текстом содержание буфера
#endif

        break;
        // -----------------------------------------
      case 0x02:
        sprintf(lcd_buf, LANG_MAXFON);  // Пишем в буфер значение счетчика
        LcdString(1, 4);        // // Выводим обычным текстом содержание буфера

        if(!Settings.units)
        {
          sprintf(lcd_buf, LANG_9UMKR, Data.Max_fon);   // Пишем в буфер значение счетчика
        } else
        {
          sprintf(lcd_buf, LANG_9UMKZV, convert_mkr_sv(Data.Max_fon));  // Пишем в буфер значение счетчика
        }
				
#ifdef DISPLAY_SSD1306
        LcdString(9, 4);        // // Выводим обычным текстом содержание буфера
#endif
				
#ifdef DISPLAY_CH1115
        LcdString(1, 5);        // // Выводим обычным текстом содержание буфера
#endif
				
        break;
        // -----------------------------------------
      case 0x03:
        sprintf(lcd_buf, LANG_DOSE10M); // Пишем в буфер значение счетчика
        LcdString(1, 4);        // // Выводим обычным текстом содержание буфера

        if(flash_read_massive(doze_length_10m, dose_select) > 0)
        {
          //фон за час massive/(3600/время счета)
          if(!Settings.units)
          {
            sprintf(lcd_buf, LANG_9UMKR, (flash_read_massive(doze_length_10m, dose_select) * (Settings.Second_count >> 2)) / 900);      // Пишем в буфер значение счетчика
          } else
          {
            sprintf(lcd_buf, LANG_9UMKZV, convert_mkr_sv((flash_read_massive(doze_length_10m, dose_select) * (Settings.Second_count >> 2)) / 900));     // Пишем в буфер значение счетчика
          }
        } else
        {
          sprintf(lcd_buf, LANG_DOSECALC);      // Пишем в буфер значение счетчика
        }
				
#ifdef DISPLAY_SSD1306
        LcdString(9, 4);        // // Выводим обычным текстом содержание буфера
#endif

#ifdef DISPLAY_CH1115
        LcdString(1, 5);        // // Выводим обычным текстом содержание буфера
#endif
				
        break;
        // -----------------------------------------
      case 0x04:
        sprintf(lcd_buf, LANG_DOSEHOUR);        // Пишем в буфер значение счетчика
        LcdString(1, 4);        // // Выводим обычным текстом содержание буфера

        if(flash_read_massive(doze_length_hour, dose_select) > 0)
        {
          if(!Settings.units)
          {
            sprintf(lcd_buf, LANG_9UMKR, ((Data.Doze_hour_count * (Settings.Second_count >> 2)) / 900));        // Пишем в буфер значение счетчика
          } else
          {
            sprintf(lcd_buf, LANG_9UMKZV, convert_mkr_sv((Data.Doze_hour_count * (Settings.Second_count >> 2)) / 900)); // Пишем в буфер значение счетчика
          }
        } else
        {
          sprintf(lcd_buf, LANG_DOSECALC);      // Пишем в буфер значение счетчика
        }
				
#ifdef DISPLAY_SSD1306
        LcdString(9, 4);        // // Выводим обычным текстом содержание буфера
#endif

#ifdef DISPLAY_CH1115
        LcdString(1, 5);        // // Выводим обычным текстом содержание буфера
#endif
				
        break;
        // -----------------------------------------
      case 0x05:
        sprintf(lcd_buf, LANG_DOSE24H); // Пишем в буфер значение счетчика
        LcdString(1, 4);        // // Выводим обычным текстом содержание буфера         

        if(flash_read_massive(doze_length_day, dose_select) > 0)        // День
        {
          if(!Settings.units)
          {
            sprintf(lcd_buf, LANG_9UMKR, ((Data.Doze_day_count * (Settings.Second_count >> 2)) / 900)); // Пишем в буфер значение счетчика
          } else
          {
            sprintf(lcd_buf, LANG_9UMKZV, convert_mkr_sv((Data.Doze_day_count * (Settings.Second_count >> 2)) / 900));  // Пишем в буфер значение счетчика
          }
        } else
        {
          sprintf(lcd_buf, LANG_DOSECALC);      // Пишем в буфер значение счетчика
        }
				
#ifdef DISPLAY_SSD1306
        LcdString(9, 4);        // // Выводим обычным текстом содержание буфера
#endif

#ifdef DISPLAY_CH1115
        LcdString(1, 5);        // // Выводим обычным текстом содержание буфера
#endif
				
        break;
        // -----------------------------------------
      case 0x06:
        sprintf(lcd_buf, LANG_DOSEWEEK);        // Пишем в буфер значение счетчика
        LcdString(1, 4);        // // Выводим обычным текстом содержание буфера

        if(flash_read_massive(doze_length_week, dose_select) > 0)       // неделя
        {
          if(!Settings.units)
          {
            sprintf(lcd_buf, LANG_9UMKR, ((Data.Doze_week_count * (Settings.Second_count >> 2)) / 900));        // Пишем в буфер значение счетчика
          } else
          {
            sprintf(lcd_buf, LANG_9UMKZV, convert_mkr_sv((Data.Doze_week_count * (Settings.Second_count >> 2)) / 900)); // Пишем в буфер значение счетчика
          }
        } else
        {
          sprintf(lcd_buf, LANG_DOSECALC);      // Пишем в буфер значение счетчика
        }
				
#ifdef DISPLAY_SSD1306
        LcdString(9, 4);        // // Выводим обычным текстом содержание буфера
#endif

#ifdef DISPLAY_CH1115
        LcdString(1, 5);        // // Выводим обычным текстом содержание буфера
#endif
				
        break;
        // -----------------------------------------

				// -----------------------------------------
      case 0x07:
        sprintf(lcd_buf, LANG_DOSEMONTH);       // Пишем в буфер значение счетчика
        LcdString(1, 4);        // // Выводим обычным текстом содержание буфера

        if(flash_read_massive(doze_length_month, dose_select) > 0)      // неделя
        {
          if(!Settings.units)
          {
            sprintf(lcd_buf, LANG_9UMKR, ((Data.Doze_month_count * (Settings.Second_count >> 2)) / 900));       // Пишем в буфер значение счетчика
          } else
          {
            sprintf(lcd_buf, LANG_9UMKZV, convert_mkr_sv((Data.Doze_month_count * (Settings.Second_count >> 2)) / 900));        // Пишем в буфер значение счетчика
          }
        } else
        {
          sprintf(lcd_buf, LANG_DOSECALC);      // Пишем в буфер значение счетчика
        }
				
#ifdef DISPLAY_SSD1306
        LcdString(9, 4);        // // Выводим обычным текстом содержание буфера
#endif

#ifdef DISPLAY_CH1115
        LcdString(1, 5);        // // Выводим обычным текстом содержание буфера
#endif
				
        break;
        // -----------------------------------------

        // -----------------------------------------
      case 0x08:
        sprintf(lcd_buf, LANG_DOSE2MONTH);      // Пишем в буфер значение счетчика
        LcdString(1, 4);        // // Выводим обычным текстом содержание буфера

        if(flash_read_massive(doze_length_2month, dose_select) > 0)     // неделя
        {
          if(!Settings.units)
          {
            sprintf(lcd_buf, LANG_9UMKR, ((Data.Doze_2month_count * (Settings.Second_count >> 2)) / 900));      // Пишем в буфер значение счетчика
          } else
          {
            sprintf(lcd_buf, LANG_9UMKZV, convert_mkr_sv((Data.Doze_2month_count * (Settings.Second_count >> 2)) / 900));       // Пишем в буфер значение счетчика
          }
        } else
        {
          sprintf(lcd_buf, LANG_DOSECALC);      // Пишем в буфер значение счетчика
        }
				
#ifdef DISPLAY_SSD1306
        LcdString(9, 4);        // // Выводим обычным текстом содержание буфера
#endif

#ifdef DISPLAY_CH1115
        LcdString(1, 5);        // // Выводим обычным текстом содержание буфера
#endif
				
        break;
        // -----------------------------------------
#ifdef STM_15XCCX	
				// -----------------------------------------
      case 0x09:
        sprintf(lcd_buf, LANG_DOSE3MONTH);      // Пишем в буфер значение счетчика
        LcdString(1, 4);        // // Выводим обычным текстом содержание буфера

        if(flash_read_massive(doze_length_3month, dose_select) > 0)     // неделя
        {
          if(!Settings.units)
          {
            sprintf(lcd_buf, LANG_9UMKR, ((Data.Doze_3month_count * (Settings.Second_count >> 2)) / 900));      // Пишем в буфер значение счетчика
          } else
          {
            sprintf(lcd_buf, LANG_9UMKZV, convert_mkr_sv((Data.Doze_3month_count * (Settings.Second_count >> 2)) / 900));       // Пишем в буфер значение счетчика
          }
        } else
        {
          sprintf(lcd_buf, LANG_DOSECALC);      // Пишем в буфер значение счетчика
        }
				
	#ifdef DISPLAY_SSD1306
        LcdString(9, 4);        // // Выводим обычным текстом содержание буфера
	#endif

	#ifdef DISPLAY_CH1115
        LcdString(1, 5);        // // Выводим обычным текстом содержание буфера
	#endif
				
        break;
        // -----------------------------------------
				
				// -----------------------------------------
			case 0x0A:
        sprintf(lcd_buf, LANG_DOSE4MONTH);      // Пишем в буфер значение счетчика
        LcdString(1, 4);        // // Выводим обычным текстом содержание буфера

        if(flash_read_massive(doze_length_4month, dose_select) > 0)     // неделя
        {
          if(!Settings.units)
          {
            sprintf(lcd_buf, LANG_9UMKR, ((Data.Doze_4month_count * (Settings.Second_count >> 2)) / 900));      // Пишем в буфер значение счетчика
          } else
          {
            sprintf(lcd_buf, LANG_9UMKZV, convert_mkr_sv((Data.Doze_4month_count * (Settings.Second_count >> 2)) / 900));       // Пишем в буфер значение счетчика
          }
        } else
        {
          sprintf(lcd_buf, LANG_DOSECALC);      // Пишем в буфер значение счетчика
        }
				
	#ifdef DISPLAY_SSD1306
        LcdString(9, 4);        // // Выводим обычным текстом содержание буфера
	#endif

	#ifdef DISPLAY_CH1115
        LcdString(1, 5);        // // Выводим обычным текстом содержание буфера
	#endif
				
        break;
        // -----------------------------------------
				
				// -----------------------------------------
			case 0x0B:
        sprintf(lcd_buf, LANG_DOSE5MONTH);      // Пишем в буфер значение счетчика
        LcdString(1, 4);        // // Выводим обычным текстом содержание буфера

        if(flash_read_massive(doze_length_5month, dose_select) > 0)     // неделя
        {
          if(!Settings.units)
          {
            sprintf(lcd_buf, LANG_9UMKR, ((Data.Doze_5month_count * (Settings.Second_count >> 2)) / 900));      // Пишем в буфер значение счетчика
          } else
          {
            sprintf(lcd_buf, LANG_9UMKZV, convert_mkr_sv((Data.Doze_5month_count * (Settings.Second_count >> 2)) / 900));       // Пишем в буфер значение счетчика
          }
        } else
        {
          sprintf(lcd_buf, LANG_DOSECALC);      // Пишем в буфер значение счетчика
        }
				
	#ifdef DISPLAY_SSD1306
        LcdString(9, 4);        // // Выводим обычным текстом содержание буфера
	#endif

	#ifdef DISPLAY_CH1115
        LcdString(1, 5);        // // Выводим обычным текстом содержание буфера
	#endif
				
        break;
        // -----------------------------------------
				
				// -----------------------------------------
			case 0x0C:
        sprintf(lcd_buf, LANG_DOSEALLTIME, Data.working_days);      // Пишем в буфер значение счетчика
        LcdString(1, 4);        // // Выводим обычным текстом содержание буфера
				if(Data.working_days > 0)        // День
					{
						if(!Settings.units)
						{
							sprintf(lcd_buf, LANG_9UMKR, Data.Doze_all_time);      // Пишем в буфер значение счетчика
						} else
						{
							sprintf(lcd_buf, LANG_9UMKZV, convert_mkr_sv(Data.Doze_all_time));       // Пишем в буфер значение счетчика
						}
					} else
					{
						sprintf(lcd_buf, LANG_DOSECALC);      // Пишем в буфер значение счетчика
					}
				
	#ifdef DISPLAY_SSD1306
        LcdString(9, 4);        // // Выводим обычным текстом содержание буфера
	#endif

	#ifdef DISPLAY_CH1115
        LcdString(1, 5);        // // Выводим обычным текстом содержание буфера
	#endif
				
        break;
        // -----------------------------------------
					
				// -----------------------------------------
	#ifdef DISPLAY_SSD1306
			case 0x0D:
				if((Settings.Second_count / 4) > 100)
				{
					Draw_fon_graph(2, 126, 3, 29, SMALL_SIZE, Detector_massive, Detector_massive_pointer, NORMAL);
				} else
				{
					Draw_fon_graph(2, 126, 3, 29, BIG_SIZE, Detector_massive, Detector_massive_pointer, NORMAL);
				}
        break;
	#endif
        // -----------------------------------------
#endif
				
#ifdef STM_15XCBX
				// -----------------------------------------
			case 0x09:
        sprintf(lcd_buf, LANG_DOSEALLTIME, Data.working_days);      // Пишем в буфер значение счетчика
        LcdString(1, 4);        // // Выводим обычным текстом содержание буфера
				if(Data.working_days > 0)        // День
					{
						if(!Settings.units)
						{
							sprintf(lcd_buf, LANG_9UMKR, Data.Doze_all_time);      // Пишем в буфер значение счетчика
						} else
						{
							sprintf(lcd_buf, LANG_9UMKZV, convert_mkr_sv(Data.Doze_all_time));       // Пишем в буфер значение счетчика
						}
					} else
					{
						sprintf(lcd_buf, LANG_DOSECALC);      // Пишем в буфер значение счетчика
					}
				
	#ifdef DISPLAY_SSD1306
        LcdString(9, 4);        // // Выводим обычным текстом содержание буфера
	#endif

	#ifdef DISPLAY_CH1115
        LcdString(1, 5);        // // Выводим обычным текстом содержание буфера
	#endif
				
        break;
        // -----------------------------------------
					
				// -----------------------------------------
	#ifdef DISPLAY_SSD1306
			case 0x0A:
				if((Settings.Second_count / 4) > 100)
				{
					Draw_fon_graph(2, 126, 3, 29, SMALL_SIZE, Detector_massive, Detector_massive_pointer, NORMAL);
				} else
				{
					Draw_fon_graph(2, 126, 3, 29, BIG_SIZE, Detector_massive, Detector_massive_pointer, NORMAL);
				}
        break;
	#endif
        // -----------------------------------------
#endif
				
      default:
        break;
      }
    } else
    {
      // Режим "Замер А-В"
      if(Settings.AB_mode > 0)
				{
				
#ifdef DISPLAY_SSD1306
        Draw_fon_digit(2, 3, 0, Data.fon_level, BETA, 0);//Draw_fon_digit(4, 1, 0, Data.fon_level, BETA, 0); TEST
#endif
					
#ifdef DISPLAY_CH1115
        Draw_fon_digit(4, 1, 0, Data.fon_level, BETA, 0);
#endif
					
				}
    }

    if(Settings.Cal_mode == 1)
    {
      sprintf(lcd_buf, "%2i  %5i", Cal_count, Cal_count_time);  // Пишем в буфер значение счетчика
      LcdString(1, 1);          // // Выводим обычным текстом содержание буфера

      sprintf(lcd_buf, LANG_FON_UMKZV, convert_mkr_sv(Data.Cal_count_mass[Cal_count])); // Пишем в буфер значение счетчика
      LcdString(1, 2);          // // Выводим обычным текстом содержание буфера    
    } else
    {
			
#ifdef DISPLAY_SSD1306
			if(Settings.AB_mode == 0)
			{
				
#ifdef STM_15XCCX
				if(Data.main_menu_stat != 0x0D)
#endif
				
#ifdef STM_15XCBX
				if(Data.main_menu_stat != 0x0A)
#endif
				{
					if(!Settings.units)
					{
						Draw_fon_digit(1, 1, 0, Data.fon_level, MKRH, 1);
					} else
					{
						Draw_fon_digit(1, 1, 0, Data.fon_level, SIVERT, 1);
					}
				}
			}
#endif
		
#ifdef DISPLAY_CH1115
			if(!Settings.units)
      {
        Draw_fon_digit(1, 1, 0, Data.fon_level, MKRH, 1);
      } else
      {
        Draw_fon_digit(1, 1, 0, Data.fon_level, SIVERT, 1);
      }
#endif
			
    }
		
#ifdef DISPLAY_CH1115
    if((Settings.Second_count / 4) > 100)
    {
      Draw_fon_graph(2, 126, 42, 61, SMALL_SIZE, Detector_massive, Detector_massive_pointer, NORMAL);
    } else
    {
      Draw_fon_graph(2, 126, 42, 61, BIG_SIZE, Detector_massive, Detector_massive_pointer, NORMAL);
    }
#endif

#ifdef DISPLAY_SSD1306
		
		#ifdef STM_15XCBX
    if(Data.auto_speedup_factor > 1 && Data.main_menu_stat != 0x0A)//TEST if(Data.auto_speedup_factor > 1)
		#endif
		
		#ifdef STM_15XCCX
    if(Data.auto_speedup_factor > 1 && Data.main_menu_stat != 0x0D)//TEST if(Data.auto_speedup_factor > 1)
		#endif
		
#endif
		
#ifdef DISPLAY_CH1115
    if(Data.auto_speedup_factor > 1)//TEST if(Data.auto_speedup_factor > 1)
#endif
		
    {
      Draw_speedup(2, 94, 67 - 25, 67);
      sprintf(lcd_buf, "x%2u", Data.auto_speedup_factor);       // Пишем в буфер значение счетчика
      LcdString(12, 3);         // // Выводим обычным текстом содержание буфера
    }
  } /*else
  {
    amodul_screen();
  }*/ //TEST

  LcdUpdate();                  // записываем данные из сформированного фрейм-буфера на дисплей
}

//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
/*void amodul_screen()
{
  uint32_t epsi = 100;
	uint32_t battery_procent;

  if(Settings.AMODUL_menu == 0)
  {
    sprintf(lcd_buf, LANG_AMODUL);      // Пишем в буфер значение счетчика
    LcdString(1, 1);            // // Выводим обычным текстом содержание буфера


    epsi = precision_measure();

    switch (Settings.AMODUL_unit)
    {
    case 0:
      Draw_fon_digit(2, 1, 0, Data.fonmodule, QUANT, 0);

      if(epsi >= 999)
        epsi = 999;
      if(epsi < 100)
      {
        sprintf(lcd_buf, "  '%1u.%1u%%", epsi / 10, epsi % 10); // Пишем в буфер значение счетчика
      } else
      {
        sprintf(lcd_buf, " '%2u.%1u%%", epsi / 10, epsi % 10);  // Пишем в буфер значение счетчика
      }
      LcdStringBold(1, 4);      // // Выводим обычным текстом содержание буфера


      // Индикация батарейки и выключение питания при разряде
      if(ADCData.Batt_voltage < 3500)
        minus_poweroff(0x00);   // Если меньше 3.5В выключаем прибор.
			
			battery_procent = ADCData.Batt_voltage;
      battery_procent -= 3500;
      battery_procent /= 5;
      LcdBatt(84, 19 + 7, 84 + 10, 19 + 19 + 1, battery_procent);
			

      Draw_fon_graph(2, 94, 67 - 25, 67, BIG_SIZE, Data.AMODULE_fon, 0, MODUL);

      break;
    case 1:
      Draw_fon_digit(2, 1, 0, Data.fonmodule, SIVERT, 0);

      if(epsi >= 999)
        epsi = 999;
      if(epsi < 100)
      {
        sprintf(lcd_buf, "  '%1u.%1u%%", epsi / 10, epsi % 10); // Пишем в буфер значение счетчика
      } else
      {
        sprintf(lcd_buf, " '%2u.%1u%%", epsi / 10, epsi % 10);  // Пишем в буфер значение счетчика
      }
      LcdStringBold(1, 4);      // // Выводим обычным текстом содержание буфера


      // Индикация батарейки и выключение питания при разряде
      if(ADCData.Batt_voltage < 3500)
        minus_poweroff(0x00);   // Если меньше 3.5В выключаем прибор.
			
			battery_procent = ADCData.Batt_voltage;
      battery_procent -= 3500;
      battery_procent /= 5;
      LcdBatt(84, 19 + 7, 84 + 10, 19 + 19 + 1, battery_procent);
      //LcdBatt(84, 19 + 7, 84 + 10, 19 + 19 + 1, cal_read(ADCData.Batt_voltage));



      Draw_fon_graph(2, 94, 67 - 25, 67, BIG_SIZE, Data.AMODULE_fon, 0, MODUL);

      break;
    case 2:

      Draw_fon_digit(2, 1, 0, Data.AMODULE_find_summ, SIVERT, 0);
      Draw_fon_digit(4, 1, 0, Data.fonmodule, SIVERT, 0);

      Draw_fon_graph(2, 94, 67 - 25, 67, BIG_SIZE, Data.AMODULE_fon, 0, MODUL);

      break;
			case 3://TEST было закоменчено

      sprintf(lcd_buf, LANG_SPECT_MARK_TEXT1);  // Пишем в буфер значение счетчика
      LcdString(1, 1);          // // Выводим обычным текстом содержание буфера
      sprintf(lcd_buf, LANG_SPECT_MARK_TEXT2);  // Пишем в буфер значение счетчика
      LcdString(1, 2);          // // Выводим обычным текстом содержание буфера
      sprintf(lcd_buf, LANG_SPECT_MARK_TEXT3);  // Пишем в буфер значение счетчика
      LcdString(1, 3);          // // Выводим обычным текстом содержание буфера
      Draw_fon_graph(2, 96, 67 - 38, 67, SMALL_SIZE, Data.AMODULE_len, 0, SPECTR);

      break;
 }
  } else
  {
    menu_screen(AMODUL_menu_mode);
  }
}*/

//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// Отрисовка меню
void menu_screen(uint32_t mode)
{
  char para_string[21];
  char tmp_string[21];
  uint16_t menu_page, i, j, max_element, selects_menu;

  ////////////////////////////////////////////
  // Выбор массива для обработки
  MenuItem *structures = NULL;

  if(mode == NORMAL_menu_mode)
  {
    if(hidden_menu)
    {
      max_element = max_struct_index;
    } else
    {
      max_element = max_public_string_count;
    }
    structures = Menu_list;
    selects_menu = Data.menu_select;
  }

  if(mode == AMODUL_menu_mode)
  {
    max_element = modul_max_struct_index;
    structures = Modul_Menu_list;
    selects_menu = Data.modul_menu_select;
  }
  ////////////////////////////////////////////


  //прорисовка меню
  sprintf(lcd_buf, LANG_MENU);
  LcdStringInv(1, 1);
  if(selects_menu == 0)
  {
    menu_page = 0;
  } else
  {

    if(mode == NORMAL_menu_mode)
    {
      if(hidden_menu)
      {
        menu_page = (Data.menu_select - 1) / (max_string_count - start_offset); // РѕРїСЂРµРґРµР»РµРЅРёРµ СЃС‚СЂР°РЅРёС†С‹ РјРµРЅСЋ (РїРѕР»РЅРѕРµ)
      } else
      {
        if(Data.menu_select <= max_public_string_count)
        {
          menu_page = (Data.menu_select - 1) / (max_string_count - start_offset);       // РѕРїСЂРµРґРµР»РµРЅРёРµ СЃС‚СЂР°РЅРёС†С‹ РјРµРЅСЋ (РџСѓР±Р»РёС‡РЅРѕРµ)
        } else
        {
          menu_page = 0;
        }
      }
    }

    if(mode == AMODUL_menu_mode)
    {
      if(selects_menu <= max_element)
      {
        menu_page = (selects_menu - 1) / (max_string_count - start_offset);     // определение страницы меню (Публичное)
      } else
      {
        menu_page = 0;
      }
    }
  }


  for (i = 0; i < (max_string_count - start_offset); i++)
  {
    uint32_t fill_len = 0;
    uint32_t para_len = 0;
    uint32_t text_len = 0;
    uint32_t menu_struct_index = 0;
    float tmp;
    uint32_t tmpi;
    menu_struct_index = (menu_page * (max_string_count - start_offset)) + i;    // вычисление адеса в структуре

    if((menu_struct_index >= max_element) && (!hidden_menu) && (mode == NORMAL_menu_mode))
      break;
    if(menu_struct_index >= max_element)
      break;                    // если меню кончилось
    // определение размера строки, таким образом чтобы параметр помещался целиком на строку вместе с аргументом (смещение по правому краю)
    // вычисляем значение параметра "10сек"
    switch (*structures[menu_struct_index].Parameter_value)
    {
    case 0:                    // если значение параметра равно нулю, ищем нет ли макроподстановки на этот случай
      if(structures[menu_struct_index].Param_is_0[0] != '\0')
      {
        sprintf(para_string, structures[menu_struct_index].Param_is_0);
        break;
      }

    case 1:                    // если значение параметра равен еденице, ищем нет ли макроподстановки на этот случай
      if(structures[menu_struct_index].Param_is_1[0] != '\0')
      {
        sprintf(para_string, structures[menu_struct_index].Param_is_1);
        break;
      }

    default:                   // во всех остальных случиях выводим по шаблону
      sprintf(para_string, structures[menu_struct_index].Param_is_N, *structures[menu_struct_index].Parameter_value);
      break;
    }

    // Заплатка на тревогу
    if(mode == AMODUL_menu_mode)
      if((menu_struct_index == 0) && (Settings.AMODUL_mode != 0))
        sprintf(para_string, LANG_UMKZV, convert_mkr_sv(*structures[menu_struct_index].Parameter_value));
    if(mode == NORMAL_menu_mode)
      if((menu_struct_index == 0) && Settings.units)
        sprintf(para_string, LANG_UMKZV, convert_mkr_sv(*structures[menu_struct_index].Parameter_value));



    // Заплатка на изотоп
    if(((menu_struct_index == 1) && (mode == AMODUL_menu_mode)) || ((menu_struct_index == 9) && (mode == NORMAL_menu_mode)))
    {
      tmpi = *structures[menu_struct_index].Parameter_value;
      switch (tmpi)
      {
      case 0x0:
        sprintf(para_string, LANG_ISOTOP_CS137);
        break;
      case 0x1:
        sprintf(para_string, LANG_ISOTOP_EU152);
        break;
      case 0x2:
        sprintf(para_string, LANG_ISOTOP_NA22);
        break;
      case 0x3:
        sprintf(para_string, LANG_ISOTOP_CD109);
        break;
      case 0x4:
        sprintf(para_string, LANG_ISOTOP_AM241);
        break;
      case 0x5:
        sprintf(para_string, LANG_ISOTOP_Y88);
        break;
      case 0x6:
        sprintf(para_string, LANG_ISOTOP_TI44);
        break;
      case 0x7:
        sprintf(para_string, LANG_ISOTOP_BA133);
        break;
      case 0x8:
        sprintf(para_string, LANG_ISOTOP_TH228);
        break;
      }
    }
    // Заплатка на бета окно
    if((menu_struct_index == 16) && (mode == NORMAL_menu_mode))
    {
      tmp = *structures[menu_struct_index].Parameter_value;
      tmp = tmp / 10;
      sprintf(para_string, LANG_BWINDOW_, tmp);
    }


    para_len = strlen(para_string);     // длинна параметра
    text_len = strlen(structures[menu_struct_index].Text);      // линна текста
    fill_len = max_string_len - para_len - text_len;    // сколько добавлять пустых символов
    sprintf(tmp_string, structures[menu_struct_index].Text);    // пишем текст сначала             "Сон"
    for (j = 0; j < fill_len; j++)
      strcat(tmp_string, " ");  // добиваем пробелами посередине   "Сон      "
    // вывод на экран
    // если курсор на пункте, то подсвечиваем. Но если мы вошли в пункт меню, то подсвечиваем только значение
    sprintf(lcd_buf, tmp_string);       // готовим к выводу на экран "Сон      "
    if(selects_menu == menu_struct_index + 1 && Data.enter_menu_item == DISABLE)        // Определение подсветки
    {
      LcdStringInv(1, i + start_offset + 1);
    } else
    {
      LcdString(1, i + start_offset + 1);
    }

    sprintf(lcd_buf, para_string);      // готовим к выводу на значения "10 сек"
    if(selects_menu == menu_struct_index + 1)   // Определение подсветки
    {
      LcdStringInv(1 + text_len + fill_len, i + start_offset + 1);
    } else
    {
      LcdString(1 + text_len + fill_len, i + start_offset + 1);
    }

  }

//**********************************************************************************************

  LcdUpdate();
}

//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
void stat_screen()
{
  switch (Data.stat_screen_number)
  {
  case 0:

#ifdef DISPLAY_SSD1306
    sprintf(lcd_buf, LANG_STAT);
    LcdStringInv(1, 1);
    sprintf(lcd_buf, LANG_VOLTAGE_PUMP);     // Выводим на дисплей
    LcdString(1, 2);            // // Выводим обычным текстом содержание буфера на строку 8
    sprintf(lcd_buf, LANG_AKB3VVV_IMP);     // Выводим на дисплей
    LcdString(1, 3);            // // Выводим обычным текстом содержание буфера на строку 8
    //sprintf(lcd_buf, "%3i%%", cal_read(ADCData.Batt_voltage));  // Выводим на дисплей
    sprintf(lcd_buf, "%1i.%02i", ADCData.Batt_voltage / 1000, (ADCData.Batt_voltage % 1000) / 10);      // Выводим на дисплей
    LcdString(1, 4);            // // Выводим обычным текстом содержание буфера на строку 8
    sprintf(lcd_buf, "|%1i.%02i", ADCData.Power_voltage / 1000, (ADCData.Power_voltage % 1000) / 10);   // Выводим на дисплей
    LcdString(5, 4);            // // Выводим обычным текстом содержание буфера на строку 8
    sprintf(lcd_buf, "|%3is", Settings.Second_count);   // Выводим на дисплей
    LcdString(10, 4);           // // Выводим обычным текстом содержание буфера на строку 8
    //sprintf(lcd_buf, LANG_PUMP);        // Выводим на дисплей
    //LcdString(1, 6);            // // Выводим обычным текстом содержание буфера на строку 8
   // sprintf(lcd_buf, LANG_IMPMINAR);    // Выводим на дисплей
    //LcdString(1, 7);            // // Выводим обычным текстом содержание буфера на строку 8
    if(PumpData.pump_counter_avg_impulse_by_1sec[1] == 0)
    {
      sprintf(lcd_buf, LANG_CALC2);
    }                           // Выводим на дисплей
    else
      sprintf(lcd_buf, "%5i ", PumpData.pump_counter_avg_impulse_by_1sec[1]);   // Выводим на дисплей
    LcdString(16, 4);            // // Выводим обычным текстом содержание буфера на строку 8
    //sprintf(lcd_buf, LANG_4IDN, Data.working_days);     // Выводим на дисплей
    //LcdString(9, 8);            // // Выводим обычным текстом содержание буфера на строку 8
#endif
		
#ifdef DISPLAY_CH1115
    sprintf(lcd_buf, LANG_STAT);
    LcdStringInv(1, 1);
    sprintf(lcd_buf, LANG_VOLTAGE);     // Выводим на дисплей
    LcdString(1, 2);            // // Выводим обычным текстом содержание буфера на строку 8
    sprintf(lcd_buf, LANG_AKB3VVV);     // Выводим на дисплей
    LcdString(1, 3);            // // Выводим обычным текстом содержание буфера на строку 8
    sprintf(lcd_buf, "%1i.%02i", ADCData.Batt_voltage / 1000, (ADCData.Batt_voltage % 1000) / 10);      // Выводим на дисплей
    LcdString(1, 4);            // // Выводим обычным текстом содержание буфера на строку 8
    sprintf(lcd_buf, "|%1i.%02i", ADCData.Power_voltage / 1000, (ADCData.Power_voltage % 1000) / 10);   // Выводим на дисплей
    LcdString(8, 4);            // // Выводим обычным текстом содержание буфера на строку 8
    sprintf(lcd_buf, "|%3is", Settings.Second_count);   // Выводим на дисплей
    LcdString(16, 4);           // // Выводим обычным текстом содержание буфера на строку 8
    sprintf(lcd_buf, LANG_PUMP);        // Выводим на дисплей
    LcdString(1, 6);            // // Выводим обычным текстом содержание буфера на строку 8
    sprintf(lcd_buf, LANG_IMPMINAR);    // Выводим на дисплей
    LcdString(1, 7);            // // Выводим обычным текстом содержание буфера на строку 8
    if(PumpData.pump_counter_avg_impulse_by_1sec[1] == 0)
    {
      sprintf(lcd_buf, LANG_CALC2);
    }                           // Выводим на дисплей
    else
      sprintf(lcd_buf, "%5i ", PumpData.pump_counter_avg_impulse_by_1sec[1]);   // Выводим на дисплей
    LcdString(1, 8);            // // Выводим обычным текстом содержание буфера на строку 8
    sprintf(lcd_buf, LANG_4IDN, Data.working_days);     // Выводим на дисплей
    LcdString(10, 8);            // // Выводим обычным текстом содержание буфера на строку 8
#endif
		
    break;
  case 1:

#ifdef DISPLAY_SSD1306
    sprintf(lcd_buf, LANG_ABOUT);
    LcdStringInv(1, 1);
    sprintf(lcd_buf, LANG_DOZIK);
    LcdString(1, 2);
    sprintf(lcd_buf, LANG_AUTHOR);
    LcdString(1, 3);
    sprintf(lcd_buf, LANG_BUILD);
    LcdString(1, 4);
    sprintf(lcd_buf, " %s", __DATE__);
    LcdString(10, 4);
#endif
	
#ifdef DISPLAY_CH1115
		sprintf(lcd_buf, LANG_ABOUT);
    LcdStringInv(1, 1);
    sprintf(lcd_buf, LANG_DOZIK);
    LcdString(1, 3);
    sprintf(lcd_buf, LANG_AUTHOR);
    LcdString(1, 4);
    sprintf(lcd_buf, LANG_CITY);
    LcdString(1, 5);
    sprintf(lcd_buf, LANG_SITE);
    LcdString(1, 6);
    sprintf(lcd_buf, LANG_BUILD);
    LcdString(1, 7);
    sprintf(lcd_buf, "     %s", __DATE__);
    LcdString(6, 8);
#endif

    break;
  default:
    Data.stat_screen_number = 0;
    break;
  }
  LcdUpdate();
}

//////////////////////////////////////////////////////////////////////////////////////////////////
