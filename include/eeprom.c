#include "stm32l1xx.h"
#include "main.h"
#include <stdio.h>
#include <string.h>

__IO FLASH_Status FLASHStatus = FLASH_COMPLETE;
__IO TestStatus DataMemoryProgramStatus = PASSED;
extern __IO uint8_t Receive_Buffer[VIRTUAL_COM_PORT_DATA_SIZE];
uint32_t NbrOfPage = 0, j = 0, Address = 0;

void eeprom_menu_working(uint32_t mode, uint32_t menu_massive)
{
  uint32_t i, max_element;
  // Выбор массива для обработки
  MenuItem *structures = NULL;

  if(menu_massive == MAIN_MENU)
  {
    max_element = max_struct_index;
    structures = Menu_list;
  }

  if(menu_massive == MODUL_MENU)
  {
    max_element = modul_max_struct_index;
    structures = Modul_Menu_list;
  }

  if(mode == READ)
  {
    for (i = 0; i < max_element; i++)   // проход всех строк основного меню
    {
      if(structures[i].EEPROM_address == 0xFFFF)
      {
        if(structures[i].Parameter_value > 0)
        {
          *structures[i].Parameter_value = structures[i].Value_default;
        }
      } else
      {
        if(eeprom_read(structures[i].EEPROM_address) != *structures[i].Parameter_value)
        {                       // Если значение параметра не соответствует тому что в памяти, прочитать его из еепром
          *structures[i].Parameter_value = eeprom_read(structures[i].EEPROM_address);
          // Если значение не укладывается в приделы минимума-максмума, сбросить по умолчанию
          if((*structures[i].Parameter_value > structures[i].Max_limit) || (*structures[i].Parameter_value < structures[i].Min_limit))
          {
            *structures[i].Parameter_value = structures[i].Value_default;
            eeprom_write(structures[i].EEPROM_address, *structures[i].Parameter_value);
          }
          // Выполнить обработчик изменений параметра
          eeprom_apply_settings(structures[i].EEPROM_address);
        }
      }
    }
  }

  if(mode == WRITE)
  {
    for (i = 0; i < max_element; i++)   // проход всех строк основного меню
    {
      if(structures[i].EEPROM_address != 0xFFFF)
      {
        if(eeprom_read(structures[i].EEPROM_address) != *structures[i].Parameter_value)
        {                       // Если значение параметра не соответствует тому что в памяти, записать его в еепром
          // Если значение не укладывается в приделы минимума-максмума, сбросить по умолчанию
          if((*structures[i].Parameter_value > structures[i].Max_limit) || (*structures[i].Parameter_value < structures[i].Min_limit))
          {
            *structures[i].Parameter_value = structures[i].Value_default;
          }
          // Выполнить запись и обработчик изменений параметра
          eeprom_write(structures[i].EEPROM_address, *structures[i].Parameter_value);
          eeprom_apply_settings(structures[i].EEPROM_address);
        }
      }
    }
  }

}

//**************************************************************************
// Запись параметров по умолчанию
void eeprom_write_default_settings(void)
{
  if(eeprom_read(Isotop_count_cs137_address) == 0x00)
  {
    Settings.Power_comp = 0;
    Settings.Isotop_count_cs137 = 250;
    Settings.Isotop_count_eu152 = 250;
    Settings.Isotop_count_na22 = 250;
    Settings.Isotop_count_cd109 = 250;
    Settings.Isotop_count_am241 = 250;
    Settings.Isotop_count_ti44 = 250;
    Settings.Isotop_count_y88 = 250;
    Settings.Isotop_count_ba133 = 250;
    Settings.Isotop_count_th228 = 250;

    eeprom_write_settings(MAIN_MENU);   // Запись
    eeprom_write_settings(MODUL_MENU);  // Запись
  }
}

//**************************************************************************

void eeprom_write_settings(uint32_t menu_massive)
{

  eeprom_menu_working(WRITE, menu_massive);

  if(eeprom_read(VRef_address) != Settings.VRef)
    eeprom_write(VRef_address, Settings.VRef);

  //Запись параметров в EEPROM
  if(eeprom_read(Power_comp_address) != Settings.Power_comp)
    eeprom_write(Power_comp_address, Settings.Power_comp);



  if(eeprom_read(Isotop_count_cs137_address) != Settings.Isotop_count_cs137)
    eeprom_write(Isotop_count_cs137_address, Settings.Isotop_count_cs137);
  if(eeprom_read(Isotop_count_eu152_address) != Settings.Isotop_count_eu152)
    eeprom_write(Isotop_count_eu152_address, Settings.Isotop_count_eu152);
  if(eeprom_read(Isotop_count_na22_address) != Settings.Isotop_count_na22)
    eeprom_write(Isotop_count_na22_address, Settings.Isotop_count_na22);
  if(eeprom_read(Isotop_count_cd109_address) != Settings.Isotop_count_cd109)
    eeprom_write(Isotop_count_cd109_address, Settings.Isotop_count_cd109);
  if(eeprom_read(Isotop_count_am241_address) != Settings.Isotop_count_am241)
    eeprom_write(Isotop_count_am241_address, Settings.Isotop_count_am241);
  if(eeprom_read(Isotop_count_ti44_address) != Settings.Isotop_count_ti44)
    eeprom_write(Isotop_count_ti44_address, Settings.Isotop_count_ti44);
  if(eeprom_read(Isotop_count_y88_address) != Settings.Isotop_count_y88)
    eeprom_write(Isotop_count_y88_address, Settings.Isotop_count_y88);
  if(eeprom_read(Isotop_count_ba133_address) != Settings.Isotop_count_ba133)
    eeprom_write(Isotop_count_ba133_address, Settings.Isotop_count_ba133);
  if(eeprom_read(Isotop_count_th228_address) != Settings.Isotop_count_th228)
    eeprom_write(Isotop_count_th228_address, Settings.Isotop_count_th228);
}

