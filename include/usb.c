#include "main.h"

extern __IO uint8_t Receive_Buffer[VIRTUAL_COM_PORT_DATA_SIZE];
extern __IO uint32_t Receive_length;
extern __IO uint32_t length;
extern __IO uint32_t Send_length;
uint8_t Send_Buffer[VIRTUAL_COM_PORT_DATA_SIZE];
uint32_t packet_sent = 1;
uint32_t packet_receive = 1;

// =========================================================================================
uint8_t prepare_data(uint32_t mode, uint16_t * massive_pointer, uint8_t start_key)      // Подготовка массива данных к передаче
{
  uint8_t data_key = 0;
  uint8_t address_hi = 0;
  uint8_t address_lo = 0;
  uint8_t fon_1_4 = 0;
  uint8_t fon_2_4 = 0;
  uint8_t fon_3_4 = 0;
  uint8_t fon_4_4 = 0;
  uint32_t used_lenght = 0;
  uint32_t tmp = 0;             // контрольная сумма
  uint32_t eeprom_data = 0;     // контрольная сумма

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
      {                         // Если возможно сжатие массива
        data_key = start_key - 0x70;
        fon_1_4 = flash_read_massive((*massive_pointer), mode) & 0xff;
        fon_2_4 = flash_read_massive((*massive_pointer) + 1, mode) & 0xff;
        fon_3_4 = flash_read_massive((*massive_pointer) + 2, mode) & 0xff;
        fon_4_4 = flash_read_massive((*massive_pointer) + 3, mode) & 0xff;
        *massive_pointer = *massive_pointer + 4;
      } else
      {                         // Если данные сжать нельзя
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
    Send_Buffer[used_lenght] = data_key;        // передать ключ
    Send_Buffer[used_lenght + 1] = address_hi;  // передать по УСАПП 
    Send_Buffer[used_lenght + 2] = address_lo;  // передать по УСАПП 
    Send_Buffer[used_lenght + 3] = fon_4_4;     // передать по УСАПП 
    Send_Buffer[used_lenght + 4] = fon_3_4;     // передать по УСАПП 
    Send_Buffer[used_lenght + 5] = fon_2_4;     // передать по УСАПП 
    Send_Buffer[used_lenght + 6] = fon_1_4;     // передать по УСАПП 

    used_lenght += 7;
  }
  return used_lenght;
}

// =========================================================================================


void USB_send_serial_data(int num)
{
//---------------------------------------------КомПорт для MadOrc------------------------------------

  switch (num)
  {
  case 0x0:
    Send_Buffer[0] = 0xE0;
    Send_Buffer[1] = U_ID_0 & 0xff;     // передать по УСАПП 
    Send_Buffer[2] = (U_ID_0 >> 8) & 0xff;      // передать по УСАПП 
    Send_Buffer[3] = (U_ID_0 >> 16) & 0xff;     // передать по УСАПП 
    Send_Buffer[4] = (U_ID_0 >> 24) & 0xff;     // передать по УСАПП 
    break;
  case 0x1:
    Send_Buffer[0] = 0xE1;
    Send_Buffer[1] = U_ID_1 & 0xff;     // передать по УСАПП 
    Send_Buffer[2] = (U_ID_1 >> 8) & 0xff;      // передать по УСАПП 
    Send_Buffer[3] = (U_ID_1 >> 16) & 0xff;     // передать по УСАПП 
    Send_Buffer[4] = (U_ID_1 >> 24) & 0xff;     // передать по УСАПП 
    break;
  case 0x2:
    Send_Buffer[0] = 0xE2;
    Send_Buffer[1] = U_ID_2 & 0xff;     // передать по УСАПП 
    Send_Buffer[2] = (U_ID_2 >> 8) & 0xff;      // передать по УСАПП 
    Send_Buffer[3] = (U_ID_2 >> 16) & 0xff;     // передать по УСАПП 
    Send_Buffer[4] = (U_ID_2 >> 24) & 0xff;     // передать по УСАПП 
    break;
  }
  Send_Buffer[5] = 0;           // передать по УСАПП 
  Send_Buffer[6] = 1;           // Атрибут лицензирования

  Send_length = 7;
}

// =========================================================================================

