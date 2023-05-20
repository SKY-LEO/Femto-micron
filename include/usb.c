#include "main.h"

extern __IO uint8_t Receive_Buffer[VIRTUAL_COM_PORT_DATA_SIZE];
extern __IO uint32_t Receive_length;
extern __IO uint32_t length;
extern __IO uint32_t Send_length;
uint8_t Send_Buffer[VIRTUAL_COM_PORT_DATA_SIZE];
uint32_t packet_sent = 1;
uint32_t packet_receive = 1;

// =========================================================================================
uint8_t prepare_data(uint32_t mode, uint16_t * massive_pointer, uint8_t start_key)      // ���������� ������� ������ � ��������
{
  uint8_t data_key = 0;
  uint8_t address_hi = 0;
  uint8_t address_lo = 0;
  uint8_t fon_1_4 = 0;
  uint8_t fon_2_4 = 0;
  uint8_t fon_3_4 = 0;
  uint8_t fon_4_4 = 0;
  uint32_t used_lenght = 0;
  uint32_t tmp = 0;             // ����������� �����
  uint32_t eeprom_data = 0;     // ����������� �����

  while (used_lenght <= (VIRTUAL_COM_PORT_DATA_SIZE - 7))
  {
    if(mode != eeprom_send_data)
    {
      if(*massive_pointer >= FLASH_MAX_ELEMENT - 1 - 4)
      {
        *massive_pointer = FLASH_MAX_ELEMENT - 1;
        return used_lenght;
      }

      address_lo = *massive_pointer & 0xff;
      address_hi = (*massive_pointer >> 8) & 0xff;

      if(flash_read_massive((*massive_pointer), mode) < 0xff &&
         flash_read_massive((*massive_pointer) + 1, mode) < 0xff &&
         flash_read_massive((*massive_pointer) + 2, mode) < 0xff && flash_read_massive((*massive_pointer) + 3, mode) < 0xff)
      {                         // ���� �������� ������ �������
        data_key = start_key - 0x70;
        fon_1_4 = flash_read_massive((*massive_pointer), mode) & 0xff;
        fon_2_4 = flash_read_massive((*massive_pointer) + 1, mode) & 0xff;
        fon_3_4 = flash_read_massive((*massive_pointer) + 2, mode) & 0xff;
        fon_4_4 = flash_read_massive((*massive_pointer) + 3, mode) & 0xff;
        *massive_pointer = *massive_pointer + 4;
      } else
      {                         // ���� ������ ����� ������
        data_key = start_key;
        tmp = flash_read_massive(*massive_pointer, mode);
        fon_1_4 = tmp & 0xff;
        fon_2_4 = (tmp >> 8) & 0xff;
        fon_3_4 = (tmp >> 16) & 0xff;
        fon_4_4 = (tmp >> 24) & 0xff;
        *massive_pointer = *massive_pointer + 1;
      }
    } else
    {
      data_key = start_key;
      address_lo = eeprom_address & 0xff;
      address_hi = (eeprom_address >> 8) & 0xff;

      eeprom_data = eeprom_read(eeprom_address);
      eeprom_address += 0x04;

      fon_1_4 = eeprom_data & 0xff;
      fon_2_4 = (eeprom_data >> 8) & 0xff;
      fon_3_4 = (eeprom_data >> 16) & 0xff;
      fon_4_4 = (eeprom_data >> 24) & 0xff;
    }
    Send_Buffer[used_lenght] = data_key;        // �������� ����
    Send_Buffer[used_lenght + 1] = address_hi;  // �������� �� ����� 
    Send_Buffer[used_lenght + 2] = address_lo;  // �������� �� ����� 
    Send_Buffer[used_lenght + 3] = fon_4_4;     // �������� �� ����� 
    Send_Buffer[used_lenght + 4] = fon_3_4;     // �������� �� ����� 
    Send_Buffer[used_lenght + 5] = fon_2_4;     // �������� �� ����� 
    Send_Buffer[used_lenght + 6] = fon_1_4;     // �������� �� ����� 

    used_lenght += 7;
  }
  return used_lenght;
}

// =========================================================================================