//**************************************************************************
void eeprom_apply_settings(uint32_t addr)
{

  if(addr == 0xFFFF)
    return;

  // контраст и реверс дисплея
  if((addr == 0x0C) || (addr == 0x08))
  {
    display_off();
    delay_ms(200);
    display_on();
  }
  // Длительность накачки, частота звука
  if((addr == 0x54) || (addr == 0xF0))
  {
    reset_TIM_prescallers_and_Compare();
  }
  // Все пункты меню, где требуется перезагрузка времени и параметров счета фона
  if((addr == 0x80) || (addr == 0xE8) || (addr == 0x94) || (addr == 0x98) || (addr == 0x9C) ||
     (addr == 0xA0) || (addr == 0xC4) || (addr == 0xD4) || (addr == 0xCC) || (addr == 0xDC) || (addr == 0xE4) || (addr == 0xEC))
  {
    reload_active_isotop_time();
  }
  // -------------------------------------------------------------------
  if((eeprom_read(Isotop_count_cs137_address) != Settings.Isotop_count_cs137) ||
     (eeprom_read(Isotop_count_eu152_address) != Settings.Isotop_count_eu152) ||
     (eeprom_read(Isotop_count_na22_address) != Settings.Isotop_count_na22) ||
     (eeprom_read(Isotop_count_cd109_address) != Settings.Isotop_count_cd109) ||
     (eeprom_read(Isotop_count_am241_address) != Settings.Isotop_count_am241) ||
     (eeprom_read(Isotop_count_ti44_address) != Settings.Isotop_count_ti44) ||
     (eeprom_read(Isotop_count_y88_address) != Settings.Isotop_count_y88) ||
     (eeprom_read(Isotop_count_ba133_address) != Settings.Isotop_count_ba133) ||
     (eeprom_read(Isotop_count_th228_address) != Settings.Isotop_count_th228))
  {
    reload_active_isotop_time();
  }
  // -------------------------------------------------------------------

}

//**************************************************************************

void eeprom_read_settings(uint32_t menu_massive)
{

  eeprom_menu_working(READ, menu_massive);

  //Чтение параметров из EEPROM
  Settings.VRef = eeprom_read(VRef_address);
  if(Settings.VRef == 0)
    Settings.VRef = 1224;

  Settings.Power_comp = eeprom_read(Power_comp_address);
  Settings.serial0 = eeprom_read(unlock_0_address);
  Settings.serial1 = eeprom_read(unlock_1_address);
  Settings.serial2 = eeprom_read(unlock_2_address);
  Settings.serial3 = eeprom_read(unlock_3_address);
  Settings.Isotop_count_cs137 = eeprom_read(Isotop_count_cs137_address);
  Settings.Isotop_count_eu152 = eeprom_read(Isotop_count_eu152_address);
  Settings.Isotop_count_na22 = eeprom_read(Isotop_count_na22_address);
  Settings.Isotop_count_cd109 = eeprom_read(Isotop_count_cd109_address);
  Settings.Isotop_count_ti44 = eeprom_read(Isotop_count_ti44_address);
  Settings.Isotop_count_y88 = eeprom_read(Isotop_count_y88_address);
  Settings.Isotop_count_ba133 = eeprom_read(Isotop_count_ba133_address);
  Settings.Isotop_count_th228 = eeprom_read(Isotop_count_th228_address);
  Settings.Isotop_count_am241 = eeprom_read(Isotop_count_am241_address);
}

///////////////////////////////////////////////////////////////////////////
void cal_write(void)
{
  uint32_t address = 0;
  uint32_t i = 0;

  address = Batt_cal_massive_address + (bat_cal_running * 0x04);

  if(bat_cal_running == 1)
  {
    for (i = Batt_cal_massive_address; i < Batt_cal_massive_end_address; i += 0x04)
    {
      eeprom_write(i, 0x00);
    }
  }

  if(bat_cal_running > 0)
  {
    if(address < Batt_cal_massive_end_address)
      eeprom_write(address, ADCData.Batt_voltage);
  }

  bat_cal_running++;

}

