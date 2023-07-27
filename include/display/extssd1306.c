#include <stdio.h>
#include "font5x8.h"
#include "main.h"
#include "delay.h"
#include "extssd1306.h"
#include "lang.h"
//#include "my_spi.h"


char lcd_buf[21];               // текстовый буфер для вывода на LCD
unsigned char LcdCache[LCD_CACHSIZE];   // Фреймбуфер
unsigned int LcdCacheIdx = 0;   // Текущий адрес во фреймбуфере


void SPI_send(uint8_t data)
{
	SPI_I2S_SendData(SPI1, data);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
}

void display_on()               // Инициализация порта LCD дисплея
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

	Power.Display_active = ENABLE;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1),
		//GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1), 
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1),

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//	GPIO_WriteBit(SCK_MOSI_PORT, SCK_Pin, Bit_SET);
	//	GPIO_WriteBit(SCK_MOSI_PORT, MOSI_Pin, Bit_SET);
	//	GPIO_WriteBit(SCK_MOSI_PORT, MISO_Pin, Bit_SET);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//	GPIO_WriteBit(CS_RST_PORT, RST_Pin,Bit_SET);
	//	GPIO_WriteBit(CS_RST_PORT, CS_Pin, Bit_SET);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);




	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	//SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	// указываем, что наше устройство - Master
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	// передавать будем по 8 бит (=1 байт)
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	// режим 00
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft | SPI_NSSInternalSoft_Set;//SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	// передаём данные старшим битом вперёд (т.е. слева направо)
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	// внесём настройки в SPI
	//SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Set);
	SPI_Init(SPI1, &SPI_InitStructure);
	// включим  SPI1
	SPI_Cmd(SPI1, ENABLE);
	// ===============================================================================================  
	// LCD дисплей
	/*GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);*/

	//my_spi_init();

	delay_ms(10);

	LcdInit();                    // Инициализируем дисплей
	LcdClear();
}


void display_off()              // Инициализация порта LCD дисплея
{

	GPIO_InitTypeDef GPIO_InitStructure;
	LcdClear();
	ssd1306_SetDisplayOn(0);

	Power.Display_active = DISABLE;

	SPI_Cmd(SPI1, DISABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, DISABLE);

	// ===============================================================================================  
	// LCD дисплей
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, GPIO_InitStructure.GPIO_Pin);   // на землю

	// ===============================================================================================  
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

	if(Settings.Display_reverse == 0x00)
	{
		LcdSend(0xC0, lcd_CMD);
		LcdSend(0xA1, lcd_CMD); //--set segment re-map 0 to 127 - CHECK
	}
	else if (Settings.Display_reverse == 0x01)
	{
		LcdSend(0xC8, lcd_CMD);
		LcdSend(0xA0, lcd_CMD); // Mirror horizontally
	}
/*#ifdef SSD1306_MIRROR_VERT
	LcdSend(0xC0, lcd_CMD); // Mirror vertically
#else
	LcdSend(0xC8, lcd_CMD); //Set COM Output Scan Direction
#endif*/

	LcdSend(0x00, lcd_CMD); //---set low column address
	LcdSend(0x10, lcd_CMD); //---set high column address

	LcdSend(0x40, lcd_CMD); //--set start line address - CHECK

	//установка контраста
	LcdSend(0x81, lcd_CMD);
	LcdSend(0x05 + 0xA * Settings.contrast, lcd_CMD);//от 0x00 до 0xFF LcdSend(0x96 + Settings.contrast, lcd_CMD)
	//


/*#ifdef SSD1306_MIRROR_HORIZ
	LcdSend(0xA0, lcd_CMD); // Mirror horizontally
#else
	LcdSend(0xA1, lcd_CMD); //--set segment re-map 0 to 127 - CHECK
#endif*/

	if(Settings.Display_inverse == 0x00)
	{
		LcdSend(0xA6, lcd_CMD); //--set normal color
	}
	else if(Settings.Display_inverse == 0x01)
	{
		LcdSend(0xA7, lcd_CMD); //--set inverse color
	}
/*#ifdef SSD1306_INVERSE_COLOR
	LcdSend(0xA7, lcd_CMD); //--set inverse color
#else
	LcdSend(0xA6, lcd_CMD); //--set normal color
#endif*/

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
		//LCD_DC_L;
	}
}