void USB_send_serial_data(int num)
{
//---------------------------------------------������� ��� MadOrc------------------------------------

  switch (num)
  {
  case 0x0:
    Send_Buffer[0] = 0xE0;
    Send_Buffer[1] = U_ID_0 & 0xff;     // �������� �� ����� 
    Send_Buffer[2] = (U_ID_0 >> 8) & 0xff;      // �������� �� ����� 
    Send_Buffer[3] = (U_ID_0 >> 16) & 0xff;     // �������� �� ����� 
    Send_Buffer[4] = (U_ID_0 >> 24) & 0xff;     // �������� �� ����� 
    break;
  case 0x1:
    Send_Buffer[0] = 0xE1;
    Send_Buffer[1] = U_ID_1 & 0xff;     // �������� �� ����� 
    Send_Buffer[2] = (U_ID_1 >> 8) & 0xff;      // �������� �� ����� 
    Send_Buffer[3] = (U_ID_1 >> 16) & 0xff;     // �������� �� ����� 
    Send_Buffer[4] = (U_ID_1 >> 24) & 0xff;     // �������� �� ����� 
    break;
  case 0x2:
    Send_Buffer[0] = 0xE2;
    Send_Buffer[1] = U_ID_2 & 0xff;     // �������� �� ����� 
    Send_Buffer[2] = (U_ID_2 >> 8) & 0xff;      // �������� �� ����� 
    Send_Buffer[3] = (U_ID_2 >> 16) & 0xff;     // �������� �� ����� 
    Send_Buffer[4] = (U_ID_2 >> 24) & 0xff;     // �������� �� ����� 
    break;
  }
  Send_Buffer[5] = 0;           // �������� �� ����� 
  Send_Buffer[6] = 1;           // ������� ��������������

  Send_length = 7;
}

// =========================================================================================

void USB_send_time_offset_data()
{
//---------------------------------------------������� ��� MadOrc------------------------------------
  uint8_t offsetHi = 0;         //  ������� ���� �������
  uint8_t offsetLo = 0;         // �������  ���� ������� 


  offsetLo = DataUpdate.doze_sec_count & 0xff;  // ������� ������ �� ������� ����
  offsetHi = (DataUpdate.doze_sec_count >> 8) & 0xff;   // ������� ������ �� ������� ����  

  Send_Buffer[0] = 0xD2;        // �������� ����� �������� �������
  Send_Buffer[1] = offsetHi;    // �������� �� ����� 
  Send_Buffer[2] = offsetLo;    // �������� �� ����� 
  Send_Buffer[3] = 0;           // �������� �� ����� 
  Send_Buffer[4] = 0;           // �������� �� ����� 
  Send_Buffer[5] = 0;           // �������� �� ����� 
  Send_Buffer[6] = 0;           // �������� �� ����� 

  Send_length = 7;
}

// =========================================================================================

void USB_send_madorc_data()
{
//---------------------------------------------������� ��� MadOrc------------------------------------
  uint8_t fonMegaHi = 0;        //  ������� ���� �������
  uint8_t fonHi = 0;            //  ������� ���� �������
  uint8_t fonLo = 0;            // �������  ���� ������� 
  uint8_t impulseHi = 0;        //  ������� ���� �������
  uint8_t impulseLo = 0;        // �������  ���� ������� 
  uint8_t voltIndexLo = 0;      // �������  ���� ������� 


  impulseLo = Data.madorc_impulse & 0xff;       // ������� ������ �� ������� ����
  impulseHi = (Data.madorc_impulse >> 8) & 0xff;        // ������� ������ �� ������� ����  
  Data.madorc_impulse = 0;

  voltIndexLo = ((ADCData.Batt_voltage / 10) - 300) & 0xff;     // ������� ������ �� ������� ����


  fonLo = Data.fon_level & 0xff;        // ������� ������ �� ������� ����
  fonHi = (Data.fon_level >> 8) & 0xff; // ������� ������ �� ������� ����  
  fonMegaHi = (Data.fon_level >> 16) & 0xff;    // ������� ������ �� ������� ����  

  Send_Buffer[0] = 0xD1;        // �������� ����� Marorc
  Send_Buffer[1] = impulseHi;   // �������� �� ����� 
  Send_Buffer[2] = impulseLo;   // �������� �� ����� 
  Send_Buffer[3] = fonMegaHi;   // �������� �� ����� 
  Send_Buffer[4] = fonHi;       // �������� �� ����� 
  Send_Buffer[5] = fonLo;       // �������� �� ����� 
  Send_Buffer[6] = voltIndexLo; // �������� �� ����� 

  Send_length = 7;
}

