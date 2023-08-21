#include <SSD1306.h>
#include "GFX.h"
#include "delay.h"

/*
 * SSD1306.c
 * Author: Harris Shallcross
 * Year: 2014-ish
 *
 * SSD1306 driver library using the STM32F0 discovery board
 * STM32F0 communicates with OLED display through SPI, pinouts described below.
 *
 * This code is provided AS IS and no warranty is included!
 */

GPIO_InitTypeDef G;
SPI_InitTypeDef S;

void SSD1306_InitSetup(void){
	static uint8_t Init = 1;
	if(Init == 1){
		Init = 0;
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

		G.GPIO_Pin = DC | CE | RS;
		G.GPIO_Mode = GPIO_Mode_OUT;
		G.GPIO_OType = GPIO_OType_PP;
		G.GPIO_PuPd = GPIO_PuPd_UP;
		G.GPIO_Speed = GPIO_Speed_40MHz;
		GPIO_Init(GPIOA, &G);

		G.GPIO_Pin = Clk | DIn;
		G.GPIO_Mode = GPIO_Mode_AF;
		G.GPIO_OType = GPIO_OType_PP;
		G.GPIO_PuPd = GPIO_PuPd_NOPULL;
		G.GPIO_Speed = GPIO_Speed_40MHz;
		GPIO_Init(GPIOA, &G);

		/* Screen power is taken directly from supply!
		G.GPIO_Pin = VCC;
		G.GPIO_OType = GPIO_OType_OD;
		G.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_Init(IOGPIO, &G);
		*/

		GPIO_PinAFConfig(GPIOA, ClkPS, GPIO_AF_SPI1);
		GPIO_PinAFConfig(GPIOA, DInPS, GPIO_AF_SPI1);

		S.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
		S.SPI_CPHA = SPI_CPHA_1Edge;
		S.SPI_CPOL = SPI_CPOL_Low;
		S.SPI_DataSize = SPI_DataSize_8b;
		S.SPI_Direction = SPI_Direction_1Line_Tx;
		S.SPI_FirstBit = SPI_FirstBit_MSB;
		S.SPI_Mode = SPI_Mode_Master;
		S.SPI_NSS = SPI_NSS_Soft;
		SPI_Init(SPI1, &S);
		SPI_Cmd(SPI1, ENABLE);
	}

	//GPIO_ResetBits(IOGPIO, VCC);
	Delay(100);
	GPIO_ResetBits(GPIOA, Clk|DIn|DC|CE|RS);
	Delay(1);
	GPIO_SetBits(GPIOA, RS);
	Delay(1);
	GPIO_ResetBits(GPIOA, RS);
	Delay(1);
	GPIO_SetBits(GPIOA, RS|DC|CE);

	SB(SetMuxRatio, Reg, 1);
	SB(0x3F, Reg, 1);
	SB(SetDispOffset, Reg, 1);
	SB(0x00, Reg, 1);
	SB(SetDispStartLine|0, Reg, 1);
	SB(SetRemap|0, Reg, 1);
	SB(SetComPinHW, Reg, 1);
	SB(0x12, Reg, 1);
	SB(SetComScanDir|0, Reg, 1);

	SB(Contrast, Reg, 1);
	SB(0x7F, Reg, 1);
	SB(MemAddMode, Reg, 1);
	SB(MModeH, Reg, 1);
	SB(SetColAdd, Reg, 1);
	SB(0x00, Reg, 1);
	SB(0x7F, Reg, 1);
	SB(SetPageAdd, Reg, 1);
	SB(0x00, Reg, 1);
	SB(0x07, Reg, 1);

	SB(NormDisp, Reg, 1);
	SB(SetComHLvl, Reg, 1);
	SB(0x00, Reg, 1);

	//SB(DispOnAll, Reg, 1); //Test whole display
	SB(DispOnRAM, Reg, 1);
	SB(SetDispFreq, Reg, 1);
	SB(0x80, Reg, 1);
	SB(ChargePump, Reg, 1);
	SB(0x14, Reg, 1);
	SB(DispOn, Reg, 1);

	ClrBuf();
	PScrn();
}

void SB(uint8_t Data, WMode CmdDat, uint8_t En){
	if(CmdDat == Reg) GPIO_WriteBit(GPIOA, DC, Bit_RESET);
	else GPIO_WriteBit(GPIOA, DC, Bit_SET);

	if(En) GPIO_ResetBits(GPIOA, CE);

	SPI_SendData(SPI1, Data);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);

	if(En) GPIO_SetBits(GPIOA, CE);
}

void LCDScreenMode(LCDScrnMode Mode){
	if(Mode == LCDInv) SB(InvDisp, Reg, 1);
	else SB(NormDisp, Reg, 1);
}

void LCDSleepMode(LCDPwrMode Mode){
	if(Mode == LCDSleep){
		SB(DispOff, Reg, 1);
		SB(ChargePump, Reg, 1);
		SB(0x10, Reg, 1);
	}
	else{
		SB(ChargePump, Reg, 1);
		SB(0x14, Reg, 1);
		SB(DispOn, Reg, 1);
	}
}

extern volatile uint32_t MSec;

void Delay(uint32_t ms){
	delay_ms(ms);
}
