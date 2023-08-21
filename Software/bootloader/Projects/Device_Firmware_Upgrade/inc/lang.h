#ifndef __lang_H
#define __lang_H

#ifndef LANG_EN
/* *INDENT-OFF* */
///////////////////////////////////////////////////////
// Menu
#define LANG_ALARM     "�������"
#define LANG_SLEEP     "���"
#define LANG_SOUND     "����"
#define LANG_VIBRO     "�����"
#define LANG_USBMODE   "����� USB"
#define LANG_CLEARDO   "����� ����"
#define LANG_REBOOT    "�������/����"
#define LANG_CONTRAST  "��������"
#define LANG_REVERSE   "������"
#define LANG_COUNT     "����"
#define LANG_SPEED     "���������"
#define LANG_VOLTAGE   "����������"
#define LANG_OFF       "����"
#define LANG_KEY       "����"
#define LANG_QUARTZ    "�����"
#define LANG_ON        "���"
#define LANG_ALARM2    "����"
#define LANG_USEC      "%u���"
#define LANG_ACAL      "%u�/�"
#define LANG_UMKR      "%u���"
#define LANG_UMKZV     "%4.2f���"
#define LANG_FON_UMKZV "��� %4.2f���"
#define LANG_UHZ       "%u ��"
#define LANG_UHZ2       "%u��"
#define LANG_UV        "%uB"
#define LANG_V4PUMP    "�������"
#define LANG_UV4PUMP   "%u���"
#define LANG_UNITS     "�������"
#define LANG_BWINDOW   "����"
#define LANG_BWINDOW_  "%2.1fD��"
#define LANG_BPROCENT  "B-����."
#define LANG_BPROCENT_ "%3u"
#define LANG_CLEAR_FON "����� ����"
#define LANG_BETA_MEAS "����� A-B"
#define LANG_SCINT_MEAS "������-�"
#define LANG_REF_VOLT  "���.���"
#define LANG_REF_VOLT_ "%u��"
#define LANG_PUMP_AGR  "���.�����."
#define LANG_ISOTOP    "������"
#define LANG_AMODUL    "�����. ������-�"
#define LANG_BAT_CAL	 "������. ���"

#define LANG_SPECT_START  "����. ���."
#define LANG_SPECT_MULTIP "����. ���."
#define LANG_SPECT_MARK1  "C�. ����.1"
#define LANG_SPECT_MARK2  "C�. ����.2"
#define LANG_SPECT_MARK3  "C�. ����.3"
#define LANG_SPECT_MARK4  "C�. ����.4"
#define LANG_SPECT_MARK5  "C�. ����.5"
#define LANG_ISOTOP_COUNTS "������� ��"
#define LANG_ISOTOP_COUNTS_ "%u�"
#define LANG_ISOTOP_CS137    "Cs-137"
#define LANG_ISOTOP_EU152    "Eu-152"
#define LANG_ISOTOP_NA22     "Na-22"
#define LANG_ISOTOP_CD109    "Cd-109"
#define LANG_ISOTOP_AM241    "Am-241"
#define LANG_ISOTOP_Y88      "Y-88"
#define LANG_ISOTOP_TI44     "Ti-44"
#define LANG_ISOTOP_BA133    "Ba-133"
#define LANG_ISOTOP_TH228    "Th-228"

#define LANG_SPECT_MARK_TEXT1 "�������: 1:60keV"
#define LANG_SPECT_MARK_TEXT2 "2:121k 3:344k"
#define LANG_SPECT_MARK_TEXT3 "4:661k 5:>800k"