// =========================================================================================
void time_loading(uint32_t current_rcvd_pointer)
{
  RTC_TimeTypeDef RTC_TimeStructure;
  RTC_DateTypeDef RTC_DateStructure;
  FunctionalState need_update_wakeup = DISABLE;

  //-----------------------------------------------------------------------------------------
  // �������� � ��������� �������
  //-----------------------------------------------------------------------------------------
  RTC_TimeStructInit(&RTC_TimeStructure);
  RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
  if(current_rcvd_pointer + 6 >= VIRTUAL_COM_PORT_DATA_SIZE)
    return;
  if((RTC_TimeStructure.RTC_Hours !=
      (Receive_Buffer[current_rcvd_pointer + 4] & 0xff))
     || (RTC_TimeStructure.RTC_Minutes !=
         (Receive_Buffer[current_rcvd_pointer + 5] & 0xff))
     ||
     (!(((RTC_TimeStructure.RTC_Seconds + 1) >=
         Receive_Buffer[current_rcvd_pointer + 6]) && ((RTC_TimeStructure.RTC_Seconds - 1) <= Receive_Buffer[current_rcvd_pointer + 6]))))
  {                             // ���� ����� �� ���������, ������������� ����� (+-1 �������)
    RTC_TimeStructInit(&RTC_TimeStructure);
    RTC_TimeStructure.RTC_Hours = Receive_Buffer[current_rcvd_pointer + 4] & 0xff;
    RTC_TimeStructure.RTC_Minutes = Receive_Buffer[current_rcvd_pointer + 5] & 0xff;
    RTC_TimeStructure.RTC_Seconds = Receive_Buffer[current_rcvd_pointer + 6] & 0xff;

    need_update_wakeup = ENABLE;

    RTC_AlarmCmd(RTC_Alarm_A, DISABLE);
    RTC_ClearFlag(RTC_FLAG_ALRAF);

    RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure);
  }
  //-----------------------------------------------------------------------------------------
  // �������� � ��������� ����
  //-----------------------------------------------------------------------------------------
  RTC_DateStructInit(&RTC_DateStructure);
  RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);

  if((RTC_DateStructure.RTC_Date !=
      (Receive_Buffer[current_rcvd_pointer + 3] & 0xff))
     || (RTC_DateStructure.RTC_Month !=
         (Receive_Buffer[current_rcvd_pointer + 2] & 0xff)) || (RTC_DateStructure.RTC_Year != (Receive_Buffer[current_rcvd_pointer + 1] & 0xff)))
  {                             // ���� ���� �� ���������, ������������� �����
    RTC_DateStructInit(&RTC_DateStructure);
    RTC_DateStructure.RTC_Date = Receive_Buffer[current_rcvd_pointer + 3] & 0xff;
    RTC_DateStructure.RTC_Month = Receive_Buffer[current_rcvd_pointer + 2] & 0xff;
    RTC_DateStructure.RTC_Year = Receive_Buffer[current_rcvd_pointer + 1] & 0xff;

    need_update_wakeup = ENABLE;

    RTC_AlarmCmd(RTC_Alarm_A, DISABLE);
    RTC_ClearFlag(RTC_FLAG_ALRAF);

    RTC_SetDate(RTC_Format_BIN, &RTC_DateStructure);
    RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
  }
  //-----------------------------------------------------------------------------------------

  if(need_update_wakeup == ENABLE)
  {
    RTC_WaitForSynchro();
    Set_next_alarm_wakeup();    // ���������� ������ ���������� �� +4 �������
    LcdClear_massive();
    LcdUpdate();
  }
}


