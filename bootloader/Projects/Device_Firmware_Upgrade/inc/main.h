#ifndef __main_user_H
#define __main_user_H


#include "smallssd1306.h"

typedef struct
{
  FunctionalState Need_batt_voltage_update;     // Необходимо обновить данные по напряжению батарейки
  FunctionalState Need_fon_update;      // Необходимо обновить данные по высокому напряжению 
  FunctionalState Need_display_update;  // Необходимо обновить данные по высокому напряжению 
  uint16_t Batt_update_time_counter;    // счетчик таймаута измерения напряжения АКБ
  uint8_t pump_counter_update_time;
  uint16_t doze_sec_count;      // Служебный счетчик для времени дозы
  uint16_t days_sec_count;
  uint16_t doze_count;          // Служебный счетчик для отметки окончания массива дозы
  uint32_t current_flash_page;  // Служебный счетчик для отметки окончания массива дозы
  FunctionalState Need_update_mainscreen_counters;
  FunctionalState Need_erase_flash;
  FunctionalState RTC_tick_update;

} DataUpdateDef;



typedef struct
{
  uint32_t Impulses_to_normal_voltage;  // Импульсов накачки до нормализации напряжения
  FunctionalState Active;       // Активна ли накачка
  uint32_t pump_counter_avg_impulse_by_1sec[2]; // Колличество импульсов накачки

} PumpDataDef;


typedef struct
{
  uint32_t Alarm_level;         // Уровень аларма
  uint32_t Sleep_time;          // время до ухода в сон
  uint32_t contrast;            // Контраст дисплея
  uint32_t Power_comp;          // Уровень потребления
  uint32_t Geiger_voltage;      // Напряжение датчика
  uint32_t Pump_Energy;
  uint32_t Display_reverse;     // переворот дисплея
  uint32_t Sound;               // Звук вкл-выкл
  uint32_t Second_count;
  uint32_t v4_target_pump;
  uint32_t Speedup;
  uint32_t units;
  uint32_t Vibro;
  uint32_t Beta_window;
  uint32_t Beta_procent;
  uint32_t serial0;
  uint32_t serial1;
  uint32_t serial2;
  uint32_t serial3;

  uint32_t Beep_freq;

  uint32_t Cal_mode;
  uint32_t Isotop;

  uint32_t Isotop_counts;

  uint32_t Isotop_count_cs137;
  uint32_t Isotop_count_eu152;
  uint32_t Isotop_count_na22;
  uint32_t Isotop_count_cd109;
  uint32_t Isotop_count_am241;
  uint32_t Isotop_count_y88;
  uint32_t Isotop_count_ti44;
  uint32_t Isotop_count_ba133;
  uint32_t Isotop_count_th228;

  uint32_t Isotop_ACAL_cs137;
  uint32_t Isotop_ACAL_eu152;
  uint32_t Isotop_ACAL_na22;
  uint32_t Isotop_ACAL_cd109;
  uint32_t Isotop_ACAL_am241;
  uint32_t Isotop_ACAL_y88;
  uint32_t Isotop_ACAL_ti44;
  uint32_t Isotop_ACAL_ba133;
  uint32_t Isotop_ACAL_th228;

  uint32_t AMODUL_menu;
  uint32_t AMODUL_Alarm_level;
  uint32_t AMODUL_Alarm_level_raw;

  uint32_t AMODUL_summ_fon;

  uint32_t AMODUL_spect_start;
  uint32_t AMODUL_spect_multi;

  uint32_t AMODUL_spect_mark1;
  uint32_t AMODUL_spect_mark2;
  uint32_t AMODUL_spect_mark3;
  uint32_t AMODUL_spect_mark4;
  uint32_t AMODUL_spect_mark5;


  uint32_t AMODUL_mode;         // 0-выкл 1-Модуль-А
  uint32_t AMODUL_unit;         // 0-Кванты 1-мкЗвч
  uint32_t ACAL_count;
  uint32_t AB_mode;             // 0-выкл 1-гамма 2-альфа-бета
  uint32_t VRef;
  uint32_t Pump_aggressive;
} SettingsDef;


