#ifndef __eeprom_user_H
#define __eeprom_user_H
#include <STM32L1xx.h>


/* Private typedef -----------------------------------------------------------*/
typedef enum
{ FAILED = 0, PASSED = !FAILED } TestStatus;

/* Private define ------------------------------------------------------------*/
#define DATA_EEPROM_START_ADDR     0x08080000
#define DATA_EEPROM_END_ADDR       0x08081FFF
#define DATA_EEPROM_PAGE_SIZE      0x8

#define Batt_cal_massive_address																0x200
#define Batt_cal_massive_end_address														0x5FF

#define second_pump_address                                     0x10
#define Geiger_angle_of_counter_characteristics_address         0x14
#define Geiger_plato_begin_address                              0x1C
#define Geiger_plato_address                                    0x20
#define HV_ADC_Corr_address                                     0x24
#define pump_pulse_by_impulse_address                           0x28
#define pump_skvagennost_address                                0x2C
#define Pump_Energy_address																			0x34
#define Second_count_address																		0x38
#define Sound_freq_address																			0x3C
#define Led_Sleep_time_address                                  0x40
#define Power_comp_address                                			0x48
#define EnergoEfficency_address                              		0x4C

#define VRef_address																		        0x74


// Лицензионный ключ тут
#define unlock_0_address 	                           						0x5C
#define unlock_1_address 	                           						0x60
#define unlock_2_address 	                           						0x64
#define unlock_3_address 	                           						0x68

#define Isotop_count_cs137_address         0x84
#define Isotop_count_eu152_address         0x88
#define Isotop_count_na22_address          0x8C
#define Isotop_count_cd109_address         0x90

#define Isotop_count_am241_address         0xC0
#define Isotop_count_y88_address           0xC8
#define Isotop_count_ti44_address          0xD0
#define Isotop_count_ba133_address         0xD8
#define Isotop_count_th228_address         0xE0

extern uint32_t NbrOfPage, Address;



void eeprom_erase(void);
uint32_t eeprom_read(uint32_t address_of_read);
void eeprom_write(uint32_t, uint32_t);
void eeprom_write_settings(uint32_t);
void eeprom_apply_settings(uint32_t);
void eeprom_write_default_settings(void);
void eeprom_read_settings(uint32_t);
void eeprom_loading(uint32_t);
void cal_write(void);
uint32_t cal_read(uint32_t);

#endif
