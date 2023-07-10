#include <stm32l1xx_gpio.h>
#include <stm32l1xx_spi.h>
#include <stm32l1xx_rcc.h>
#include "test.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++  ++++++++
/* Private variables */

uint8_t GRAM[64/8][128];    // видеопамять размером 1 кБайт

//++++++++++++++++++++++++++++++++++++++++++++++++++  ++++++++
/* Private function prototypes */
void Interface_Init(void);
void Display_Init(void);
void OLED_Write(uint8_t data);
void Switch_to_Command(void);
void Switch_to_Data(void);
void Refresh_frame(void);

//++++++++++++++++++++++++++++++++++++++++++++++++++  ++++++++
/* Private functions */
/*-----------------------------------------------
 * Настройка интерфейса.
 * MOSI    - PB15 AF PP
 * SCK    - PB13 AF PP
 * CS    - PB12 AF PP
 * DC    - PB15    PP
 * SPI2: Master, 8 bit,  Bidir, BidiroutEnable,
 *       1/16, SSM+SSI, SSO
 */
void Interface_Init(void)
{
		SPI_InitTypeDef SPI_InitStruct;
	GPIO_InitTypeDef InitStruct;
	GPIO_InitTypeDef GPIO_InitStructure_CS;
	
	// Стартуем тактирование SPI
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
		// Настраиваем ноги GPIO для сигналов SCK и MOSI
	InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	InitStruct.GPIO_Mode = GPIO_Mode_AF;
	InitStruct.GPIO_OType = GPIO_OType_PP;
	InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIOA, &InitStruct);
	
	GPIO_InitStructure_CS.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure_CS.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure_CS.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure_CS.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure_CS.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure_CS);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
	
	// Настраиваем SPI
	//SPI_Cmd(SPI1, DISABLE);
	SPI_StructInit(&SPI_InitStruct);
	SPI_InitStruct.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStruct);
	SPI_Cmd(SPI1, ENABLE);
}//----------------------------------------------
/*-----------------------------------------------
 * Настройка дисплея, очистка и включение
 */
void Display_Init(void)
{
	uint8_t x,y;
		GPIOA->BSRRH = GPIO_Pin_4;
    Switch_to_Command();    // Переключение в режим команд

    OLED_Write(0x20);        // Ориентация и развертка дисплея
    OLED_Write(0x00);        // автоинкремент страниц, слева направо, сверху вниз

    OLED_Write(0x8D);        // Включение DC/DC
    OLED_Write(0x14);        // конвертера

    Switch_to_Data();        // Переключение в режим данных
    Refresh_frame();        // Очистка дисплея

    Switch_to_Command();    // Переключение в режим команд
    OLED_Write(0xAF);        // Включение дисплея

    Switch_to_Data();        // Переключение в режим данных
	
		 /* чето такое рисуется, сетка какаято */
  for (y=0; y<8; y++)
  {
      for (x=0; x<128; x++)
      {
          if (!(x%8)) GRAM[y][x] = 0xE7;
          else GRAM[y][x] = 0x81;
      }
  }
}//----------------------------------------------
/*-----------------------------------------------
 * отправка байта в дисплей
 */
void OLED_Write(uint8_t data)
{
    while (!(SPI1 ->SR & SPI_SR_TXE)) {}        // Ожидание свободного буфера передачи
    SPI1->DR = data;                        // Запись байта в буфер передачи
}//---------------------------------
/*----------------------------------
 * Переключение в режим команд, DC = 0
 */
void Switch_to_Command(void)
{
    while (SPI1 ->SR & SPI_SR_BSY) {}        // Ожидание завершения передачи
    //GPIOA - ›BSRR = GPIO_BSRR_BR2;            // DC = 0
		GPIOA->BSRRH = GPIO_Pin_2;
}//---------------------------------
/*----------------------------------
 * Переключение в режим данных, DC = 1
 */
void Switch_to_Data(void)
{
    while (SPI1 ->SR & SPI_SR_BSY) {}        // Ожидание завершения передачи
    //GPIOA - ›BSRR = GPIO_BSRR_BS2;            // DC = 1
		GPIOA->BSRRL = GPIO_Pin_2;
		
}//----------------------------------

/*-----------------------------------
 * Перерисовка полного кадра дисплея.
 * Отправляет в дисплей содержимое видеопамти полностью.
 */
void Refresh_frame(void)
{
	uint8_t y, x;
    for (y = 0; y<8; y++)
    {
        for (x = 0; x<128; x++)
        {
            OLED_Write(GRAM[y][x]);            // Отправка байта данных
        }
    }
}//---------------------------------------------- 