typedef struct
{
  uint32_t Alarm_beep_count;
  uint32_t Tick_beep_count;
  FunctionalState Alarm_active;
  FunctionalState User_cancel;
} AlarmDef;

#ifdef debug
typedef struct
{
  uint32_t total_wakeup;
  uint32_t total_cycle;
  uint32_t tim9_wakeup;
  uint32_t tim10_wakeup;
  uint32_t sensor_wakeup;
  uint32_t rtc_wakeup;
  uint32_t pump_wakeup;
  uint32_t comp_wakeup;
} WakeupDef;
#endif

typedef struct
{
  FunctionalState ADC_active;   // Сейчас работает АЦП
  FunctionalState Pump_active;  // В данный момент идет накачка
  FunctionalState Sound_active; // В данный подается звук
  FunctionalState Display_active;       // Включен дисплей
  FunctionalState USB_active;   // Включен USB
  FunctionalState sleep_now;    // Активность сна

  uint32_t APB1ENR;             //

  uint32_t sleep_time;          //
  FunctionalState Pump_deny;
} PowerDef;


static __IO uint8_t timer_is_reload = 0;        // counts 1ms timeTicks
extern uint16_t key;            // массив нажатых кнопок [012]
extern uint32_t ix;
extern uint32_t ix_update;



// Режим отображения больших цифр
#define QUANT 0
#define SIVERT 1
#define MKRH 2
#define BETA 3

// Размер линий графика
#define SMALL_SIZE 0
#define BIG_SIZE 1

// Режим графика
#define NORMAL 0
#define MODUL 1
#define SPECTR 2

// Режим работы с меню в eeprom
#define READ 0
#define WRITE 1
#define MAIN_MENU 0
#define MODUL_MENU 1

#define max_fon_select 1
#define dose_select 2
#define eeprom_send_data 3


// Команды компаратора
#define INIT_COMP 0
#define ON_COMP 1
#define OFF_COMP 2



extern uint16_t bat_cal_running;


#define Detector_massive_pointer_max 375

extern uint16_t Detector_massive[Detector_massive_pointer_max + 1];

extern uint32_t Detector_AB_massive[15];        // 1 минута, интервалами по 4 сек



#define FLASH_PAGE_SIZE                 0x100   // (НЕ ТРОГАТЬ! развилится оптимизация USB обмена!!)
#define FLASH_START_ADDR                0x0800F000
#define FLASH_END_ADDR                  0x08039400 //0x08041B00 //0x0801FFFF
#define FLASH_MAX_PAGE                  (FLASH_END_ADDR - FLASH_START_ADDR) / FLASH_PAGE_SIZE // 10FFF -> 10F, 32B00 -> 32B, 2A400 -> 2A4
#define FLASH_MAX_ELEMENT               FLASH_MAX_PAGE * (FLASH_PAGE_SIZE >> 3) //10F * 20 = 21E0 = 8672, 32B * 20 = 6560 = 25952, 2A4 * 20 = 5480 = 21632

#define doze_length_10m       1 // 10 минут
#define doze_length_hour      6 // 1 час    интервалами по 10 минут 60/10
#define doze_length_day     144 // 1 день   интервалами по 10 минут (60/10)*24
#define doze_length_week   1008 // 1 неделя интервалами по 10 минут (60/10)*24*7
#define doze_length_month  4320 // 1 месяц  интервалами по 10 минут (60/10)*24*30
#define doze_length_2month 8640 // 2 месяца интервалами по 10 минут (60/10)*24*30*2
#define doze_length_3month 12960 // 3 месяца интервалами по 10 минут (60/10)*24*30*3
#define doze_length_4month 17280 // 4 месяца интервалами по 10 минут (60/10)*24*30*4
#define doze_length_5month 21600 // 5 месяцев интервалами по 10 минут (60/10)*24*30*5
//#define doze_length_6month 25920 // 6 месяцев интервалами по 10 минут (60/10)*24*30*6

