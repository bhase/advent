EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L RF_Module:ESP32-WROOM-32 U?
U 1 1 61898C83
P 3600 3400
F 0 "U?" H 3600 4981 50  0000 C CNN
F 1 "ESP32-WROOM-32" H 3600 4890 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 3600 1900 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf" H 3300 3450 50  0001 C CNN
	1    3600 3400
	1    0    0    -1  
$EndComp
$Comp
L Driver_LED:MAX7221xNG U?
U 1 1 6189ACB9
P 6700 3050
F 0 "U?" H 6700 4231 50  0000 C CNN
F 1 "MAX7221xNG" H 6700 4140 50  0000 C CNN
F 2 "Package_DIP:DIP-24_W7.62mm" H 6650 3100 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf" H 6750 2900 50  0001 C CNN
	1    6700 3050
	1    0    0    -1  
$EndComp
$Comp
L Driver_LED:MAX7221xNG U?
U 1 1 6189B999
P 8400 3050
F 0 "U?" H 8400 4231 50  0000 C CNN
F 1 "MAX7221xNG" H 8400 4140 50  0000 C CNN
F 2 "Package_DIP:DIP-24_W7.62mm" H 8350 3100 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf" H 8450 2900 50  0001 C CNN
	1    8400 3050
	1    0    0    -1  
$EndComp
$Comp
L Driver_LED:MAX7221xNG U?
U 1 1 6189C990
P 10150 3050
F 0 "U?" H 10150 4231 50  0000 C CNN
F 1 "MAX7221xNG" H 10150 4140 50  0000 C CNN
F 2 "Package_DIP:DIP-24_W7.62mm" H 10100 3100 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf" H 10200 2900 50  0001 C CNN
	1    10150 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 3850 8000 3850
Wire Wire Line
	8800 3850 9750 3850
Wire Wire Line
	3000 3400 2650 3400
Wire Wire Line
	2650 3400 2650 5250
Wire Wire Line
	2650 5250 5700 5250
Wire Wire Line
	5700 5250 5700 3850
Wire Wire Line
	5700 3850 6300 3850
Wire Wire Line
	3000 3800 2700 3800
Wire Wire Line
	2700 3800 2700 5200
Wire Wire Line
	2700 5200 5650 5200
Wire Wire Line
	5650 5200 5650 3750
Wire Wire Line
	5650 3750 6300 3750
Wire Notes Line width 20 style solid rgb(255, 0, 0)
	4050 5050 4200 5050
Wire Notes Line width 20 style solid rgb(255, 0, 0)
	4200 5050 4200 5400
Wire Notes Line width 20 style solid rgb(255, 0, 0)
	4200 5400 4300 5400
Text Notes 3950 5050 0    50   ~ 10
Level shifting necessary
Text Notes 2950 1750 0    50   ~ 0
Note: This is a NodeMCU board\nso power supply over USB etc. available
Wire Wire Line
	5650 5200 7850 5200
Wire Wire Line
	7850 5200 7850 3750
Wire Wire Line
	7850 3750 8000 3750
Connection ~ 5650 5200
Wire Wire Line
	7850 5200 9650 5200
Wire Wire Line
	9650 5200 9650 3750
Wire Wire Line
	9650 3750 9750 3750
Connection ~ 7850 5200
Wire Wire Line
	6300 3650 5550 3650
Wire Wire Line
	5550 3650 5550 5150
Wire Wire Line
	5550 5150 7800 5150
Wire Wire Line
	7800 3650 8000 3650
Wire Wire Line
	7800 5150 9600 5150
Wire Wire Line
	9600 3650 9750 3650
Connection ~ 7800 5150
Wire Wire Line
	7800 3650 7800 5150
Wire Wire Line
	9600 3650 9600 5150
$Comp
L power:GND #PWR?
U 1 1 618C4D32
P 6700 4250
F 0 "#PWR?" H 6700 4000 50  0001 C CNN
F 1 "GND" H 6705 4077 50  0000 C CNN
F 2 "" H 6700 4250 50  0001 C CNN
F 3 "" H 6700 4250 50  0001 C CNN
	1    6700 4250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 618C8CAA
