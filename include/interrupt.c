#include "main.h"



// =======================================================
// ������������� ���������� ������� 1
void EXTI5_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;

  // ��������� �����
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);   // ������ ������������ �� ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // ����� ����� "����"
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;      // ��� ��������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;     // ����� ����� � �����
  GPIO_Init(GPIOB, &GPIO_InitStructure);        // ���������� ������������

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);        // ������ ������������ �� SYSCFG
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource5); // ���������� EXTI � �����

  // ��������� EXTI
  EXTI_InitStructure.EXTI_Line = EXTI_Line5;    // ����� EXTI
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;   // ����� ����������
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;        // ������� �� ������������ ������
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;     // ��������
  EXTI_Init(&EXTI_InitStructure);       // ���������� ������������

  // ��������� ����� ����������
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;    // �����
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

// =======================================================
// ������������� ���������� ������� 2
void EXTI10_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;

  // ��������� �����
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);   // ������ ������������ �� ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // ����� ����� "����"
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;      // ��� ��������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;     // ����� ����� � �����
  GPIO_Init(GPIOB, &GPIO_InitStructure);        // ���������� ������������

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);        // ������ ������������ �� SYSCFG
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource10); // ���������� EXTI � �����

  // ��������� EXTI
  EXTI_InitStructure.EXTI_Line = EXTI_Line10;    // ����� EXTI
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;   // ����� ����������
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;        // ������� �� ������������ ������
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;     // ��������
  EXTI_Init(&EXTI_InitStructure);       // ���������� ������������

  // ��������� ����� ����������
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;    // �����
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

// =======================================================
// ������������� ���������� ��������� USB
void EXTI9_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;

  // ��������� �����
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);   // ������ ������������ �� ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // ����� ����� "����"
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;      // ��� ��������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;     // ����� ����� � �����
  GPIO_Init(GPIOA, &GPIO_InitStructure);        // ���������� ������������

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);        // ������ ������������ �� SYSCFG
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource9); // ���������� EXTI � �����

  // ��������� EXTI
  EXTI_InitStructure.EXTI_Line = EXTI_Line9;    // ����� EXTI
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;   // ����� ����������
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;        // ������� �� ������������ ������
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;     // ��������
  EXTI_Init(&EXTI_InitStructure);       // ���������� ������������

  // ��������� ����� ����������
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;    // �����
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

// =======================================================
// ������������� ���������� �� ������� ������ 0 (Menu)
void EXTI1_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;

  // ��������� �����
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);   // ������ ������������ �� ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // ����� ����� "����"
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // �������� � +
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;     // ����� ����� � �����
  GPIO_Init(GPIOB, &GPIO_InitStructure);        // ���������� ������������

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);        // ������ ������������ �� SYSCFG
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource1); // ���������� EXTI � �����

  // ��������� EXTI
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;    // ����� EXTI
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;   // ����� ����������
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;       // ������� �� ���������� ������
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;     // ��������
  EXTI_Init(&EXTI_InitStructure);       // ���������� ������������

  // ��������� ����� ����������
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;      // �����
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


// =======================================================
// ������������� ���������� �� ������-�
/*void EXTI1_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;

  // ��������� �����
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);   // ������ ������������ �� ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // ����� ����� "����"
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;        // �������� � +
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;     // ����� ����� � �����
  GPIO_Init(GPIOA, &GPIO_InitStructure);        // ���������� ������������

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);        // ������ ������������ �� SYSCFG
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource3); // ���������� EXTI � �����

  // ��������� EXTI
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;    // ����� EXTI
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;   // ����� ����������
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;        // ������� �� ���������� ������
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;     // ��������
  EXTI_Init(&EXTI_InitStructure);       // ���������� ������������

  // ��������� ����� ����������
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;      // �����
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}*/

// =======================================================
// ������������� ���������� �� ������� ������ 1 (-)
void EXTI2_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;

  // ��������� �����
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);   // ������ ������������ �� ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // ����� ����� "����"
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // �������� � +
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;     // ����� ����� � �����
  GPIO_Init(GPIOB, &GPIO_InitStructure);        // ���������� ������������

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);        // ������ ������������ �� SYSCFG
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource2); // ���������� EXTI � �����

  // ��������� EXTI
  EXTI_InitStructure.EXTI_Line = EXTI_Line2;    // ����� EXTI
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;   // ����� ����������
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;       // ������� �� ���������� ������
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;     // ��������
  EXTI_Init(&EXTI_InitStructure);       // ���������� ������������

  // ��������� ����� ����������
  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;      // �����
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


// =======================================================
// ������������� ���������� �� ������� ������ 2 (+)
void EXTI0_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;

  // ��������� �����
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);   // ������ ������������ �� ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  // ����� ����� "����"
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  // �������� � +
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;     // ����� ����� � �����
  GPIO_Init(GPIOB, &GPIO_InitStructure);        // ���������� ������������

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);        // ������ ������������ �� SYSCFG
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource0); // ���������� EXTI � �����

  // ��������� EXTI
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;    // ����� EXTI
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;   // ����� ����������
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;       // ������� �� ���������� ������
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;     // ��������
  EXTI_Init(&EXTI_InitStructure);       // ���������� ������������

  // ��������� ����� ����������
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;    // �����
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