///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
// Dose
#define LANG_TIME       "�����"
#define LANG_DATE       "����"
#define LANG_MAXFON     "�������� ����"
#define LANG_DOSE10M    "���� �� 10���"
#define LANG_DOSEHOUR   "���� �� ���"
#define LANG_DOSE24H    "���� �� �����"
#define LANG_DOSEWEEK   "���� �� ������"
#define LANG_DOSEMONTH  "���� �� �����"
#define LANG_DOSE2MONTH "���� 2 ������"
#define LANG_DOSECALC   "  *������*   "
#define LANG_DOSECALCZV "  *������*   "
#define LANG_9UMKR      "%9u ���"
#define LANG_9UMKZV     "%8.2f ����"
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
// Screen
#define LANG_MENU     "      ����      "
#define LANG_STAT     "   ����������   "
#define LANG_AKB3VVV  "���  |+3�  |����"
#define LANG_PUMP     "�������"
#define LANG_IMPMINAR "���/� | �������."
#define LANG_CALC2    "������"
#define LANG_4IDN     "%4i��."

#define LANG_DALL     "�����  %5i"
#define LANG_DIMP     "���.   %5i"
#define LANG_DTIME    "����� %6i"
#define LANG_DSENS    "������ %5i"

#define LANG_ABOUT    "  � ���������   "
#define LANG_DOZIK    "  ������-������ "
#define LANG_AUTHOR   "   (c)Shodan    "
#define LANG_CITY     " �.���� 2014-17�"
#define LANG_SITE     "    misrv.com   "
#define LANG_BUILD    " ��������:"
///////////////////////////////////////////////////////

#define LANG_POWEROFF " ����������.... "

#define LANG_REBOOTPR "������������...."
#define LANG_DONTOTO1 "   �� �������   "
#define LANG_DONTOTO2 "   �� ��������! "
#define LANG_USBON    "USB �����������"
#define LANG_USBOFF   "USB  ��������"
#define LANG_ERRISO   " ��� ���������� "
#define LANG_ERRISO2  "   �� �������   "
#define LANG_ERRISO3  "    �������     "

#define LANG_BETA1    "���"
#define LANG_BETA2    "��2"
#define LANG_GAMMA1   "���"
#define LANG_GAMMA2   "���"
#define LANG_UR       "���"
#define LANG_UZ       "���"
#define LANG_UZV      "����"
#define LANG_H        " � "
///////////////////////////////////////////////////////
/* *INDENT-ON* */
#else
/* *INDENT-OFF* */
///////////////////////////////////////////////////////
// Menu
#define LANG_ALARM    "Alarm"
#define LANG_SLEEP    "Sleep"
#define LANG_SOUND    "Sound"
#define LANG_VIBRO    "Vibro"
#define LANG_USBMODE  "USB state"
#define LANG_CLEARDO  "Clr dose"
#define LANG_REBOOT   "Reboot/off"
#define LANG_CONTRAST "Contrast"
#define LANG_REVERSE  "Reverse"
#define LANG_COUNT    "Count"
#define LANG_VOLTAGE  "Voltage"
#define LANG_SPEED    "Speedup"
#define LANG_ON       "on"
#define LANG_OFF      "off"
#define LANG_KEY      "key"
#define LANG_QUARTZ   "Quarz"
#define LANG_ALARM2   "alrm"
#define LANG_USEC     "%usec"
#define LANG_ACAL     "%ui/dr"
#define LANG_UMKR     "%uuRh"
#define LANG_UMKZV    "%4.2fuSv"
#define LANG_FON_UMKZV "Dose %4.2fuSv"
#define LANG_UHZ      "%u Hz"
#define LANG_UHZ2     "%uHz"
#define LANG_UV       "%uV"
#define LANG_V4PUMP   "Pump"
#define LANG_UV4PUMP  "%uT"
#define LANG_UNITS    "Units"
#define LANG_BWINDOW  "Window"
#define LANG_BWINDOW_ "%2.1fDmm"
#define LANG_BPROCENT "B-proc."
#define LANG_BPROCENT_ "%3u"
#define LANG_CLEAR_FON "Clear rad"
#define LANG_BETA_MEAS "A-B meas."
#define LANG_SCINT_MEAS "Module-A"
#define LANG_REF_VOLT  "cal Vref"
#define LANG_REF_VOLT_ "%umV"
#define LANG_PUMP_AGR  "Pump AGR"
#define LANG_ISOTOP    "Isotop"
#define LANG_BAT_CAL	 "Batt cal."