void LcdClear(void)             //Clears the display
{
	int i = 0;

	for (i = 0; i < LCD_CACHSIZE; i++)
		LcdCache[i] = 0x00;            //забиваем всю память 0(черный цвет)
	LcdUpdate();
}

void LcdClear_massive(void)     //Clears the display
{
	int i = 0;

	for (i = 0; i < LCD_CACHSIZE; i++)
		LcdCache[i] = 0x00;            //забиваем всю память 0
}


void LcdPixel(unsigned char x, unsigned char y, unsigned char mode)     //Displays a pixel at given absolute (x, y) location, mode -> Off, On or Xor
{
	int index = 0;
	unsigned char offset = 0, data = 0;

	if (x > LCD_X_RES)
		return;                     //если передали в функцию муть - выходим
	if (y > LCD_Y_RES)
		return;

	index = (((int)(y) >> 3) * 128) + x;  //считаем номер байта в массиве памяти дисплея index = (((int)(y) >> 3) * 96) + x; TEST
	offset = y - ((y >> 3) << 3); //считаем номер бита в этом байте

	data = LcdCache[index];       //берем байт по найденному индексу

	if (mode == PIXEL_OFF)
		data &= (~(0x01 << offset));        //редактируем бит в этом байте
	else if (mode == PIXEL_ON)
		data |= (0x01 << offset);
	else if (mode == PIXEL_XOR)
		data ^= (0x01 << offset);

	LcdCache[index] = data;       //загружаем байт назад
}


void LcdLine(int x1, int y1, int x2, int y2, unsigned char mode)        //Draws a line between two points on the display - по Брезенхейму
{
	signed int dy = 0;
	signed int dx = 0;
	signed int stepx = 0;
	signed int stepy = 0;
	signed int fraction = 0;

	if (x1 > LCD_X_RES || x2 > LCD_X_RES || y1 > LCD_Y_RES || y2 > LCD_Y_RES)
		return;

	dy = y2 - y1;
	dx = x2 - x1;
	if (dy < 0)
	{
		dy = -dy;
		stepy = -1;
	}
	else
		stepy = 1;
	if (dx < 0)
	{
		dx = -dx;
		stepx = -1;
	}
	else
		stepx = 1;
	dy <<= 1;
	dx <<= 1;
	LcdPixel(x1, y1, mode);
	if (dx > dy)
	{
		fraction = dy - (dx >> 1);
		while (x1 != x2)
		{
			if (fraction >= 0)
			{
				y1 += stepy;
				fraction -= dx;
			}
			x1 += stepx;
			fraction += dy;
			LcdPixel(x1, y1, mode);
		}
	}
	else
	{
		fraction = dx - (dy >> 1);
		while (y1 != y2)
		{
			if (fraction >= 0)
			{
				x1 += stepx;
				fraction -= dy;
			}
			y1 += stepy;
			fraction += dx;
			LcdPixel(x1, y1, mode);
		}
	}
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

	if (x > 21 || y > 4)//TEST if (x > 17 || y > 8)
		return;
	LcdGotoXYFont(x, y);
	for (i = 0; i < 21; i++)//TEST for (i = 0; i < 17; i++)
		if (lcd_buf[i])
			LcdChr(lcd_buf[i]);
	clean_lcd_buf();
}


void LcdChrBold(int ch)         //Displays a bold character at current cursor location and increment cursor location
{
	unsigned char i = 0;
	unsigned char a = 0, b = 0, c = 0;

	for (i = 0; i < 5; i++)
	{
		if (ch > 0x7f)
		{
			c = lcd_font_table_rus[(ch * 5 + i - 0x3C0)];     //выделяем столбец из символа
		}
		else
		{
			c = lcd_font_table[(ch * 5 + i - 0xA0)];  //выделяем столбец из символа                
		}

		b = (c & 0x01) * 3;         //"растягиваем" столбец на два байта 
		b |= (c & 0x02) * 6;
		b |= (c & 0x04) * 12;
		b |= (c & 0x08) * 24;

		c >>= 4;
		a = (c & 0x01) * 3;
		a |= (c & 0x02) * 6;
		a |= (c & 0x04) * 12;
		a |= (c & 0x08) * 24;

		LcdCache[LcdCacheIdx] = b;  //копируем байты в экранный буфер
		LcdCache[LcdCacheIdx + 1] = b;      //дублируем для получения жирного шрифта
		LcdCache[LcdCacheIdx + 128] = a;//LcdCache[LcdCacheIdx + 96] = a; TEST
		LcdCache[LcdCacheIdx + 129] = a;//LcdCache[LcdCacheIdx + 97] = a; TEST
		LcdCacheIdx = LcdCacheIdx + 2;
	}
	LcdCache[LcdCacheIdx++] = 0x00;       //для пробела между символами
	LcdCache[LcdCacheIdx++] = 0x00;
}

