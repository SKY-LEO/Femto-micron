#include <stdio.h>
#include "font5x8.h"
#include "main.h"
#include "delay.h"
#include "smallssd1306.h"
#include "lang.h"
#include "my_spi.h"


char lcd_buf[20];               // текстовый буфер для вывода на LCD
unsigned char LcdCache[LCD_CACHSIZE];   // Фреймбуфер
unsigned int LcdCacheIdx = 0;   // Текущий адрес во фреймбуфере

void display_on()               // Инициализация порта LCD дисплея
{
	GPIO_InitTypeDef GPIO_InitStructure;


	Power.Display_active = ENABLE;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	// ===============================================================================================  
	// LCD дисплей
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	my_spi_init();

	delay_ms(10);

	LcdInit();                    // Инициализируем дисплей
	LcdClear();
}


void LcdInit()
{
	//ресетим дисплей
	// CS = High (not selected)
	LCD_CS_H; //HAL_GPIO_WritePin(SSD1306_CS_Port, SSD1306_CS_Pin, GPIO_PIN_SET);
	// Reset the OLED
	LCD_RST_L; //HAL_GPIO_WritePin(SSD1306_Reset_Port, SSD1306_Reset_Pin, GPIO_PIN_RESET);
	delay_ms(10); //HAL_Delay(10);
	LCD_RST_H; //HAL_GPIO_WritePin(SSD1306_Reset_Port, SSD1306_Reset_Pin, GPIO_PIN_SET);
	delay_ms(10); //HAL_Delay(10);


	// Wait for the screen to boot
	delay_ms(100); //HAL_Delay(100);

	// Init OLED
	ssd1306_SetDisplayOn(0); //display off

	LcdSend(0x20, lcd_CMD); //Set Memory Addressing Mode
	LcdSend(0x00, lcd_CMD); // 00b,Horizontal Addressing Mode; 01b,Vertical Addressing Mode;
	// 10b,Page Addressing Mode (RESET); 11b,Invalid

	LcdSend(0xB0, lcd_CMD); //Set Page Start Address for Page Addressing Mode,0-7

#ifdef SSD1306_MIRROR_VERT
	LcdSend(0xC0, lcd_CMD); // Mirror vertically
#else
	LcdSend(0xC8, lcd_CMD); //Set COM Output Scan Direction
#endif

	LcdSend(0x00, lcd_CMD); //---set low column address
	LcdSend(0x10, lcd_CMD); //---set high column address

	LcdSend(0x40, lcd_CMD); //--set start line address - CHECK

	//установка контраста
	LcdSend(0x81, lcd_CMD);
	LcdSend(0xFF, lcd_CMD);//от 0x00 до 0xFF LcdSend(0x96 + Settings.contrast, lcd_CMD)
	//
	

#ifdef SSD1306_MIRROR_HORIZ
	LcdSend(0xA0, lcd_CMD); // Mirror horizontally
#else
	LcdSend(0xA1, lcd_CMD); //--set segment re-map 0 to 127 - CHECK
#endif

#ifdef SSD1306_INVERSE_COLOR
	LcdSend(0xA7, lcd_CMD); //--set inverse color
#else
	LcdSend(0xA6, lcd_CMD); //--set normal color
#endif

	// Set multiplex ratio.
#if (SSD1306_HEIGHT == 128)
	// Found in the Luma Python lib for SH1106.
	LcdSend(0xFF, lcd_CMD);
#else
	LcdSend(0xA8, lcd_CMD); //--set multiplex ratio(1 to 64) - CHECK
#endif

#if (SSD1306_HEIGHT == 32)
	LcdSend(0x1F, lcd_CMD); //
#elif (SSD1306_HEIGHT == 64)
	LcdSend(0x3F, lcd_CMD); //
#elif (SSD1306_HEIGHT == 128)
	LcdSend(0x3F, lcd_CMD); // Seems to work for 128px high displays too.
#else
#error "Only 32, 64, or 128 lines of height are supported!"
#endif

	LcdSend(0xA4, lcd_CMD); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content

	LcdSend(0xD3, lcd_CMD); //-set display offset - CHECK
	LcdSend(0x00, lcd_CMD); //-not offset

	LcdSend(0xD5, lcd_CMD); //--set display clock divide ratio/oscillator frequency
	LcdSend(0xF0, lcd_CMD); //--set divide ratio

	LcdSend(0xD9, lcd_CMD); //--set pre-charge period
	LcdSend(0x22, lcd_CMD); //

	LcdSend(0xDA, lcd_CMD); //--set com pins hardware configuration - CHECK
#if (SSD1306_HEIGHT == 32)
	LcdSend(0x02, lcd_CMD);
#elif (SSD1306_HEIGHT == 64)
	LcdSend(0x12, lcd_CMD);
#elif (SSD1306_HEIGHT == 128)
	LcdSend(0x12, lcd_CMD);
#else
#error "Only 32, 64, or 128 lines of height are supported!"
#endif

	LcdSend(0xDB, lcd_CMD); //--set vcomh
	LcdSend(0x20, lcd_CMD); //0x20,0.77xVcc

	LcdSend(0x8D, lcd_CMD); //--set DC-DC enable
	LcdSend(0x14, lcd_CMD); //
	ssd1306_SetDisplayOn(1); //--turn on SSD1306 panel


	// Clear screen
	//ssd1306_Fill();

	// Flush buffer to screen
	//ssd1306_UpdateScreen();
}

