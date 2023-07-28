#ifndef __services_user_H
#define __services_user_H

uint8_t check_wakeup_keys(void);
FunctionalState check_license(void);
float convert_mkr_sv(uint32_t);
void recalculate_fon(void);
void RTC_tick_processing(void);
void sleep_mode(FunctionalState);
void geiger_calc_fon(void);
uint32_t calc_ab(void);
void reload_active_isotop_time(void);
uint32_t precision_measure(void);
void sleep_mode(FunctionalState sleep);
FunctionalState check_license(void);
float convert_mkr_sv(uint32_t);
void check_isotop_time(void);
void clear_sleep_time(void);
void activate_charge_gpio(void);
void deactivate_charge_gpio(void);

#endif