void USB_send_time_offset_data()
{
//---------------------------------------------КомПорт для MadOrc------------------------------------
  uint8_t offsetHi = 0;         //  старший байт индекса
  uint8_t offsetLo = 0;         // младший  байт индекса 


  offsetLo = DataUpdate.doze_sec_count & 0xff;  // разбить индекс на младший байт
  offsetHi = (DataUpdate.doze_sec_count >> 8) & 0xff;   // разбить индекс на старший байт  

  Send_Buffer[0] = 0xD2;        // передать ключь смещения времени
  Send_Buffer[1] = offsetHi;    // передать по УСАПП 
  Send_Buffer[2] = offsetLo;    // передать по УСАПП 
  Send_Buffer[3] = 0;           // передать по УСАПП 
  Send_Buffer[4] = 0;           // передать по УСАПП 
  Send_Buffer[5] = 0;           // передать по УСАПП 
  Send_Buffer[6] = 0;           // передать по УСАПП 

  Send_length = 7;
}

// =========================================================================================

void USB_send_madorc_data()
{
//---------------------------------------------КомПорт для MadOrc------------------------------------
  uint8_t fonMegaHi = 0;        //  старший байт индекса
  uint8_t fonHi = 0;            //  старший байт индекса
  uint8_t fonLo = 0;            // младший  байт индекса 
  uint8_t impulseHi = 0;        //  старший байт индекса
  uint8_t impulseLo = 0;        // младший  байт индекса 
  uint8_t voltIndexLo = 0;      // младший  байт индекса 


  impulseLo = Data.madorc_impulse & 0xff;       // разбить индекс на младший байт
  impulseHi = (Data.madorc_impulse >> 8) & 0xff;        // разбить индекс на старший байт  
  Data.madorc_impulse = 0;

  voltIndexLo = ((ADCData.Batt_voltage / 10) - 300) & 0xff;     // разбить индекс на младший байт


  fonLo = Data.fon_level & 0xff;        // разбить индекс на младший байт
  fonHi = (Data.fon_level >> 8) & 0xff; // разбить индекс на старший байт  
  fonMegaHi = (Data.fon_level >> 16) & 0xff;    // разбить индекс на старший байт  

  Send_Buffer[0] = 0xD1;        // передать ключь Marorc
  Send_Buffer[1] = impulseHi;   // передать по УСАПП 
  Send_Buffer[2] = impulseLo;   // передать по УСАПП 
  Send_Buffer[3] = fonMegaHi;   // передать по УСАПП 
  Send_Buffer[4] = fonHi;       // передать по УСАПП 
  Send_Buffer[5] = fonLo;       // передать по УСАПП 
  Send_Buffer[6] = voltIndexLo; // передать по УСАПП 

  Send_length = 7;
}