void LcdStringBold(unsigned char x, unsigned char y)    //Displays a string at current cursor location
{
	unsigned char i = 0;
	if (x > 21 || y > 4)//TEST if (x > 17 || y > 8)
		return;
	LcdGotoXYFont(x, y);
	for (i = 0; i < 21 - x; i++)//for (i = 0; i < 17 - x; i++) TEST
		if (lcd_buf[i])
			LcdChrBold(lcd_buf[i]);
	clean_lcd_buf();
}

void LcdChrBig(int ch)          //Displays a character at current cursor location and increment cursor location
{
	unsigned char i = 0;
	unsigned char a = 0, b = 0, c = 0;

	for (i = 0; i < 5; i++)
	{
		if (ch > 0x7f)
		{
			c = lcd_font_table_rus[(ch * 5 + i - 0x3C0)];     //выделяем столбец из символа                       
		}
		else
		{
			c = lcd_font_table[(ch * 5 + i - 0xA0)];  //выделяем столбец из символа
		}

		b = (c & 0x01) * 3;         //"растягиваем" столбец на два байта 
		b |= (c & 0x02) * 6;
		b |= (c & 0x04) * 12;
		b |= (c & 0x08) * 24;

		c >>= 4;
		a = (c & 0x01) * 3;
		a |= (c & 0x02) * 6;
		a |= (c & 0x04) * 12;
		a |= (c & 0x08) * 24;
		LcdCache[LcdCacheIdx] = b;
		LcdCache[LcdCacheIdx + 128] = a;//LcdCache[LcdCacheIdx + 96] = a; TEST
		LcdCacheIdx = LcdCacheIdx + 1;
	}

	LcdCache[LcdCacheIdx++] = 0x00;
}

void LcdStringBig(unsigned char x, unsigned char y)     //Displays a string at current cursor location
{
	unsigned char i = 0;

	if (x > 21 || y > 4)//TEST if (x > 17 || y > 8)
		return;
	LcdGotoXYFont(x, y);
	for (i = 0; i < 21 - x; i++)//for (i = 0; i < 17 - x; i++) TEST
		if (lcd_buf[i])
			LcdChrBig(lcd_buf[i]);
	clean_lcd_buf();
}


void LcdStringInv(unsigned char x, unsigned char y)     //Displays a string at current cursor location
{
	unsigned char i = 0;

	if (x > 21 || y > 4)//TEST if (x > 17 || y > 8)
		return;
	LcdGotoXYFont(x, y);
	for (i = 0; i < 21; i++)//for (i = 0; i < 17 - x; i++) TEST
		if (lcd_buf[i])
			LcdChrInv(lcd_buf[i]);
	clean_lcd_buf();
}


