#ifndef __menu_user_H
#define __menu_user_H
#include <STM32L1xx.h>

#define max_string_len 16       // ������������ ������ ������
#define max_string_count 8      // ������������ ���������� �����
#define max_public_string_count 10      // ������������ ���������� ����� ���������� ����
#define max_struct_index 21     // ������������ ���������� ������� ����
#define start_offset 2          // �� ������� ����� �������� ���� ����

#define modul_max_struct_index 12       // ������������ ���������� ������� ����


#define NORMAL_menu_mode 0
#define AMODUL_menu_mode 1

typedef struct
{
  int8_t Hide;
  uint16_t EEPROM_address;
  char Text[17];
  char Param_is_0[10];
  char Param_is_1[10];
  char Param_is_N[10];
  uint32_t *Parameter_value;
  uint32_t Min_limit;
  uint32_t Max_limit;
  uint32_t Value_default;
  void (*Plus_reaction) (uint32_t *);
  int16_t Plus_value;
  void (*Minus_reaction) (uint32_t *);
  int16_t Minus_value;

} MenuItem;

void main_screen(void);
void menu_screen(uint32_t);
void stat_screen(void);
void amodul_screen(void);

extern MenuItem Menu_list[];
extern MenuItem Modul_Menu_list[];

#endif