#define LANG_ISOTOP_CS137    "Cs-137"
#define LANG_ISOTOP_EU152    "Eu-152"
#define LANG_ISOTOP_NA22     "Na-22"
#define LANG_ISOTOP_CD109    "Cd-109"
#define LANG_ISOTOP_AM241    "Am-241"
#define LANG_ISOTOP_Y88      "Y-88"
#define LANG_ISOTOP_TI44     "Ti-44"
#define LANG_ISOTOP_BA133    "Ba-133"
#define LANG_ISOTOP_TH228    "Th-228"

#define LANG_AMODUL    "Module-A act."

#define LANG_ISOTOP_COUNTS "Pulses on"
#define LANG_ISOTOP_COUNTS_ "%uI"


#define LANG_SPECT_START  "Spec.start"
#define LANG_SPECT_MULTIP "Spec.mul."
#define LANG_SPECT_MARK1  "Spec.Mark1"
#define LANG_SPECT_MARK2  "Spec.Mark2"
#define LANG_SPECT_MARK3  "Spec.Mark3"
#define LANG_SPECT_MARK4  "Spec.Mark4"
#define LANG_SPECT_MARK5  "Spec.Mark5"

#define LANG_SPECT_MARK_TEXT1 "Mark: 1:60keV"
#define LANG_SPECT_MARK_TEXT2 "2:121k 3:344k"
#define LANG_SPECT_MARK_TEXT3 "4:661k 5:>800k"


///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
// Dose
#define LANG_TIME       "Time"
#define LANG_DATE       "Date"
#define LANG_MAXFON     "Radiation max"
#define LANG_DOSE10M    "10 min dose"
#define LANG_DOSEHOUR   "Hour dose"
#define LANG_DOSE24H    "Day dose"
#define LANG_DOSEWEEK   "Week dose"
#define LANG_DOSE2MONTH "2 Month dose"
#define LANG_DOSEMONTH  "Month dose"
#define LANG_DOSECALC   " *CALC*     "
#define LANG_DOSECALCSV " *CALC*     "
#define LANG_9UMKR      "%9u uR"
#define LANG_9UMKZV     "%8.2f uSv"
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
// Screen
#define LANG_MENU     "      Menu      "
#define LANG_STAT     "   Statistic    "
#define LANG_ABOUT    "      About     "

#define LANG_AKB3VVV  "BAT  |+3V  |cnt"
#define LANG_PUMP     "Pump  "
#define LANG_IMPMINAR "imp/m | uptime  "
#define LANG_CALC2    "calc  "
#define LANG_4IDN     "%4iday"

#define LANG_DALL     "All    %5i"
#define LANG_DIMP     "Imp.   %5i"
#define LANG_DTIME    "Time  %6i"
#define LANG_DSENS    "Sensor %5i"

#define LANG_DOZIK    "  Ultra-Micron  "
#define LANG_AUTHOR   " (c)Shodan,Tula "
#define LANG_CITY     " Russia 2014-17 "
#define LANG_SITE     "    misrv.com   "
#define LANG_BUILD    " FW Build:"
///////////////////////////////////////////////////////

#define LANG_POWEROFF "Power off...... "

#define LANG_REBOOTPR "Rebooting......."
#define LANG_DONTOTO1 "  DO NOT TOUCH  "
#define LANG_DONTOTO2 "  ANY KEYS!!!   "
#define LANG_USBON    "USB enabled"
#define LANG_USBOFF   "USB disabled"
#define LANG_ERRISO   " No calibration "
#define LANG_ERRISO2  "    on this     "
#define LANG_ERRISO3  "   reference    "

#define LANG_BETA1    "par"
#define LANG_BETA2    "cm2"
#define LANG_GAMMA1   "par"
#define LANG_GAMMA2   "sec"
#define LANG_UR       "uR"
#define LANG_UZ       "uSv"
#define LANG_UZV      "uSv"
#define LANG_H        " h "
///////////////////////////////////////////////////////

/* *INDENT-ON* */
#endif
#endif