void LcdGotoXYFont(unsigned char x, unsigned char y)    //Sets cursor location to xy location. Range: 1,1 .. 14,6
{
	LcdCacheIdx = ((int)(y)-1) * 128 + ((int)(x)-1) * 6; //LcdCacheIdx = ((int)(y)-1) * 96 + ((int)(x)-1) * 6; TEST
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


void LcdChrInv(int ch)          //Displays a character at current cursor location and increment cursor location
{
	unsigned char i = 0;
	if (ch > 0x7f)
	{
		for (i = 0; i < 5; i++)
			LcdCache[LcdCacheIdx++] = ~(lcd_font_table_rus[(ch * 5 + i - 0x3C0)]);    //выделяем байт-столбик из символа и грузим в массив - 5 раз
	}
	else
	{
		for (i = 0; i < 5; i++)
			LcdCache[LcdCacheIdx++] = ~(lcd_font_table[(ch * 5 + i - 0xA0)]); //выделяем байт-столбик из символа и грузим в массив - 5 раз        
	}
	LcdCache[LcdCacheIdx++] = 0xFF;       //добавляем пробел между символами
}


void clean_lcd_buf(void)        //очистка текстового буфера
{
	char i = 0;

	for (i = 0; i < 21; i++)
		lcd_buf[i] = 0x00;
}


//////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////
void Draw_fon_graph(uint8_t x_start, uint8_t x_end, uint8_t y_start, uint8_t y_end, uint8_t size, uint16_t* massive, uint32_t massive_pointer_val,
	uint32_t spec)
{
	uint32_t x_lenght = 0, y_lenght = 0;
	uint32_t q = 0, i = 0, j = 0, pointer = 0;
	uint32_t scalling_factor = 0;

	LcdClear_massive();//TEST
	for (i = x_start; i <= x_end; i++)
	{
		for (j = y_start; j <= y_end; j++)
		{
			LcdPixel(i, j, 0);
		}
	}

	x_lenght = x_end - x_start;
	y_lenght = y_end - y_start;


	//  if((Settings.Second_count / 4) > 100)
	if (size == SMALL_SIZE)
	{                             // если время счета большое, то рисуем тонкие линии
		scalling_factor = y_lenght / 10;
		for (q = 0; q < x_lenght + 1; q++)
		{
			if (spec == NORMAL)
			{
				if (massive_pointer_val >= q)
				{
					pointer = massive_pointer_val - q;
				}
				else
				{
					pointer = (Settings.Second_count >> 2) - (q - massive_pointer_val);
				}
			}
			else
			{
				pointer = q;
			}

			if (massive[pointer] > scalling_factor)
				scalling_factor = massive[pointer];
		}

		for (q = x_end; q > x_start; q--)
		{
			if (spec == NORMAL)
			{
				if (massive_pointer_val >= (x_end - q))
				{
					pointer = massive_pointer_val - (x_end - q);
				}
				else
				{
					pointer = (Settings.Second_count >> 2) - ((x_end - q) - massive_pointer_val);
				}
				i = massive[pointer];
			}
			else
			{
				i = massive[(x_end - q)];
			}

			if (i > 0)
				LcdLine(x_end - q, y_end, x_end - q, y_end - ((i * y_lenght) / scalling_factor), 1);
		}
	}
	else
	{                             // если время счета маленькое, то рисуем толстые линии
		scalling_factor = y_lenght / 10;
		for (q = 0; q < (x_lenght / 2) + 1; q++)
		{
			if (spec == NORMAL)
			{
				if (massive_pointer_val >= q)
				{
					pointer = massive_pointer_val - q;
				}
				else
				{
					pointer = (Settings.Second_count >> 2) - (q - massive_pointer_val);
				}
			}
			else
			{
				pointer = q;
			}

			if (massive[pointer] > scalling_factor)
				scalling_factor = massive[pointer];
		}

		for (q = x_end; q > x_start; q--)
		{
			if (spec == NORMAL)
			{

				if (massive_pointer_val >= ((x_end - q) / 2))
				{
					pointer = massive_pointer_val - ((x_end - q) / 2);
				}
				else
				{
					pointer = (Settings.Second_count >> 2) - (((x_end - q) / 2) - massive_pointer_val);
				}

				i = 0;
				if (((x_end - q) / 2) < (Settings.Second_count / 4))
					i = massive[pointer];
			}
			else
			{
				i = massive[(x_end - q) / 2];
			}
			if (i > 0)
				LcdLine(x_end - q, y_end, x_end - q, y_end - ((i * y_lenght) / scalling_factor), 1);
		}
	}

	if (spec == SPECTR)
	{
		// Рисуем маркеры над графиком

		LcdLine(Settings.AMODUL_spect_mark1, y_start - 3, Settings.AMODUL_spect_mark1 + 1, y_start - 3, 1);
		LcdLine(Settings.AMODUL_spect_mark1, y_start - 2, Settings.AMODUL_spect_mark1 + 1, y_start - 2, 1);

		LcdLine(Settings.AMODUL_spect_mark2, y_start - 3, Settings.AMODUL_spect_mark2 + 1, y_start - 3, 1);
		LcdLine(Settings.AMODUL_spect_mark2, y_start - 2, Settings.AMODUL_spect_mark2 + 1, y_start - 2, 1);

		LcdLine(Settings.AMODUL_spect_mark3, y_start - 3, Settings.AMODUL_spect_mark3 + 1, y_start - 3, 1);
		LcdLine(Settings.AMODUL_spect_mark3, y_start - 2, Settings.AMODUL_spect_mark3 + 1, y_start - 2, 1);

		LcdLine(Settings.AMODUL_spect_mark4, y_start - 3, Settings.AMODUL_spect_mark4 + 1, y_start - 3, 1);
		LcdLine(Settings.AMODUL_spect_mark4, y_start - 2, Settings.AMODUL_spect_mark4 + 1, y_start - 2, 1);

		LcdLine(Settings.AMODUL_spect_mark5, y_start - 3, Settings.AMODUL_spect_mark5 + 1, y_start - 3, 1);
		LcdLine(Settings.AMODUL_spect_mark5, y_start - 2, Settings.AMODUL_spect_mark5 + 1, y_start - 2, 1);
	}
	//risuem setku
	LcdLine(x_start, y_start, x_start, y_start - 2, 1);
	LcdLine(x_start, y_end, x_start, y_end + 2, 1);

	LcdLine(x_end, y_start, x_end, y_start - 2, 1);
	LcdLine(x_end, y_end, x_end, y_end + 2, 1);

	LcdPixel(x_start, y_start + (y_lenght / 2), 1);
	LcdPixel(x_end, y_start + (y_lenght / 2), 1);

	for (j = x_lenght; j > 0; j--)
	{
		if ((j % 4) == 0)
		{
			LcdPixel(x_start + j, y_start, 1);        // up line
			LcdPixel(x_start + j, y_start + (y_lenght / 2), 1);       // middle line
			LcdPixel(x_start + j, y_end, 1);  // down line
		}

		if ((j % 8) == 0)
		{
			for (q = y_lenght; q > 0; q--)
			{
				if ((q % 3) == 0)
					LcdPixel(x_start + j, y_end - q, 1);  // vertical line
			}
		}
	}

}

//////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////////
void Draw_speedup(uint8_t x_start, uint8_t x_end, uint8_t y_start, uint8_t y_end)
{
	uint32_t i = 0;
	int massive_len = Settings.Second_count >> 2; // 50@200 62@250
	int recalc_len = massive_len / Data.auto_speedup_factor;      // 62/9 = 6


	if ((Settings.Second_count / 4) > 100)
	{                             // если время счета большое, то рисуем тонкие линии
		i = x_start + recalc_len;

	}
	else
	{                             // если время счета маленькое, то рисуем толстые линии
		i = x_start + (recalc_len * 2);
	}

	if ((i + 2) <= x_end)
	{
		LcdLine(i, y_start - 2, i + 2, y_start - 2, 1);
		LcdLine(i, y_start - 3, i + 2, y_start - 3, 1);
	}
}

//////////////////////////////////////////////////////////////////////////////////////


void Draw_fon_digit(uint8_t line, uint8_t start_char, uint8_t invert, uint32_t fonmodule_val, uint8_t label, uint8_t accentuation)
{
	uint32_t digit_num = 0;
	float fonusvh = 0;

	if (label == QUANT)
	{
		sprintf(lcd_buf, LANG_GAMMA1);
		LcdString(((start_char + 6) * 2), line);

		sprintf(lcd_buf, LANG_GAMMA2);
		LcdString(((start_char + 6) * 2), line + 1);

		if (fonmodule_val < 1000000)
		{
			sprintf(lcd_buf, "%6i", fonmodule_val);
		}
		else
		{
			sprintf(lcd_buf, "%5iK", fonmodule_val / 1000);
		}
		LcdStringBold(start_char, line);
	}

	if (label == SIVERT)
	{
		if (Settings.AMODUL_mode == 0)
		{
			fonusvh = convert_mkr_sv(fonmodule_val);
		}
		else
		{
			fonusvh = fonmodule_val;
			fonusvh /= Settings.ACAL_count;
		}

		sprintf(lcd_buf, LANG_UZ);
		LcdString(((start_char + 6) * 2), line);

		sprintf(lcd_buf, LANG_H);
		LcdString(((start_char + 6) * 2), line + 1);

		if (fonusvh <= 1000)         // 999.99 мкЗв/ч
		{
			sprintf(lcd_buf, "%6.2f", fonusvh);
		}
		else
		{
			if (fonusvh <= 1000)       // 9999.9 мкЗв/ч
			{
				sprintf(lcd_buf, "%6.1f", fonusvh);
			}
			else
			{                         // 999999 мкЗв/ч
				sprintf(lcd_buf, "%6.0f", fonusvh);
			}
		}
		LcdStringBold(start_char, line);
	}

	if (label == MKRH)
	{
		sprintf(lcd_buf, LANG_UR);
		LcdString(((start_char + 6) * 2), line);

		sprintf(lcd_buf, LANG_H);
		LcdString(((start_char + 6) * 2), line + 1);

		if (Data.fon_level <= 999999)        // 1Р/ч
		{
			sprintf(lcd_buf, "%6i", Data.fon_level);
		}
		else
		{
			sprintf(lcd_buf, "%5iK", Data.fon_level / 1000);
		}
		LcdStringBold(start_char, line);
	}

	if (label == BETA)
	{
		if (Settings.AB_mode < 2)
		{
			sprintf(lcd_buf, LANG_BETA1);
			LcdStringInv(((start_char + 6) * 2), line);

			sprintf(lcd_buf, LANG_BETA2);
			LcdStringInv(((start_char + 6) * 2), line + 1);
		}
		else
		{
			sprintf(lcd_buf, LANG_BETA1);
			LcdString(((start_char + 6) * 2), line);

			sprintf(lcd_buf, LANG_BETA2);
			LcdString(((start_char + 6) * 2), line + 1);
		}

		if (Data.AB_fon < 1000000)
		{
			sprintf(lcd_buf, "%6i", Data.AB_fon);
			LcdStringBold(start_char, line);
		}
		else
		{
			sprintf(lcd_buf, "%5iK", Data.AB_fon / 1000);
			LcdStringBold(start_char, line);
		}
	}

	LcdLine(((start_char + 5) * 12) + 5, line * 8, ((start_char + 5) * 12) + 18 + 5, line * 8, 1);

	if (accentuation == 1)
		for (digit_num = 0; digit_num < 6; digit_num++)
		{
			LcdLine(((start_char + digit_num - 1) * 10) + (2 * digit_num),
				line * 16, ((start_char + digit_num - 1) * 10) + (2 * digit_num) + 10, line * 16, 1);
			LcdLine(((start_char + digit_num - 1) * 10) + (2 * digit_num),
				line * 16, ((start_char + digit_num - 1) * 10) + (2 * digit_num), (line * 16) - 3, 1);
			LcdLine(((start_char + digit_num - 1) * 10) + (2 * digit_num) + 10,
				line * 16, ((start_char + digit_num - 1) * 10) + (2 * digit_num) + 10, (line * 16) - 3, 1);
		}
}

//////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////



void LcdBatt(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t persent, uint8_t is_charged)      //рисуем батарейку с заполнением в %
{
	uint32_t horizon_line = 0, horizon_line2 = 0, i = 0;
	if (persent > 100)
		persent = 100;
	LcdLine(x1, y2, x2, y2, 1);   //down
	LcdLine(x2, y1, x2, y2, 1);   //right
	LcdLine(x1, y1, x1, y2, 1);   //left
	LcdLine(x1, y1, x2, y1, 1);   //up
	LcdLine(x1 + 7, y1 - 1, x2 - 7, y1 - 1, 1);
	LcdLine(x1 + 7, y1 - 2, x2 - 7, y1 - 2, 1);

	if(Power.charging && !is_charged)
	{
		/*LcdPixel(x1+2+5, y1+2+2, PIXEL_ON);
		
		LcdPixel(x1+2+4, y1+2+3, PIXEL_ON);
		LcdPixel(x1+2+5, y1+2+3, PIXEL_ON);
		
		LcdPixel(x1+2+3, y1+2+4, PIXEL_ON);
		LcdPixel(x1+2+4, y1+2+4, PIXEL_ON);
		LcdPixel(x1+2+5, y1+2+4, PIXEL_ON);
		
		LcdPixel(x1+2+2, y1+2+5, PIXEL_ON);
		LcdPixel(x1+2+3, y1+2+5, PIXEL_ON);
		LcdPixel(x1+2+4, y1+2+5, PIXEL_ON);
		
		LcdPixel(x1+2+1, y1+2+6, PIXEL_ON);
		LcdPixel(x1+2+2, y1+2+6, PIXEL_ON);
		LcdPixel(x1+2+3, y1+2+6, PIXEL_ON);
		LcdPixel(x1+2+4, y1+2+6, PIXEL_ON);
		
		LcdPixel(x1+2+1, y1+2+7, PIXEL_ON);
		LcdPixel(x1+2+2, y1+2+7, PIXEL_ON);
		LcdPixel(x1+2+3, y1+2+7, PIXEL_ON);
		LcdPixel(x1+2+4, y1+2+7, PIXEL_ON);
		LcdPixel(x1+2+5, y1+2+7, PIXEL_ON);
		
		LcdPixel(x1+2+1, y1+2+8, PIXEL_ON);
		LcdPixel(x1+2+2, y1+2+8, PIXEL_ON);
		LcdPixel(x1+2+3, y1+2+8, PIXEL_ON);
		LcdPixel(x1+2+4, y1+2+8, PIXEL_ON);
		LcdPixel(x1+2+5, y1+2+8, PIXEL_ON);
		
		LcdPixel(x1+2+3, y1+2+9, PIXEL_ON);
		LcdPixel(x1+2+4, y1+2+9, PIXEL_ON);
		LcdPixel(x1+2+5, y1+2+9, PIXEL_ON);
		LcdPixel(x1+2+6, y1+2+9, PIXEL_ON);
		
		LcdPixel(x1+2+3, y1+2+10, PIXEL_ON);
		LcdPixel(x1+2+4, y1+2+10, PIXEL_ON);
		LcdPixel(x1+2+5, y1+2+10, PIXEL_ON);
		
		LcdPixel(x1+2+2, y1+2+11, PIXEL_ON);
		LcdPixel(x1+2+3, y1+2+11, PIXEL_ON);
		LcdPixel(x1+2+4, y1+2+11, PIXEL_ON);
		
		LcdPixel(x1+2+2, y1+2+12, PIXEL_ON);
		LcdPixel(x1+2+3, y1+2+12, PIXEL_ON);
		
		LcdPixel(x1+2+2, y1+2+13, PIXEL_ON);*/
		LcdPixel(x1+2+3, y1+2+1, PIXEL_ON);
		LcdLine(x1 + 2 + 2, y1 + 2 + 2, x1 + 2 + 3, y1 + 2 + 2, 1);
		LcdLine(x1 + 2 + 2, y1 + 2 + 3, x1 + 2 + 3, y1 + 2 + 3, 1);
		LcdLine(x1 + 2 + 1, y1 + 2 + 4, x1 + 2 + 3, y1 + 2 + 4, 1);
		LcdLine(x1 + 2 + 1, y1 + 2 + 5, x1 + 2 + 3, y1 + 2 + 5, 1);
		LcdLine(x1 + 2, y1 + 2 + 6, x1 + 2 + 3, y1 + 2 + 6, 1);
		LcdLine(x1 + 2, y1 + 2 + 7, x1 + 2 + 6, y1 + 2 + 7, 1);
		LcdLine(x1 + 2, y1 + 2 + 8, x1 + 2 + 6, y1 + 2 + 8, 1);
		LcdLine(x1 + 2 + 3, y1 + 2 + 9, x1 + 2 + 6, y1 + 2 + 9, 1);
		LcdLine(x1 + 2 + 3, y1 + 2 + 10, x1 + 2 + 5, y1 + 2 + 10, 1);
		LcdLine(x1 + 2 + 3, y1 + 2 + 11, x1 + 2 + 5, y1 + 2 + 11, 1);
		LcdLine(x1 + 2 + 3, y1 + 2 + 12, x1 + 2 + 4, y1 + 2 + 12, 1);
		LcdLine(x1 + 2 + 3, y1 + 2 + 13, x1 + 2 + 4, y1 + 2 + 13, 1);
		LcdPixel(x1+2+3, y1+2+14, PIXEL_ON);
	}else
	{
		horizon_line = persent * (y2 - y1 - 1) / 100;
		for (i = 0; i < horizon_line; i++)
		LcdLine(x1 + 1, y2 - 1 - i, x2 - 1, y2 - 1 - i, 1);
		horizon_line2 = (y2 - y1 - 1);
		for (i = horizon_line2; i > horizon_line; i--)
		LcdLine(x1 + 1, y2 - 1 - i, x2 - 1, y2 - 1 - i, 0);
	}
}