//-----------------------------------------------------------------------------------------
void USB_work()
{
  uint32_t wait_count;
  uint32_t current_rcvd_pointer = 0;
  int i;

//---------------------------------------------�������� ������------------------------------------
  if(bDeviceState == CONFIGURED)
  {
    CDC_Receive_DATA();

    //wait_count=0;
    //while((packet_receive != 1) && (wait_count<=1000))wait_count++; // ���� �������� ������

    if(Receive_length != 0)
    {
      current_rcvd_pointer = 0; // ����� �������� ������� ������� ������

      // �������������� �������� ������ �������� ������ ������.
      if(DataUpdate.Need_erase_flash == ENABLE)
      {
        full_erase_flash();
        DataUpdate.Need_erase_flash = DISABLE;
      }
      Data.USB_not_active = 0;  // ����� ������� ������������ USB 

      while (Receive_length > current_rcvd_pointer)
      {
        if(current_rcvd_pointer >= VIRTUAL_COM_PORT_DATA_SIZE)
          return;
        switch (Receive_Buffer[current_rcvd_pointer])
        {
        case 0xD4:             // �������� ������ �� ������� ������ ������ (RCV 1 ����)
          if(Settings.Cal_mode != 1)
            USB_send_madorc_data();
          current_rcvd_pointer++;
          break;

        case 0xE0:             // �������� ��������� ������ �� (RCV 1 ����)
          USB_send_serial_data(0);
          current_rcvd_pointer++;
          break;

        case 0xE1:             // �������� ��������� ������ �� (RCV 1 ����)
          USB_send_serial_data(1);
          current_rcvd_pointer++;
          break;

        case 0xE2:             // �������� ��������� ������ �� (RCV 1 ����)
          USB_send_serial_data(2);
          current_rcvd_pointer++;
          break;
        case 0xE5:             // �������� ���� �������� (RCV 1 ����)
          Send_Buffer[0] = 0xE5;        // �������� ����
          Send_Buffer[1] = __DATE__[4]; // ����
          Send_Buffer[2] = __DATE__[5]; // ����
          Send_Buffer[3] = __DATE__[0]; // �����
          Send_Buffer[4] = __DATE__[1]; // �����
          Send_Buffer[5] = __DATE__[2]; // �����
          Send_Buffer[6] = __DATE__[10];        // ���
          Send_length = 7;
          current_rcvd_pointer++;
          break;

        case 0xE6:             // �������� ������ ������ (RCV 1 ����)
          Send_Buffer[0] = 0xE6;        // �������� ����
          Send_Buffer[1] = HW_REVISION[0];
          Send_Buffer[2] = HW_REVISION[1];
          Send_Buffer[3] = HW_REVISION[2];
          Send_Buffer[4] = HW_REVISION[3];
          Send_Buffer[5] = HW_REVISION[4];
          Send_Buffer[6] = 0x00;
          Send_length = 7;

          current_rcvd_pointer++;
          break;

        case 0xD5:             // �������� ����� �������� ������� (RCV 1 ����)
          USB_send_time_offset_data();
          current_rcvd_pointer++;
          break;

        case 0x31:             // �������� ������� ������������� ���� (RCV 1 ����)
          Send_length = prepare_data(max_fon_select, &USB_maxfon_massive_pointer, 0xF1);        // ���������� ������� ������ � ��������
          if(Send_length == 0)
            current_rcvd_pointer++;     // ���� ������ ��������
          break;

        case 0x32:             // �������� ������� ���� (RCV 1 ����)
          Send_length = prepare_data(dose_select, &USB_doze_massive_pointer, 0xF3);     // ���������� ������� ������ � ��������
          if(Send_length == 0)
            current_rcvd_pointer++;     // ���� ������ ��������
          break;

        case 0x33:             // �������� �������� (RCV 1 ����)
          USB_maxfon_massive_pointer = 0;
          USB_doze_massive_pointer = 0;
          USB_send_settings_data();
          current_rcvd_pointer++;
          break;

        case 0x34:             // �������� ���������� (RCV 1 ����)
          USB_send_calibration_data();
          current_rcvd_pointer++;
          break;

        case 0x35:             // ������ ���������� (RCV 1 ����)
          for (i = 0; i < 19; i++)
            Data.Cal_count_mass[i] = 0;
          Cal_count = 0;
          Cal_count_time = 0;
          Settings.Cal_mode = 1;
          Data.menu_select = 0;
          Data.enter_menu_item = DISABLE;
          Data.screen = 1;
          hidden_menu = ENABLE;
          GPIO_ResetBits(GPIOC, GPIO_Pin_13);
          current_rcvd_pointer++;
          break;

        case 0x36:             // ����� �� ���������� (RCV 1 ����)
          for (i = 0; i < 19; i++)
            Data.Cal_count_mass[i] = 0;
          Cal_count = 0;
          Cal_count_time = 0;
          Settings.Cal_mode = 0;
          Data.menu_select = 0;
          Data.enter_menu_item = DISABLE;
          Data.screen = 1;
          hidden_menu = DISABLE;
          Data.madorc_impulse = 0;
          plus_rad_reset(0x0);
          plus_doze_reset(0x0);
          full_erase_flash();
          GPIO_SetBits(GPIOC, GPIO_Pin_13);
          current_rcvd_pointer++;
          break;

        case 0x37:             // �������� ������ � EEPROM (RCV 7 ����)
          if((current_rcvd_pointer + 7) <= Receive_length)      // �������� ������ ��������� �������
          {
            eeprom_loading(current_rcvd_pointer);
            current_rcvd_pointer += 7;
          } else
          {
            current_rcvd_pointer = Receive_length;      // ������� ������ ��� ������ ����, ��������� ����
          }
          break;


        case 0x38:             // �������� ������ �� EEPROM (RCV 1 ����)
          Send_length = prepare_data(eeprom_send_data, 0x00, 0xF7);     // ���������� ������� ������ � ��������
          if(Send_length == 0 || eeprom_address >= 0xFF)
          {
            eeprom_address = 0;
            current_rcvd_pointer++;     // ���� ������ ��������
          }
          break;


        case 0x39:             // ���������� �������� (RCV 1 ����)
          USB_maxfon_massive_pointer = 0;
          USB_doze_massive_pointer = 0;
          current_rcvd_pointer++;
          break;

        case 0xE4:             // �������� ������� (RCV 7 ����)
          if((current_rcvd_pointer + 7) <= Receive_length)      // �������� ������ ��������� �������
          {
            time_loading(current_rcvd_pointer);
            current_rcvd_pointer += 7;
          } else
          {
            current_rcvd_pointer = Receive_length;      // ������� ������ ��� ������ ����, ��������� ����
          }
          break;

        case 0xE3:             // ���� ������������� (RCV 5 ����)
          if((current_rcvd_pointer + 5) <= Receive_length)      // �������� ������ ��������� �������
          {
            if(current_rcvd_pointer + 4 >= VIRTUAL_COM_PORT_DATA_SIZE)
              return;
            eeprom_write(unlock_0_address, Receive_Buffer[current_rcvd_pointer + 1]);
            eeprom_write(unlock_1_address, Receive_Buffer[current_rcvd_pointer + 2]);
            eeprom_write(unlock_2_address, Receive_Buffer[current_rcvd_pointer + 3]);
            eeprom_write(unlock_3_address, Receive_Buffer[current_rcvd_pointer + 4]);
            current_rcvd_pointer += 5;
            LcdClear_massive();
            LcdUpdate();
          } else
          {
            current_rcvd_pointer = Receive_length;      // ������� ������ ��� ������ ����, ��������� ����
          }
          break;

        default:
          current_rcvd_pointer++;
          break;
        }

        if(Send_length > 0)     // ���� ����� �� �������� �����������
        {
          wait_count = 0;
          while ((packet_sent != 1) && (wait_count < 0xFFFF))
            wait_count++;       // ��������� ������� �� ������� �����

          CDC_Send_DATA((unsigned char *) Send_Buffer, Send_length);
          Send_length = 0;
        }
      }
      Receive_length = 0;
    }
  }
  if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)) // ���� 5� �� USB �� ��������, �� ��������� ���
  {

    wait_count = 0;
    while ((packet_sent != 1) && (wait_count < 0xFFFF))
      wait_count++;             // ��������� ������� �� ������� �����

    usb_deactivate(0x00);
  }

}



