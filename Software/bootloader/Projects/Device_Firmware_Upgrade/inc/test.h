#ifndef __test_H
#define __test_H
#include <stm32l1xx_gpio.h>
#include <stm32l1xx_spi.h>
#include <stm32l1xx_rcc.h>

void Interface_Init(void);
void Display_Init(void);
void OLED_Write(uint8_t data);
void Switch_to_Command(void);
void Switch_to_Data(void);
void Refresh_frame(void);
#endif
