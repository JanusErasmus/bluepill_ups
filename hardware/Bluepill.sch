EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
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
L Bluepill:BluePill_STM32F103C U?
U 1 1 5C14BC04
P 5650 3750
F 0 "U?" H 5675 2278 50  0000 C CNN
F 1 "BluePill_STM32F103C" H 5675 2187 50  0000 C CNN
F 2 "BluePill_breakouts:BluePill_STM32F103C" H 5700 2150 50  0001 C CNN
F 3 "www.rogerclark.net" H 5650 2250 50  0001 C CNN
	1    5650 3750
	1    0    0    -1  
$EndComp
Text Label 7650 3350 0    50   ~ 0
TM1637_DI0
Text Label 7650 3450 0    50   ~ 0
TM1637_CLK
$Comp
L TinkerForge:TM1637_MODULE U?
U 1 1 5C14BC0D
P 8950 3650
F 0 "U?" H 8550 4100 60  0000 L CNN
F 1 "TM1637_MODULE" H 8900 3800 60  0000 L CNN
F 2 "" H 8950 3650 60  0000 C CNN
F 3 "" H 8950 3650 60  0000 C CNN
	1    8950 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 3350 8350 3350
Wire Wire Line
	6550 3450 8350 3450
Wire Wire Line
	8350 3550 8250 3550
Wire Wire Line
	8250 3550 8250 2900
$Comp
L power:GNDREF #PWR?
U 1 1 5C14BC18
P 8250 4000
F 0 "#PWR?" H 8250 3750 50  0001 C CNN
F 1 "GNDREF" H 8255 3827 50  0001 C CNN
F 2 "" H 8250 4000 50  0001 C CNN
F 3 "" H 8250 4000 50  0001 C CNN
	1    8250 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 3650 8250 3650
Wire Wire Line
	8250 3650 8250 4000
$Comp
L Bluepill:NRF24L01_Breakout U?
U 1 1 5C14BC20
P 2150 4150
F 0 "U?" H 2628 4128 50  0000 L CNN
F 1 "NRF24L01_Breakout" H 2628 4037 50  0000 L CNN
F 2 "RF_Module:nRF24L01_Breakout" H 2300 4750 50  0001 L CIN
F 3 "http://www.nordicsemi.com/eng/content/download/2730/34105/file/nRF24L01_Product_Specification_v2_0.pdf" H 2150 4050 50  0001 C CNN
	1    2150 4150
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4800 3950 2650 3950
Wire Wire Line
	2650 3850 4800 3850
Wire Wire Line
	2650 4050 4800 4050
Wire Wire Line
	4800 4150 2650 4150
Wire Wire Line
	2650 4250 4800 4250
Wire Wire Line
	2650 4350 4800 4350
$Comp
L power:GNDREF #PWR?
U 1 1 5C14BC2D
P 2150 4800
F 0 "#PWR?" H 2150 4550 50  0001 C CNN
F 1 "GNDREF" H 2155 4627 50  0001 C CNN
F 2 "" H 2150 4800 50  0001 C CNN
F 3 "" H 2150 4800 50  0001 C CNN
	1    2150 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 4750 2150 4800
$Comp
L power:+5V #PWR?
U 1 1 5C14BC34
P 8250 2900
F 0 "#PWR?" H 8250 2750 50  0001 C CNN
F 1 "+5V" H 8265 3073 50  0000 C CNN
F 2 "" H 8250 2900 50  0001 C CNN
F 3 "" H 8250 2900 50  0001 C CNN
	1    8250 2900
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5C14BC3A
P 6650 3250
F 0 "#PWR?" H 6650 3100 50  0001 C CNN
F 1 "+5V" V 6650 3400 50  0000 L CNN
F 2 "" H 6650 3250 50  0001 C CNN
F 3 "" H 6650 3250 50  0001 C CNN
	1    6650 3250
	0    1    1    0   
$EndComp
$Comp
L power:GNDREF #PWR?
U 1 1 5C14BC40
P 7000 3150
F 0 "#PWR?" H 7000 2900 50  0001 C CNN
F 1 "GNDREF" H 7005 2977 50  0001 C CNN
F 2 "" H 7000 3150 50  0001 C CNN
F 3 "" H 7000 3150 50  0001 C CNN
	1    7000 3150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7000 3150 6550 3150
Wire Wire Line
	6650 3250 6550 3250
Text Label 3250 3850 0    50   ~ 0
SP1_CS
Text Label 3250 3950 0    50   ~ 0
SPI1_SCK
Text Label 3250 4050 0    50   ~ 0
SPI1_MISO
Text Label 3250 4150 0    50   ~ 0
SPI1_MOSI
Text Label 3250 4250 0    50   ~ 0
NRF_IRQ
Text Label 3250 4350 0    50   ~ 0
NRF_CE
$Comp
L power:+3.3V #PWR?
U 1 1 5C14BC4E
P 2150 3300
F 0 "#PWR?" H 2150 3150 50  0001 C CNN
F 1 "+3.3V" H 2165 3473 50  0000 C CNN
F 2 "" H 2150 3300 50  0001 C CNN
F 3 "" H 2150 3300 50  0001 C CNN
	1    2150 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 3300 2150 3550
$Comp
L power:+3.3V #PWR?
U 1 1 5C14BC55
P 6650 3050
F 0 "#PWR?" H 6650 2900 50  0001 C CNN
F 1 "+3.3V" V 6665 3178 50  0000 L CNN
F 2 "" H 6650 3050 50  0001 C CNN
F 3 "" H 6650 3050 50  0001 C CNN
	1    6650 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	6650 3050 6550 3050
$Comp
L power:GNDREF #PWR?
U 1 1 5C14BC5C
P 4650 5050
F 0 "#PWR?" H 4650 4800 50  0001 C CNN
F 1 "GNDREF" H 4655 4877 50  0001 C CNN
F 2 "" H 4650 5050 50  0001 C CNN
F 3 "" H 4650 5050 50  0001 C CNN
	1    4650 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 4850 4650 4850
Wire Wire Line
	4650 4850 4650 4950
Wire Wire Line
	4800 4950 4650 4950
Connection ~ 4650 4950
Wire Wire Line
	4650 4950 4650 5050
Wire Wire Line
	4800 3450 3350 3450
Wire Wire Line
	4800 3550 3350 3550
Text Label 3800 3450 0    50   ~ 0
ADC_CH0
Text Label 3800 3550 0    50   ~ 0
ADC_CH1
$EndSCHEMATC