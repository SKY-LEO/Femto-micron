#include "my_spi.h"
#include <stm32l1xx_gpio.h>
#include <stm32l1xx_spi.h>
#include <stm32l1xx_rcc.h>

void my_spi_init()
{
	SPI_InitTypeDef SPI_InitStruct;
	GPIO_InitTypeDef InitStruct;
	
	// Стартуем тактирование SPI
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	
	// Настраиваем SPI
	SPI_Cmd(SPI1, DISABLE);
	
	SPI_InitStruct.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 0x7;
	SPI_Init(SPI1, &SPI_InitStruct);
	SPI_Cmd(SPI1, ENABLE);

	// Настраиваем ноги GPIO для сигналов SCK и MOSI
	InitStruct.GPIO_Mode = GPIO_Mode_AF;
	InitStruct.GPIO_OType = GPIO_OType_PP;
	InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_Init(GPIOA, &InitStruct);

	// Настраиваем ножку GPIO для сигнала MISO
	InitStruct.GPIO_Mode = GPIO_Mode_IN;
	InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOA, &InitStruct);
}

void SPI_send(unsigned char data)
{
	SPI_I2S_SendData(SPI1, data);
}
