#ifndef __keys_user_H
#define __keys_user_H

//////////////////////////////////////////////////////////////////////////////////////////////////
extern void plus_batcal(uint32_t * param);

extern void plus(uint32_t * param);
extern void minus(uint32_t * param);

extern void plus_alarm(uint32_t * param);
extern void minus_alarm(uint32_t * param);

extern void plus_sleep(uint32_t * param);
extern void minus_sleep(uint32_t * param);

extern void plus_on(uint32_t * param);
extern void minus_off(uint32_t * param);

extern void plus_one_ref(uint32_t * param);
extern void minus_one_ref(uint32_t * param);

void plus_doze_reset(uint32_t * param);
void plus_reboot(uint32_t * param);
void minus_poweroff(uint32_t * param);

void usb_activate(uint32_t * param);
void usb_deactivate(uint32_t * param);

void plus_rad_reset(uint32_t * param);

void plus_ab_engage(uint32_t * param);
void plus_amodul_engage(uint32_t * param);
void ab_meas_on(void);
void ab_meas_off(void);

void keys_proccessing(void);

#endif