P 8400 4300
F 0 "#PWR?" H 8400 4050 50  0001 C CNN
F 1 "GND" H 8405 4127 50  0000 C CNN
F 2 "" H 8400 4300 50  0001 C CNN
F 3 "" H 8400 4300 50  0001 C CNN
	1    8400 4300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 618C92AB
P 10150 4300
F 0 "#PWR?" H 10150 4050 50  0001 C CNN
F 1 "GND" H 10155 4127 50  0000 C CNN
F 2 "" H 10150 4300 50  0001 C CNN
F 3 "" H 10150 4300 50  0001 C CNN
	1    10150 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	10150 4300 10150 4050
Wire Wire Line
	8400 4300 8400 4050
Wire Wire Line
	6700 4050 6700 4250
$Comp
L Device:R R?
U 1 1 618D24C8
P 6050 1950
F 0 "R?" H 6120 1996 50  0000 L CNN
F 1 "R" H 6120 1905 50  0000 L CNN
F 2 "" V 5980 1950 50  0001 C CNN
F 3 "~" H 6050 1950 50  0001 C CNN
	1    6050 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 618D311F
P 7800 1950
F 0 "R?" H 7870 1996 50  0000 L CNN
F 1 "R" H 7870 1905 50  0000 L CNN
F 2 "" V 7730 1950 50  0001 C CNN
F 3 "~" H 7800 1950 50  0001 C CNN
	1    7800 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 618D378E
P 9650 1900
F 0 "R?" H 9720 1946 50  0000 L CNN
F 1 "R" H 9720 1855 50  0000 L CNN
F 2 "" V 9580 1900 50  0001 C CNN
F 3 "~" H 9650 1900 50  0001 C CNN
	1    9650 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 2100 6050 2250
Wire Wire Line
	6050 2250 6300 2250
Wire Wire Line
	7800 2100 7800 2250
Wire Wire Line
	7800 2250 8000 2250
Wire Wire Line
	9650 2050 9650 2250
Wire Wire Line
	9650 2250 9750 2250
$Comp
L power:+5V #PWR?
U 1 1 618D5928
P 6700 1550
F 0 "#PWR?" H 6700 1400 50  0001 C CNN
F 1 "+5V" H 6715 1723 50  0000 C CNN
F 2 "" H 6700 1550 50  0001 C CNN
F 3 "" H 6700 1550 50  0001 C CNN
	1    6700 1550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 618D605B
P 8400 1550
F 0 "#PWR?" H 8400 1400 50  0001 C CNN
F 1 "+5V" H 8415 1723 50  0000 C CNN
F 2 "" H 8400 1550 50  0001 C CNN
F 3 "" H 8400 1550 50  0001 C CNN
	1    8400 1550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 618D685C
P 10150 1550
F 0 "#PWR?" H 10150 1400 50  0001 C CNN
F 1 "+5V" H 10165 1723 50  0000 C CNN
F 2 "" H 10150 1550 50  0001 C CNN
F 3 "" H 10150 1550 50  0001 C CNN
	1    10150 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 1550 6700 1650
Wire Wire Line
	8400 1550 8400 1650
Wire Wire Line
	10150 1550 10150 1650
Wire Wire Line
	9650 1750 9650 1650
Wire Wire Line
	9650 1650 10150 1650
Connection ~ 10150 1650
Wire Wire Line
	10150 1650 10150 2050
Wire Wire Line
	7800 1800 7800 1650
Wire Wire Line
	7800 1650 8400 1650
Connection ~ 8400 1650
Wire Wire Line
	8400 1650 8400 2050
Wire Wire Line
	6050 1800 6050 1650
Wire Wire Line
	6050 1650 6700 1650
Connection ~ 6700 1650
Wire Wire Line
	6700 1650 6700 2050
$EndSCHEMATC