// =========================================================================================
void time_loading(uint32_t current_rcvd_pointer)
{
  RTC_TimeTypeDef RTC_TimeStructure;
  RTC_DateTypeDef RTC_DateStructure;
  FunctionalState need_update_wakeup = DISABLE;

  //-----------------------------------------------------------------------------------------
  // Проверка и установка времени
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
  {                             // Если время не совпадает, устанавливаем новое (+-1 секунда)
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
  // Проверка и установка даты
  //-----------------------------------------------------------------------------------------
  RTC_DateStructInit(&RTC_DateStructure);
  RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);

  if((RTC_DateStructure.RTC_Date !=
      (Receive_Buffer[current_rcvd_pointer + 3] & 0xff))
     || (RTC_DateStructure.RTC_Month !=
         (Receive_Buffer[current_rcvd_pointer + 2] & 0xff)) || (RTC_DateStructure.RTC_Year != (Receive_Buffer[current_rcvd_pointer + 1] & 0xff)))
  {                             // Если дата не совпадает, устанавливаем новую
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
    Set_next_alarm_wakeup();    // установить таймер просыпания на +4 секунды
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

//---------------------------------------------Передача данных------------------------------------
  if(bDeviceState == CONFIGURED)
  {
    CDC_Receive_DATA();

    //wait_count=0;
    //while((packet_receive != 1) && (wait_count<=1000))wait_count++; // Ждем принятия пакета

    if(Receive_length != 0)
    {
      current_rcvd_pointer = 0; // сброс счетчика текущей позиции приема

      // Предотвращение загрузки старых неверных блоков данных.
      if(DataUpdate.Need_erase_flash == ENABLE)
      {
        full_erase_flash();
        DataUpdate.Need_erase_flash = DISABLE;
      }
      Data.USB_not_active = 0;  // Сброс четчика неактивности USB 

      while (Receive_length > current_rcvd_pointer)
      {
        if(current_rcvd_pointer >= VIRTUAL_COM_PORT_DATA_SIZE)
          return;
        switch (Receive_Buffer[current_rcvd_pointer])
        {
        case 0xD4:             // Отправка данных по запросу каждую минуту (RCV 1 байт)
          if(Settings.Cal_mode != 1)
            USB_send_madorc_data();
          current_rcvd_pointer++;
          break;

        case 0xE0:             // Отправка серийного номера МК (RCV 1 байт)
          USB_send_serial_data(0);
          current_rcvd_pointer++;
          break;

        case 0xE1:             // Отправка серийного номера МК (RCV 1 байт)
          USB_send_serial_data(1);
          current_rcvd_pointer++;
          break;

        case 0xE2:             // Отправка серийного номера МК (RCV 1 байт)
          USB_send_serial_data(2);
          current_rcvd_pointer++;
          break;
        case 0xE5:             // Отправка даты прошивки (RCV 1 байт)
          Send_Buffer[0] = 0xE5;        // передать ключ
          Send_Buffer[1] = __DATE__[4]; // день
          Send_Buffer[2] = __DATE__[5]; // день
          Send_Buffer[3] = __DATE__[0]; // месяц
          Send_Buffer[4] = __DATE__[1]; // месяц
          Send_Buffer[5] = __DATE__[2]; // месяц
          Send_Buffer[6] = __DATE__[10];        // год
          Send_length = 7;
          current_rcvd_pointer++;
          break;

        case 0xE6:             // Отправка версии железа (RCV 1 байт)
          Send_Buffer[0] = 0xE6;        // передать ключ
          Send_Buffer[1] = HW_REVISION[0];
          Send_Buffer[2] = HW_REVISION[1];
          Send_Buffer[3] = HW_REVISION[2];
          Send_Buffer[4] = HW_REVISION[3];
          Send_Buffer[5] = HW_REVISION[4];
          Send_Buffer[6] = 0x00;
          Send_length = 7;

          current_rcvd_pointer++;
          break;

        case 0xD5:             // Отправка метки смещения времени (RCV 1 байт)
          USB_send_time_offset_data();
          current_rcvd_pointer++;
          break;

        case 0x31:             // передача массива максимального фона (RCV 1 байт)
          Send_length = prepare_data(max_fon_select, &USB_maxfon_massive_pointer, 0xF1);        // Подготовка массива данных к передаче
          if(Send_length == 0)
            current_rcvd_pointer++;     // Если массив исчерпан
          break;

        case 0x32:             // передача массива дозы (RCV 1 байт)
          Send_length = prepare_data(dose_select, &USB_doze_massive_pointer, 0xF3);     // Подготовка массива данных к передаче
          if(Send_length == 0)
            current_rcvd_pointer++;     // Если массив исчерпан
          break;

        case 0x33:             // передача настроек (RCV 1 байт)
          USB_maxfon_massive_pointer = 0;
          USB_doze_massive_pointer = 0;
          USB_send_settings_data();
          current_rcvd_pointer++;
          break;

        case 0x34:             // передача калибровки (RCV 1 байт)
          USB_send_calibration_data();
          current_rcvd_pointer++;
          break;

        case 0x35:             // запуск калибровки (RCV 1 байт)
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

        case 0x36:             // выход из калибровки (RCV 1 байт)
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

        case 0x37:             // Загрузка данных в EEPROM (RCV 7 байт)
          if((current_rcvd_pointer + 7) <= Receive_length)      // Проверка длинны принятого участка
          {
            eeprom_loading(current_rcvd_pointer);
            current_rcvd_pointer += 7;
          } else
          {
            current_rcvd_pointer = Receive_length;      // Принято меньше чем должно быть, завершаем цикл
          }
          break;


        case 0x38:             // передача данных из EEPROM (RCV 1 байт)
          Send_length = prepare_data(eeprom_send_data, 0x00, 0xF7);     // Подготовка массива данных к передаче
          if(Send_length == 0 || eeprom_address >= 0xFF)
          {
            eeprom_address = 0;
            current_rcvd_pointer++;     // Если массив исчерпан
          }
          break;


        case 0x39:             // завершение передачи (RCV 1 байт)
          USB_maxfon_massive_pointer = 0;
          USB_doze_massive_pointer = 0;
          current_rcvd_pointer++;
          break;

        case 0xE4:             // Загрузка времени (RCV 7 байт)
          if((current_rcvd_pointer + 7) <= Receive_length)      // Проверка длинны принятого участка
          {
            time_loading(current_rcvd_pointer);
            current_rcvd_pointer += 7;
          } else
          {
            current_rcvd_pointer = Receive_length;      // Принято меньше чем должно быть, завершаем цикл
          }
          break;

        case 0xE3:             // Ключ разблокировки (RCV 5 байт)
          if((current_rcvd_pointer + 5) <= Receive_length)      // Проверка длинны принятого участка
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
            current_rcvd_pointer = Receive_length;      // Принято меньше чем должно быть, завершаем цикл
          }
          break;

        default:
          current_rcvd_pointer++;
          break;
        }

        if(Send_length > 0)     // Если пакет на передачу сформитован
        {
          wait_count = 0;
          while ((packet_sent != 1) && (wait_count < 0xFFFF))
            wait_count++;       // Проверяем передан ли прошлый пакет

          CDC_Send_DATA((unsigned char *) Send_Buffer, Send_length);
          Send_length = 0;
        }
      }
      Receive_length = 0;
    }
  }
  if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)) // если 5В на USB не подается, то отключаем его
  {

    wait_count = 0;
    while ((packet_sent != 1) && (wait_count < 0xFFFF))
      wait_count++;             // Проверяем передан ли прошлый пакет

    usb_deactivate(0x00);
  }

}



