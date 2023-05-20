#ifndef __pump_user_H
#define __pump_user_H

#include "STM32L1xx.h"          // Device header


void PumpCmd(FunctionalState);
void PumpTimerConfig(void);
void PumpPrescaler(void);
void PumpCompCmd(uint8_t);

#endif