void USB_send_settings_data()
{
//---------------------------------------------������� ��� MadOrc------------------------------------

  uint8_t count_time_hi = 0;
  uint8_t count_time_lo = 0;

  count_time_lo = Settings.Second_count & 0xff;
  count_time_hi = (Settings.Second_count >> 8) & 0xff;
  Send_Buffer[0] = 0xF5;        // �������� �����
  Send_Buffer[1] = count_time_hi;       // �������� �� ����� 
  Send_Buffer[2] = count_time_lo;       // �������� �� ����� 
  Send_Buffer[3] = 0xFF;        // �������� �� ����� 
  Send_Buffer[4] = 0xFF;        // �������� �� ����� 
  Send_Buffer[5] = 0xFF;        // �������� �� ����� 
  Send_Buffer[6] = 0xFF;        // �������� �� ����� 
  Send_Buffer[7] = 0xFF;        // �������� �� ����� 

  Send_length = 7;
}


void USB_send_calibration_data()
{
//---------------------------------------------�������� ������ ��� ����������------------------------------------

  uint8_t count_time_lo = 0;
  uint8_t count_time_hi = 0;
  if(Cal_count > 0)
  {
    count_time_lo = Settings.Second_count & 0xff;
    count_time_hi = (Settings.Second_count >> 8) & 0xff;
    Send_Buffer[0] = 0xF6;      // �������� �����
    Send_Buffer[1] = count_time_hi;
    Send_Buffer[2] = count_time_lo;
    Send_Buffer[3] = Data.Cal_count_mass[Cal_count - 1] & 0xff;
    Send_Buffer[4] = (Data.Cal_count_mass[Cal_count - 1] >> 8) & 0xff;
    Send_Buffer[5] = (Data.Cal_count_mass[Cal_count - 1] >> 16) & 0xff;
    Send_Buffer[6] = (Cal_count - 1) & 0xff;
  } else
  {
    Send_Buffer[0] = 0xF6;      // �������� �����
    Send_Buffer[1] = 0x0;
    Send_Buffer[2] = 0x0;
    Send_Buffer[3] = 0x0;
    Send_Buffer[4] = 0x0;
    Send_Buffer[5] = 0x0;
    Send_Buffer[6] = 0xff;
  }
  Send_length = 7;
}