void ssd1306_SetDisplayOn(const uint8_t on) {
	uint8_t value;
	if (on) {
		value = 0xAF;   // Display on
	}
	else {
		value = 0xAE;   // Display off
	}
	LcdSend(value, lcd_CMD);
}

void LcdSend(uint8_t data, uint8_t cmd) //Sends data to display controller
{
	if (cmd == lcd_CMD)
	{
		LCD_CS_L; //HAL_GPIO_WritePin(SSD1306_CS_Port, SSD1306_CS_Pin, GPIO_PIN_RESET); // select OLED
		LCD_DC_L; //HAL_GPIO_WritePin(SSD1306_DC_Port, SSD1306_DC_Pin, GPIO_PIN_RESET); // command
		SPI_send(data);
		//SPI_I2S_SendData(SPI1, *(&data)); //HAL_SPI_Transmit(&SSD1306_SPI_PORT, (uint8_t*)&byte, 1, HAL_MAX_DELAY);
		LCD_CS_H; //HAL_GPIO_WritePin(SSD1306_CS_Port, SSD1306_CS_Pin, GPIO_PIN_SET); // un-select OLED
	}
	else {
		LCD_CS_L; //HAL_GPIO_WritePin(SSD1306_CS_Port, SSD1306_CS_Pin, GPIO_PIN_RESET); // select OLED
		LCD_DC_H; //HAL_GPIO_WritePin(SSD1306_DC_Port, SSD1306_DC_Pin, GPIO_PIN_SET); // data
		SPI_send(data); //SPI_I2S_SendData(SPI1, *(&data));
		//SPI_send8b(SPI_periph, pBuff, BuffLen); //HAL_SPI_Transmit(&SSD1306_SPI_PORT, buffer, buff_size, HAL_MAX_DELAY);
		LCD_CS_H; //HAL_GPIO_WritePin(SSD1306_CS_Port, SSD1306_CS_Pin, GPIO_PIN_SET); // un-select OLED
		LCD_DC_L;
	}
}

void LcdClear(void)             //Clears the display
{
	int i = 0;

	for (i = 0; i < LCD_CACHSIZE; i++)
		LcdCache[i] = 0;            //забиваем всю память 0(черный цвет)
	LcdUpdate();
}

void LcdUpdate(void)            //Copies the LCD cache into the device RAM
{
	/*int i = 0, j = 0;

	LcdSend(0xB0, lcd_CMD);       //Позицианируем курсор на начало координат
	LcdSend(0x10, lcd_CMD);
	LcdSend(0x00, lcd_CMD);

	for (i = 0; i < (LCD_Y_RES >> 3); i++)        //грузим данные строками (было деление на 8)
		for (j = LCD_X_RES - 1; j >= 0; j--)        //грузим данные столюиками по 8 пикселей
		{
			LcdSend(LcdCache[((i * LCD_X_RES) + j)], lcd_DATA);       //вычисляем адрес в фрейм буфере, и данные от туда грузим в дисплей.
		}
	*/
	int i = 0, j = 0;
	for (i = 0; i < SSD1306_HEIGHT / 8; i++) {
		LcdSend(0xB0 + i, lcd_CMD); // Set the current RAM page address.
		LcdSend(0x00 + SSD1306_X_OFFSET_LOWER, lcd_CMD);
		LcdSend(0x10 + SSD1306_X_OFFSET_UPPER, lcd_CMD); 
		for (j = LCD_X_RES - 1; j >= 0; j--)
		{
			LcdSend(LcdCache[((i * LCD_X_RES) + j)], lcd_DATA);
		}
	}
}

void LcdString(unsigned char x, unsigned char y)        //Displays a string at current cursor location
{
	unsigned char i = 0;

	if (x > 17 || y > 8)
		return;
	LcdGotoXYFont(x, y);
	for (i = 0; i < 17; i++)
		if (lcd_buf[i])
			LcdChr(lcd_buf[i]);
	clean_lcd_buf();
}

void LcdGotoXYFont(unsigned char x, unsigned char y)    //Sets cursor location to xy location. Range: 1,1 .. 14,6
{
	LcdCacheIdx = ((int)(y)-1) * 96 + ((int)(x)-1) * 6;
}

void LcdChr(int ch)             //Displays a character at current cursor location and increment cursor location
{
	char i = 0;
	if (ch > 0x7f)
	{
		for (i = 0; i < 5; i++)
			LcdCache[LcdCacheIdx++] = lcd_font_table_rus[(ch * 5 + (i)-0x3C0)];     //выделяем байт-столбик из символа и грузим в массив - 5 раз
	}
	else
	{
		for (i = 0; i < 5; i++)
			LcdCache[LcdCacheIdx++] = lcd_font_table[(ch * 5 + (i)-0xA0)];  //выделяем байт-столбик из символа и грузим в массив - 5 раз        
	}
	LcdCache[LcdCacheIdx++] = 0x00;       //добавляем пробел между символами
}

void clean_lcd_buf(void)        //очистка текстового буфера
{
	char i = 0;

	for (i = 0; i < 20; i++)
		lcd_buf[i] = 0;
}