#define doze_length 32          // длинна массива в памяти (НЕ ТРОГАТЬ! развилится оптимизация USB обмена!!)




typedef struct
{
// Серийный номер
  uint32_t unlock_0_serial;
  uint32_t unlock_1_serial;
  uint32_t unlock_2_serial;
  uint32_t unlock_3_serial;

// Данные дозы
  uint16_t Doze_sec_count;      // Счет времени для дозы
  uint32_t Doze_day_count;      // Доза за день
  uint32_t Doze_hour_count;     // Доза за час
  uint32_t Doze_week_count;     // Доза за неделю
  uint32_t Doze_month_count;    // Доза за месяц
  uint32_t Doze_2month_count;   // Доза за два месяца
	uint32_t Doze_3month_count;   // Доза за три месяца
	uint32_t Doze_4month_count;   // Доза за четыре месяца
	uint32_t Doze_5month_count;   // Доза за пять месяцев
	//uint32_t Doze_6month_count;   // Доза за шесть месяцев
	uint32_t Doze_all_time;   // Доза за все время


  uint32_t Max_fon;             // Максимум фона

  // Меню
  uint8_t main_menu_stat;
  uint32_t menu_select;
  uint32_t modul_menu_select;
  FunctionalState enter_menu_item;
  uint8_t screen;
  uint8_t stat_screen_number;

  uint32_t fon_level;           // Фон
  uint32_t working_days;        // Наработка дней
  uint8_t auto_speedup_factor;  // Коэфицент ускорения счета фона
  uint32_t madorc_impulse;      // данные для алгоритма MadOrc'а
  uint32_t USB_not_active;      // Активность интерфейса USB
  uint32_t last_count_pump_on_impulse;  //


  uint32_t Cal_count_mass[20];  // Массив данных калибровки



  // Слюдяной датчик
  uint32_t AB_fon;              // Фон Альфа-Бета

  // Модуль-А
  uint32_t fonmodule;
  uint16_t AMODULE_fon[60];     // Массив импульсов по секундам
  uint16_t AMODULE_find[11];    // Массив импульсов по 100 мс.
  uint32_t AMODULE_find_summ;   // Сумма импульсов за одну секунду

  uint32_t AMODULE_timend;      // Время начала импульса с модуля
  uint32_t AMODULE_timstart;    // Время конца импульса с модуля
  uint32_t AMODULE_Capture;
  uint8_t AMODULE_page;
  uint16_t AMODULE_len[100];    // Массив для спектрометра
  uint32_t AMODULE_count;


} DataDef;




extern uint32_t ram_Doze_massive[doze_length + 1];      // 1 ячейка = 10 минут
extern uint32_t ram_max_fon_massive[doze_length + 1];   // 1 ячейка = 10 минут
extern uint16_t USB_maxfon_massive_pointer;
extern uint16_t USB_doze_massive_pointer;
extern uint16_t Detector_massive_pointer;       // Указатель на ячейку в массиве фона

extern FunctionalState pump_on_impulse;

extern FunctionalState spect_impulse;

extern uint32_t Isotop_counts;

extern uint32_t Cal_count;
extern uint32_t Cal_count_time;

extern uint8_t Pump_on_alarm_count;

extern uint16_t eeprom_address;

extern FunctionalState hidden_menu;

extern FunctionalState poweroff_state;
extern uint32_t fullstop;
extern FunctionalState Sound_key_pressed;
extern FunctionalState Pump_on_alarm;
extern uint16_t current_pulse_count;
extern uint8_t pump_count;

//extern ADCDataDef ADCData;
extern DataUpdateDef DataUpdate;
extern PowerDef Power;
extern DataDef Data;
extern SettingsDef Settings;
extern AlarmDef Alarm;
extern PumpDataDef PumpData;

#endif
