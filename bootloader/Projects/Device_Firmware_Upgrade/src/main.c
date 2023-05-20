/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Device Firmware Upgrade(DFU) demo main file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/

#include "hw_config.h" 
#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_prop.h"
#include "usb_pwr.h"
#include "dfu_mal.h"
#include "delay.h"
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
typedef  void (*pFunction)(void);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
uint8_t DeviceState;
uint8_t DeviceStatus[6];
pFunction Jump_To_Application;
uint32_t JumpAddress;

SettingsDef Settings;
PowerDef Power;

extern char lcd_buf[20];

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : main.
* Description    : main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int main(void)
{
  
GPIO_InitTypeDef   GPIO_InitStructure;

RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);  

GPIO_StructInit(&GPIO_InitStructure);
GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOA, &GPIO_InitStructure);
GPIO_SetBits(GPIOA,GPIO_Pin_7);// ������������� ���������� �� 3 ������
delay_ms(100);
  
  DFU_Button_Config();
  
  /* Check if the Key push-button on STM3210x-EVAL Board is pressed */
  if(RTC_ReadBackupRegister(RTC_BKP_DR1) != 0x1234)
  {
    if (DFU_Button_Read() != 0x00)
    { /* Test if user code is programmed starting from address 0x8003000 */
      if (((*(__IO uint32_t*)ApplicationAddress) & 0x2FFE0000 ) == 0x20000000)
      { /* Jump to user application */
  
        JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);
        Jump_To_Application = (pFunction) JumpAddress;
        /* Initialize user application's Stack Pointer */
        __set_MSP(*(__IO uint32_t*) ApplicationAddress);
        Jump_To_Application();
      }
    } /* Otherwise enters DFU mode to allow user to program his application */
  } else
  {
    RTC_WriteBackupRegister(RTC_BKP_DR1,0x0);
  }

  Settings.Display_reverse=2;
  display_on();
  
  lcd_buf[0] = 'D';
  lcd_buf[1] = 'F';
  lcd_buf[2] = 'U';
  lcd_buf[3] = ' ';
  lcd_buf[4] = 'M';
  lcd_buf[5] = 'o';
  lcd_buf[6] = 'd';
  lcd_buf[7] = 'e';
  
  LcdString(1, 1);


  LcdUpdate();
  
  delay_ms(2000);

#if defined (USE_STM32L152D_EVAL)
  FLASH_Unlock();
  FLASH_ClearFlag(FLASH_FLAG_OPTVERRUSR);
#endif


  /* Enter DFU mode */
  DeviceState = STATE_dfuERROR;
  DeviceStatus[0] = STATUS_ERRFIRMWARE;
  DeviceStatus[4] = DeviceState;

  Set_System();
  Set_USBClock();
  USB_Init();  
  
  /* Main loop */
  
  while (1)
  {

  }
}


#ifdef USE_FULL_ASSERT
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