void USB_send_settings_data()
{
//---------------------------------------------КомПорт для MadOrc------------------------------------

  uint8_t count_time_hi = 0;
  uint8_t count_time_lo = 0;

  count_time_lo = Settings.Second_count & 0xff;
  count_time_hi = (Settings.Second_count >> 8) & 0xff;
  Send_Buffer[0] = 0xF5;        // передать ключь
  Send_Buffer[1] = count_time_hi;       // передать по УСАПП 
  Send_Buffer[2] = count_time_lo;       // передать по УСАПП 
  Send_Buffer[3] = 0xFF;        // передать по УСАПП 
  Send_Buffer[4] = 0xFF;        // передать по УСАПП 
  Send_Buffer[5] = 0xFF;        // передать по УСАПП 
  Send_Buffer[6] = 0xFF;        // передать по УСАПП 
  Send_Buffer[7] = 0xFF;        // передать по УСАПП 

  Send_length = 7;
}


void USB_send_calibration_data()
{
//---------------------------------------------Передача данных для калибровки------------------------------------

  uint8_t count_time_lo = 0;
  uint8_t count_time_hi = 0;
  if(Cal_count > 0)
  {
    count_time_lo = Settings.Second_count & 0xff;
    count_time_hi = (Settings.Second_count >> 8) & 0xff;
    Send_Buffer[0] = 0xF6;      // передать ключь
    Send_Buffer[1] = count_time_hi;
    Send_Buffer[2] = count_time_lo;
    Send_Buffer[3] = Data.Cal_count_mass[Cal_count - 1] & 0xff;
    Send_Buffer[4] = (Data.Cal_count_mass[Cal_count - 1] >> 8) & 0xff;
    Send_Buffer[5] = (Data.Cal_count_mass[Cal_count - 1] >> 16) & 0xff;
    Send_Buffer[6] = (Cal_count - 1) & 0xff;
  } else
  {
    Send_Buffer[0] = 0xF6;      // передать ключь
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
//---------------------------------------------Отключение USB------------------------------------
  Power.USB_active = DISABLE;
  PowerOff();
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, DISABLE);
  set_msi();

  SystemCoreClockUpdate();

  // Приводим в порядок систему тактирования (заплатка)
  //sleep_mode(ENABLE);
  //while (Power.Pump_active || Power.Sound_active);
  //PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI); // Переходим в сон
  //sleep_mode(DISABLE);

  Power.sleep_time = Settings.Sleep_time;

  GPIO_ResetBits(GPIOC, GPIO_Pin_13);   // Включаем подсветку  

  // ===============================================================================================  
  // Включаем питание модуля А
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;      // Ножка
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);        // Загружаем конфигурацию
  GPIO_SetBits(GPIOA, GPIO_InitStructure.GPIO_Pin);     // Отключаем токосемник
  // ===============================================================================================  


}


void USB_on()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  //---------------------------------------------Включение USB------------------------------------

  // ===============================================================================================  
  // Выключаем питание модуля А
  GPIO_ResetBits(GPIOA, GPIO_Pin_11 | GPIO_Pin_12);     // Отключаем токосемник
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  // ===============================================================================================  


  GPIO_SetBits(GPIOC, GPIO_Pin_13);     // Выключаем подсветку (Hi-Z)

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
