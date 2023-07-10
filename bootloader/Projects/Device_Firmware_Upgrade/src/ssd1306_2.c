#include "stm32l1xx_conf.h"
#include "stm32l1xx_spi.h"
#include "delay.h"
#include "ssd1306_2.h"

unsigned char Dummy;

static uint8_t buffer[64 * 128 / 8] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x80, 0x80, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xF8, 0xE0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80,
0x80, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0xFF,
0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x1F, 0x0F,
0x87, 0xC7, 0xF7, 0xFF, 0xFF, 0x1F, 0x1F, 0x3D, 0xFC, 0xF8, 0xF8, 0xF8, 0xF8, 0x7C, 0x7D, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x0F, 0x07, 0x00, 0x30, 0x30, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xC0, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xC0, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x3F, 0x1F,
0x0F, 0x07, 0x1F, 0x7F, 0xFF, 0xFF, 0xF8, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF8, 0xE0,
0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00,
0x00, 0xFC, 0xFE, 0xFC, 0x0C, 0x06, 0x06, 0x0E, 0xFC, 0xF8, 0x00, 0x00, 0xF0, 0xF8, 0x1C, 0x0E,
0x06, 0x06, 0x06, 0x0C, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0xFC,
0xFE, 0xFC, 0x00, 0x18, 0x3C, 0x7E, 0x66, 0xE6, 0xCE, 0x84, 0x00, 0x00, 0x06, 0xFF, 0xFF, 0x06,
0x06, 0xFC, 0xFE, 0xFC, 0x0C, 0x06, 0x06, 0x06, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00, 0xC0, 0xF8,
0xFC, 0x4E, 0x46, 0x46, 0x46, 0x4E, 0x7C, 0x78, 0x40, 0x18, 0x3C, 0x76, 0xE6, 0xCE, 0xCC, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0F, 0x1F, 0x1F, 0x3F, 0x3F, 0x3F, 0x3F, 0x1F, 0x0F, 0x03,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00,
0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x03, 0x07, 0x0E, 0x0C,
0x18, 0x18, 0x0C, 0x06, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x01, 0x0F, 0x0E, 0x0C, 0x18, 0x0C, 0x0F,
0x07, 0x01, 0x00, 0x04, 0x0E, 0x0C, 0x18, 0x0C, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00,
0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x07,
0x07, 0x0C, 0x0C, 0x18, 0x1C, 0x0C, 0x06, 0x06, 0x00, 0x04, 0x0E, 0x0C, 0x18, 0x0C, 0x0F, 0x07,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


void Init_SSD1306_gpios()
{
	GPIO_InitTypeDef GPIO_InitStructure;
SPI_InitTypeDef SPI_InitStructure;
	
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
	delay_ms(10);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	delay_ms(10);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1), 
	//GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1), 
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1), 
	
	GPIO_InitStructure.GPIO_Pin = SCK_Pin | MOSI_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//	GPIO_WriteBit(SCK_MOSI_PORT, SCK_Pin, Bit_SET);
	//	GPIO_WriteBit(SCK_MOSI_PORT, MOSI_Pin, Bit_SET);
	//	GPIO_WriteBit(SCK_MOSI_PORT, MISO_Pin, Bit_SET);

	GPIO_InitStructure.GPIO_Pin = RST_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_Init(CS_RST_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = CS_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_Init(CS_RST_PORT, &GPIO_InitStructure);

	//	GPIO_WriteBit(CS_RST_PORT, RST_Pin,Bit_SET);
	//	GPIO_WriteBit(CS_RST_PORT, CS_Pin, Bit_SET);

	GPIO_InitStructure.GPIO_Pin = VDD_Pin | DC_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(VDD_DC_PORT, &GPIO_InitStructure);
	
	
	
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	//SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	// ���������, ��� ���� ���������� - Master
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	// ���������� ����� �� 8 ��� (=1 ����)
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	// ����� 00
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft | SPI_NSSInternalSoft_Set;//SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	// ������� ������ ������� ����� ����� (�.�. ����� �������)
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	// ����� ��������� � SPI
	//SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Set);
	SPI_Init(SPI1, &SPI_InitStructure);
	// �������  SPI1
	SPI_Cmd(SPI1, ENABLE);
	/*GPIO_SetBits(GPIOA, GPIO_Pin_4);
	SPI1->CR1=0x354;
	SPI1->CR2=0x0;
	//SPI1->SR=0x2;
	//SPI1->DR=0x0;
	SPI1->CRCPR=0x7;
	//	GPIO_WriteBit(VDD_DC_PORT, VDD_Pin, Bit_SET);
	//	GPIO_WriteBit(VDD_DC_PORT, DC_Pin, Bit_SET);
	GPIOA->ODR |= GPIO_OTYPER_ODR_4;*/
}

void Initialize_SPI() {
	/*SPI_InitTypeDef SPI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	delay_ms(10);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	// ���������, ��� ���� ���������� - Master
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	// ���������� ����� �� 8 ��� (=1 ����)
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	// ����� 00
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	// ������� ������ ������� ����� ����� (�.�. ����� �������)
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	// ����� ��������� � SPI
	SPI_Init(SPI1, &SPI_InitStructure);
	// �������  SPI1
	SPI_Cmd(SPI1, ENABLE);*/
	// SS = 1
//    SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Set);
}