void USB_off()
{
  GPIO_InitTypeDef GPIO_InitStructure;
//---------------------------------------------���������� USB------------------------------------
  Power.USB_active = DISABLE;
  PowerOff();
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, DISABLE);
  set_msi();

  SystemCoreClockUpdate();

  // �������� � ������� ������� ������������ (��������)
  //sleep_mode(ENABLE);
  //while (Power.Pump_active || Power.Sound_active);
  //PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI); // ��������� � ���
  //sleep_mode(DISABLE);

  Power.sleep_time = Settings.Sleep_time;

  GPIO_ResetBits(GPIOC, GPIO_Pin_13);   // �������� ���������  

  // ===============================================================================================  
  // �������� ������� ������ �
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;      // �����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);        // ��������� ������������
  GPIO_SetBits(GPIOA, GPIO_InitStructure.GPIO_Pin);     // ��������� ����������
  // ===============================================================================================  


}


void USB_on()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  //---------------------------------------------��������� USB------------------------------------

  // ===============================================================================================  
  // ��������� ������� ������ �
  GPIO_ResetBits(GPIOA, GPIO_Pin_11 | GPIO_Pin_12);     // ��������� ����������
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  // ===============================================================================================  


  GPIO_SetBits(GPIOC, GPIO_Pin_13);     // ��������� ��������� (Hi-Z)

  set_pll_for_usb();
  Set_System();
  SystemCoreClockUpdate();
  Set_USBClock();
  reset_TIM_prescallers_and_Compare();
  USB_Interrupts_Config();
  USB_Init();
  SYSCFG->PMC |= (uint32_t) SYSCFG_PMC_USB_PU;  // Connect internal pull-up on USB DP line
  Power.USB_active = ENABLE;
}
