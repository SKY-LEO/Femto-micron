#include "stm32l1xx.h"
#include "main.h"


__IO FLASH_Status FLASHStatus_eeprom = FLASH_COMPLETE;
__IO TestStatus MemoryProgramStatus_eeprom = PASSED;


//////////////////////////////////////////////////////////////////////////////////////
void full_erase_flash(void)     // Erase full dataflash
{
  uint32_t j = 0, Address = 0, NbrOfPage = 0, tmp = 0;

  /* Unlock the FLASH Program memory */
  FLASH_Unlock();

  /* Clear all pending flags */
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR | FLASH_FLAG_OPTVERRUSR);

  Address = FLASH_START_ADDR;
  NbrOfPage = ((FLASH_END_ADDR - Address) + 1) >> 8;
  /* Erase the FLASH Program memory pages */
  for (j = 0; j < NbrOfPage; j++)
  {
    tmp = Address + (FLASH_PAGE_SIZE * j);
    if(tmp > FLASH_END_ADDR)
    {
      FLASH_Lock();
      return;
    }
    if(tmp < FLASH_START_ADDR)
    {
      FLASH_Lock();
      return;
    }

    FLASHStatus_eeprom = FLASH_ErasePage(tmp);

    if(FLASHStatus_eeprom != FLASH_COMPLETE)
    {
      MemoryProgramStatus_eeprom = FAILED;
    } else
    {
      FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR | FLASH_FLAG_OPTVERRUSR);
    }
  }

  FLASH_Lock();
}

//////////////////////////////////////////////////////////////////////////////////////
void page_erase_flash(uint32_t page)    // Erase 32 elements
{
  uint32_t Address = 0;
  if(FLASH_MAX_PAGE >= page)    // ���� �� �� ��������� ���������
  {

    /* Unlock the FLASH Program memory */
    FLASH_Unlock();

    /* Clear all pending flags */
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR | FLASH_FLAG_OPTVERRUSR);

    Address = FLASH_START_ADDR + (page * FLASH_PAGE_SIZE);
    /* Erase the FLASH Program memory pages */

    if(Address > FLASH_END_ADDR)
    {
      FLASH_Lock();
      return;
    }
    if(Address < FLASH_START_ADDR)
    {
      FLASH_Lock();
      return;
    }

    FLASHStatus_eeprom = FLASH_ErasePage(Address);

    if(FLASHStatus_eeprom != FLASH_COMPLETE)
    {
      MemoryProgramStatus_eeprom = FAILED;
    } else
    {
      FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR | FLASH_FLAG_OPTVERRUSR);
    }

    FLASH_Lock();
  }
}

//////////////////////////////////////////////////////////////////////////////////////
void flash_write_page(uint32_t page)    // Write 32 element of massive ram_Doze_massive and ram_max_fon_massive
{
  uint32_t Address = 0;

  if(FLASH_MAX_PAGE >= page)    // ���� �� �� ��������� ���������
  {

    Address = FLASH_START_ADDR + (page * FLASH_PAGE_SIZE);

    page_erase_flash(page);     // ������� �������� ����� �������

    /* Unlock the FLASH Program memory */
    FLASH_Unlock();

    /* Clear all pending flags */
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR | FLASH_FLAG_OPTVERRUSR);

    /* Write the FLASH Program memory using HalfPage operation */

    if(Address > FLASH_END_ADDR)
    {
      FLASH_Lock();
      return;
    }
    if(Address < FLASH_START_ADDR)
    {
      FLASH_Lock();
      return;
    }

    FLASHStatus_eeprom = FLASH_ProgramHalfPage(Address, ram_Doze_massive);

    if(FLASHStatus_eeprom == FLASH_COMPLETE)
    {
    } else
    {
      FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR | FLASH_FLAG_OPTVERRUSR);
    }

    Address += FLASH_PAGE_SIZE >> 1;
    /* Write the FLASH Program memory using HalfPage operation */

    if(Address > FLASH_END_ADDR)
    {
      FLASH_Lock();
      return;
    }
    if(Address < FLASH_START_ADDR)
    {
      FLASH_Lock();
      return;
    }

    FLASHStatus_eeprom = FLASH_ProgramHalfPage(Address, ram_max_fon_massive);

    if(FLASHStatus_eeprom == FLASH_COMPLETE)
    {
    } else
    {
      FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR | FLASH_FLAG_OPTVERRUSR);
    }

    FLASH_Lock();
  }
}


//////////////////////////////////////////////////////////////////////////////////////
uint32_t flash_read_massive(uint32_t virt_element, uint32_t mode)
{
  uint32_t Address = FLASH_START_ADDR, page = 0, page_num = 0, index = 0;

  if(virt_element >= FLASH_MAX_ELEMENT)
    return 0;                   // �������� ��������� ���������

  if(virt_element < doze_length)        // 0-31
  {
    if(mode == max_fon_select)
      return ram_max_fon_massive[virt_element];
    if(mode == dose_select)
      return ram_Doze_massive[virt_element];

  } else                        // >31 ������� �� �� ������, ����� �� ������
  {
/*	x<<1 = *2
		x<<2 = *4
		x<<5 = *32
		x<<8 = *256
*/

    index = virt_element - (DataUpdate.doze_count + 1);
    page = DataUpdate.current_flash_page;
//////////////////////////////////////////////////
    //page_num=index/doze_length; // �� �����������
    page_num = index >> 5;      // ������� ������� ���� ������ // /32

    if(page_num > page)
    {
      page = FLASH_MAX_PAGE + page - page_num;
    }                           // ���� ���� ������ ������ ����� ������, �� ��������������� �����
    else
    {
      page = page - page_num - 1;
    }

    //������� �� �������
    //index=index-(page_num*doze_length); // �� �����������
    index = index - (page_num << 5);    // *32

    // �� �����������
    //if(mode == max_fon_select) Address = FLASH_START_ADDR + (FLASH_PAGE_SIZE/2) + (page * FLASH_PAGE_SIZE) + (index*4); // ��������� ����� ������ ��������
    //if(mode == dose_select)    Address = FLASH_START_ADDR +                       (page * FLASH_PAGE_SIZE) + (index*4); // ��������� ����� ������ ��������
    if(mode == max_fon_select)
      Address = FLASH_START_ADDR + (FLASH_PAGE_SIZE >> 1) + (page << 8) + (index << 2); // ��������� ����� ������ ��������
    if(mode == dose_select)
      Address = FLASH_START_ADDR + (page << 8) + (index << 2);  // ��������� ����� ������ ��������
    if(Address < FLASH_START_ADDR)
      return 0;
    if(Address > FLASH_END_ADDR)
      return 0;

    return (*(__IO uint32_t *) Address);
  }
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////