uint32_t cal_read(uint32_t voltage)
{
  uint32_t address = 0;
  uint32_t data = 0;
  uint32_t i = 0;
  uint32_t end_massive = 0;
  uint32_t tmp = 0;

  address = Batt_cal_massive_address;

  while (address < Batt_cal_massive_end_address)
  {
    i += 0x04;
    address = Batt_cal_massive_address + i;

    data = eeprom_read(address);
    if(data > 0)
    {
      end_massive++;
      if(voltage <= data)
        tmp++;
    } else
    {
      break;
    }
  }

  if(end_massive == 0)
    return 0;                   // На ноль делить нельзя

  tmp = (100 * tmp) / end_massive;
  if(tmp > 100)
    tmp = 100;

  return 100 - tmp;

}


///////////////////////////////////////////////////////////////////////////
void eeprom_loading(uint32_t current_rcvd_pointer)      // Запись в EEPROM
{
  uint16_t eeprom_write_address;
  uint32_t eeprom_data;
  if(current_rcvd_pointer + 7 >= VIRTUAL_COM_PORT_DATA_SIZE)
    return;

  eeprom_write_address = (Receive_Buffer[current_rcvd_pointer + 1] & 0xff);
  eeprom_write_address += ((Receive_Buffer[current_rcvd_pointer + 2] & 0xff) << 8);

  eeprom_data = (Receive_Buffer[current_rcvd_pointer + 3] & 0xff);
  eeprom_data += ((Receive_Buffer[current_rcvd_pointer + 4] & 0xff) << 8);
  eeprom_data += ((Receive_Buffer[current_rcvd_pointer + 5] & 0xff) << 16);
  eeprom_data += ((Receive_Buffer[current_rcvd_pointer + 6] & 0xff) << 24);

  if(eeprom_read(eeprom_write_address) != eeprom_data)
  {
    eeprom_write(eeprom_write_address, eeprom_data);
    eeprom_read_settings(MAIN_MENU);
    eeprom_read_settings(MODUL_MENU);
    reload_active_isotop_time();
  }

}


//**************************************************************************
void eeprom_erase(void)
{
  DATA_EEPROM_Unlock();         // разблокировка перед записью

  /* Clear all pending flags */
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR | FLASH_FLAG_OPTVERRUSR);

  /*  Data EEPROM Fast Word program of FAST_DATA_32 at addresses defined by 
     DATA_EEPROM_START_ADDR and DATA_EEPROM_END_ADDR */
  Address = DATA_EEPROM_START_ADDR;

  NbrOfPage = ((DATA_EEPROM_END_ADDR - Address) + 1) >> 2;

  /* Erase the Data EEPROM Memory pages by Word (32-bit) */
  for (j = 0; j < NbrOfPage; j++)
  {
    FLASHStatus = DATA_EEPROM_EraseWord(Address + (4 * j));
  }
  DATA_EEPROM_Lock();

  /* Check the correctness of written data */
  while (Address < DATA_EEPROM_END_ADDR)
  {
    if(*(__IO uint32_t *) Address != 0x0)
    {
      DataMemoryProgramStatus = FAILED;
      //ОШИБКА стирания !!!!
      return;
    }
    Address = Address + 4;
  }

}



//************************************************************************
uint32_t eeprom_read(uint32_t address_of_read)
{

  /* Clear all pending flags */
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR | FLASH_FLAG_OPTVERRUSR);

  /*  Data EEPROM Fast Word program of FAST_DATA_32 at addresses defined by 
     DATA_EEPROM_START_ADDR and DATA_EEPROM_END_ADDR */
  Address = DATA_EEPROM_START_ADDR + address_of_read;
  if(Address > DATA_EEPROM_END_ADDR)
  {
    // ОШИБКА вне диапазона eeprom !!!!
    return 0x00;
  }
  // чтение данных
  return *(__IO uint32_t *) Address;
}



//************************************************************************

void eeprom_write(uint32_t address_of_read, uint32_t data)
{

  DATA_EEPROM_Unlock();         // разблокировка перед записью

  /* Clear all pending flags */
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR | FLASH_FLAG_OPTVERRUSR);

  /*  Data EEPROM Fast Word program of FAST_DATA_32 at addresses defined by 
     DATA_EEPROM_START_ADDR and DATA_EEPROM_END_ADDR */
  Address = DATA_EEPROM_START_ADDR + address_of_read;
  if(Address > DATA_EEPROM_END_ADDR)
  {
    // ОШИБКА вне диапазона eeprom !!!!
    DATA_EEPROM_Lock();
    return;
  }
  // Запись данных по адресу
  FLASHStatus = DATA_EEPROM_ProgramWord(Address, data);
  DATA_EEPROM_Lock();

  if(FLASHStatus != FLASH_COMPLETE)
  {
    // ОШИБКА записи eeprom !!!!
    return;
  }
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR);


  // Проверка записанных данных 
  if(*(__IO uint32_t *) Address != data)
  {
    DataMemoryProgramStatus = FAILED;
    // ОШИБКА записи !!!!!
    return;
  }



}