void command(uint8_t data)
{
	GPIO_WriteBit(CS_RST_PORT, CS_Pin, Bit_RESET);
	GPIO_WriteBit(VDD_DC_PORT, DC_Pin, Bit_RESET);
	
	//while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
  //{
  //}
  
  /*!< Send the byte */
  //SPI_I2S_SendData(SD_SPI, Data);
	//while(!(SPI1->SR & SPI_SR_TXE));
	//SPI1->DR=data;
  //while (!(SPI1->SR & SPI_SR_TXE)); 
  SPI_I2S_SendData(SPI1, data);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
  /*!< Wait to receive a byte*/
	//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET); // ���, ���� ������ �� ����������
	//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
	GPIO_WriteBit(CS_RST_PORT, CS_Pin, Bit_SET);
};

void Write_Data(uint8_t data)
{
	GPIO_WriteBit(CS_RST_PORT, CS_Pin, Bit_RESET);
	GPIO_WriteBit(VDD_DC_PORT, DC_Pin, Bit_SET);

	//while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
  //{
  //}
  
  /*!< Send the byte */
  //SPI_I2S_SendData(SD_SPI, Data);
	//while(!(SPI1->SR & SPI_SR_TXE));
	//SPI1->DR=data;
  //while (!(SPI1->SR & SPI_SR_TXE)); 
  SPI_I2S_SendData(SPI1, data);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
	//while (!(SPI1->SR & SPI_SR_TXE)); 
  /*!< Wait to receive a byte*/
	//SPI_I2S_SendData(SPI1, data);
	//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
	//while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == RESET);
	//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET); // ���, ���� ������ �� ����������
	GPIO_WriteBit(CS_RST_PORT, CS_Pin, Bit_SET);
};

void Init_SSD1306()
{

	Init_SSD1306_gpios();
	Initialize_SPI();

	GPIO_WriteBit(CS_RST_PORT, CS_Pin, Bit_SET);
	
	GPIO_WriteBit(CS_RST_PORT, RST_Pin, Bit_RESET);
	delay_ms(10);
	GPIO_WriteBit(CS_RST_PORT, RST_Pin, Bit_SET);
	delay_ms(10);
	
	delay_ms(100);
	
	command(SSD1306_DISPLAYOFF);
	//Write_Data(0x20);

    command(0x20); //Set Memory Addressing Mode
    command(0x00); // 00b,Horizontal Addressing Mode; 01b,Vertical Addressing Mode;
                                // 10b,Page Addressing Mode (RESET); 11b,Invalid
    command(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
    command(0xC8); //Set COM Output Scan Direction
    command(0x00); //---set low column address
    command(0x10); //---set high column address
    command(0x40); //--set start line address - CHECK
    command(0xFF);
    command(0xA1); //--set segment re-map 0 to 127 - CHECK
    command(0xA7); //--set inverse color
    command(0xA8); //--set multiplex ratio(1 to 64) - CHECK
    command(0x1F); //

    command(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content

    command(0xD3); //-set display offset - CHECK
    command(0x00); //-not offset

    command(0xD5); //--set display clock divide ratio/oscillator frequency
    command(0xF0); //--set divide ratio

    command(0xD9); //--set pre-charge period
    command(0x22); //

    command(0xDA); //--set com pins hardware configuration - CHECK
    command(0x02);


    command(0xDB); //--set vcomh
    command(0x20); //0x20,0.77xVcc

    command(0x8D); //--set DC-DC enable
    command(0x14); //
		command(SSD1306_DISPLAYON);

	/*command(SSD1306_DISPLAYOFF);
	command(SSD1306_SETDISPLAYCLOCKDIV);
	command(0x80);                                  // the suggested ratio 0x80

	command(SSD1306_SETMULTIPLEX);
	command(0x3F);

	command(SSD1306_SETDISPLAYOFFSET);
	command(0x0);                                   // no offset

	command(SSD1306_SETSTARTLINE | 0x0);            // line #0

	command(SSD1306_CHARGEPUMP);
	command(0x10);

	command(SSD1306_MEMORYMODE);
	command(0x00);

	command(SSD1306_SEGREMAP | 0x1);

	command(SSD1306_COMSCANDEC);

	command(SSD1306_SETCOMPINS);
	command(0x12);

	command(SSD1306_SETCONTRAST);
	command(0x9F);

	command(SSD1306_SETPRECHARGE);
	command(0x22);

	command(SSD1306_SETVCOMDETECT);
	command(0x40);

	command(SSD1306_DISPLAYALLON_RESUME);

	command(SSD1306_NORMALDISPLAY);

	command(SSD1306_DISPLAYON);*/

}

/* Write the screenbuffer with changed to the screen */
void UpdateScreen(void) {
	uint8_t i = 0;
    // Write data to each page of RAM. Number of pages
    // depends on the screen height:
    //
    //  * 32px   ==  4 pages
    //  * 64px   ==  8 pages
    //  * 128px  ==  16 pages
    for(i = 0; i < 64/8; i++) {
        command(0xB0 + i); // Set the current RAM page address.
        command(0x00);
        command(0x10);
        Write_Data(buffer[i]);
    }
}
