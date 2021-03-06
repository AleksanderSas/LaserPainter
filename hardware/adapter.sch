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
L power:GND #PWR?
U 1 1 6063FB8C
P 4900 5200
F 0 "#PWR?" H 4900 4950 50  0001 C CNN
F 1 "GND" H 4905 5027 50  0000 C CNN
F 2 "" H 4900 5200 50  0001 C CNN
F 3 "" H 4900 5200 50  0001 C CNN
	1    4900 5200
	1    0    0    -1  
$EndComp
$Comp
L 74xx:7400 U?
U 1 1 6065517F
P 3450 4800
F 0 "U?" H 3450 5125 50  0001 C CNN
F 1 "7400" H 3450 5034 50  0001 C CNN
F 2 "" H 3450 4800 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn7400" H 3450 4800 50  0001 C CNN
	1    3450 4800
	1    0    0    -1  
$EndComp
$Comp
L 74xx:7400 U?
U 2 1 606575C0
P 3450 5400
F 0 "U?" H 3450 5725 50  0001 C CNN
F 1 "7400" H 3450 5634 50  0001 C CNN
F 2 "" H 3450 5400 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn7400" H 3450 5400 50  0001 C CNN
	2    3450 5400
	1    0    0    -1  
$EndComp
$Comp
L 74xx:7400 U?
U 3 1 60658D25
P 3400 6050
F 0 "U?" H 3400 6375 50  0001 C CNN
F 1 "7400" H 3400 6284 50  0001 C CNN
F 2 "" H 3400 6050 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn7400" H 3400 6050 50  0001 C CNN
	3    3400 6050
	1    0    0    -1  
$EndComp
$Comp
L 74xx:7400 U?
U 4 1 6065AE7A
P 3400 6700
F 0 "U?" H 3400 7025 50  0001 C CNN
F 1 "7400" H 3400 6934 50  0001 C CNN
F 2 "" H 3400 6700 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn7400" H 3400 6700 50  0001 C CNN
	4    3400 6700
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS393 U?
U 2 1 606A4076
P 2000 6200
F 0 "U?" H 2000 6567 50  0001 C CNN
F 1 "74LS393" H 2000 6476 50  0000 C CNN
F 2 "" H 2000 6200 50  0001 C CNN
F 3 "74xx\\74LS393.pdf" H 2000 6200 50  0001 C CNN
	2    2000 6200
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS393 U?
U 1 1 606946C9
P 2000 5450
F 0 "U?" H 2000 5817 50  0001 C CNN
F 1 "74LS393" H 2000 5726 50  0000 C CNN
F 2 "" H 2000 5450 50  0001 C CNN
F 3 "74xx\\74LS393.pdf" H 2000 5450 50  0001 C CNN
	1    2000 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 5650 2500 5850
Wire Wire Line
	2500 5850 1450 5850
Wire Wire Line
	1450 5850 1450 6100
Wire Wire Line
	1450 6100 1500 6100
Wire Wire Line
	1500 5650 1350 5650
Wire Wire Line
	1350 6400 1500 6400
Wire Wire Line
	3100 6600 3050 6600
Wire Wire Line
	3050 6600 3050 6800
Wire Wire Line
	3050 6800 3100 6800
Wire Wire Line
	3700 6700 3700 6300
Wire Wire Line
	3700 6300 3100 6300
Wire Wire Line
	3100 6300 3100 6150
Wire Wire Line
	3150 5500 3150 5300
Wire Wire Line
	3750 5400 3750 5700
Wire Wire Line
	3750 5700 3100 5700
Wire Wire Line
	3100 5700 3100 5950
Wire Wire Line
	2500 6100 2800 6100
Wire Wire Line
	2800 6100 2800 6600
Wire Wire Line
	2800 6600 3050 6600
Connection ~ 3050 6600
Wire Wire Line
	3750 5400 3750 5150
Wire Wire Line
	3750 5150 3150 5150
Wire Wire Line
	3150 5150 3150 4900
Connection ~ 3750 5400
Wire Wire Line
	2800 6100 2800 4700
Wire Wire Line
	2800 4700 3150 4700
Connection ~ 2800 6100
Wire Wire Line
	2950 5300 3150 5300
Connection ~ 3150 5300
Wire Wire Line
	1350 5650 1350 6400
$Comp
L Analog_DAC:MCP4921 U?
U 1 1 60621914
P 4900 4800
F 0 "U?" H 5644 4846 50  0000 L CNN
F 1 "MCP4921" H 5644 4755 50  0000 L CNN
F 2 "" H 5900 4700 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/22248a.pdf" H 5900 4700 50  0001 C CNN
	1    4900 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6060B9CB
P 6950 4400
F 0 "#PWR?" H 6950 4150 50  0001 C CNN
F 1 "GND" H 6955 4227 50  0000 C CNN
F 2 "" H 6950 4400 50  0001 C CNN
F 3 "" H 6950 4400 50  0001 C CNN
	1    6950 4400
	-1   0    0    1   
$EndComp
Connection ~ 5650 4350
Wire Wire Line
	5650 4250 5650 4350
Connection ~ 5100 4350
Wire Wire Line
	5100 4350 5650 4350
Wire Wire Line
	5100 4350 5100 4400
Wire Wire Line
	4900 4350 5100 4350
Wire Wire Line
	4900 4400 4900 4350
Wire Wire Line
	5600 4800 6050 4800
$Comp
L Device:R_Small R?
U 1 1 6060FF56
P 6350 4350
F 0 "R?" V 6154 4350 50  0001 C CNN
F 1 "100k" V 6245 4350 50  0000 C CNN
F 2 "" H 6350 4350 50  0001 C CNN
F 3 "~" H 6350 4350 50  0001 C CNN
	1    6350 4350
	0    1    1    0   
$EndComp
Wire Wire Line
	6950 4500 7050 4500
Wire Wire Line
	6950 4400 6950 4500
Wire Wire Line
	7650 5000 7450 5000
Wire Wire Line
	7650 4600 7650 5000
Connection ~ 7050 4700
Wire Wire Line
	7050 5000 7250 5000
Wire Wire Line
	7050 4700 7050 5000
$Comp
L Device:R_Small R?
U 1 1 6060712F
P 7350 5000
F 0 "R?" V 7154 5000 50  0001 C CNN
F 1 "100k" V 7245 5000 50  0000 C CNN
F 2 "" H 7350 5000 50  0001 C CNN
F 3 "~" H 7350 5000 50  0001 C CNN
	1    7350 5000
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 605F6BED
P 6850 4700
F 0 "R?" V 6654 4700 50  0001 C CNN
F 1 "100k" V 6745 4700 50  0000 C CNN
F 2 "" H 6850 4700 50  0001 C CNN
F 3 "~" H 6850 4700 50  0001 C CNN
	1    6850 4700
	0    1    1    0   
$EndComp
Wire Wire Line
	6950 4700 7050 4700
Connection ~ 6650 4700
Wire Wire Line
	6750 4700 6650 4700
Wire Wire Line
	5650 4600 5750 4600
Wire Wire Line
	5650 4350 5650 4600
$Comp
L power:+5V #PWR?
U 1 1 605D59B4
P 5650 4250
F 0 "#PWR?" H 5650 4100 50  0001 C CNN
F 1 "+5V" H 5665 4423 50  0000 C CNN
F 2 "" H 5650 4250 50  0001 C CNN
F 3 "" H 5650 4250 50  0001 C CNN
	1    5650 4250
	1    0    0    -1  
$EndComp
Connection ~ 6050 4600
Wire Wire Line
	5950 4600 6050 4600
$Comp
L Device:R_Small R?
U 1 1 605CB035
P 5850 4600
F 0 "R?" V 5654 4600 50  0001 C CNN
F 1 "100k" V 5745 4600 50  0000 C CNN
F 2 "" H 5850 4600 50  0001 C CNN
F 3 "~" H 5850 4600 50  0001 C CNN
	1    5850 4600
	0    1    1    0   
$EndComp
$Comp
L Amplifier_Operational:TL062 U?
U 2 1 605B015F
P 6350 4700
F 0 "U?" H 6350 5067 50  0001 C CNN
F 1 "TL062" H 6350 4976 50  0000 C CNN
F 2 "" H 6350 4700 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl061.pdf" H 6350 4700 50  0001 C CNN
	2    6350 4700
	1    0    0    1   
$EndComp
Wire Wire Line
	6050 4350 6050 4600
Wire Wire Line
	6250 4350 6050 4350
Wire Wire Line
	6650 4350 6650 4700
Wire Wire Line
	6450 4350 6650 4350
$Comp
L Amplifier_Operational:TL062 U?
U 1 1 605AC5BA
P 7350 4600
F 0 "U?" H 7350 4967 50  0001 C CNN
F 1 "TL062" H 7350 4876 50  0000 C CNN
F 2 "" H 7350 4600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl061.pdf" H 7350 4600 50  0001 C CNN
	1    7350 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60821582
P 4900 6450
F 0 "#PWR?" H 4900 6200 50  0001 C CNN
F 1 "GND" H 4905 6277 50  0000 C CNN
F 2 "" H 4900 6450 50  0001 C CNN
F 3 "" H 4900 6450 50  0001 C CNN
	1    4900 6450
	1    0    0    -1  
$EndComp
$Comp
L Analog_DAC:MCP4921 U?
U 1 1 6082158C
P 4900 6050
F 0 "U?" H 5644 6096 50  0000 L CNN
F 1 "MCP4921" H 5644 6005 50  0000 L CNN
F 2 "" H 5900 5950 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/22248a.pdf" H 5900 5950 50  0001 C CNN
	1    4900 6050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60821596
P 6950 5650
F 0 "#PWR?" H 6950 5400 50  0001 C CNN
F 1 "GND" H 6955 5477 50  0000 C CNN
F 2 "" H 6950 5650 50  0001 C CNN
F 3 "" H 6950 5650 50  0001 C CNN
	1    6950 5650
	-1   0    0    1   
$EndComp
Connection ~ 5650 5600
Wire Wire Line
	5650 5500 5650 5600
Connection ~ 5100 5600
Wire Wire Line
	5100 5600 5650 5600
Wire Wire Line
	5100 5600 5100 5650
Wire Wire Line
	4900 5600 5100 5600
Wire Wire Line
	4900 5650 4900 5600
Wire Wire Line
	5600 6050 6050 6050
$Comp
L Device:R_Small R?
U 1 1 608215A8
P 6350 5600
F 0 "R?" V 6154 5600 50  0001 C CNN
F 1 "100k" V 6245 5600 50  0000 C CNN
F 2 "" H 6350 5600 50  0001 C CNN
F 3 "~" H 6350 5600 50  0001 C CNN
	1    6350 5600
	0    1    1    0   
$EndComp
Wire Wire Line
	6950 5750 7050 5750
Wire Wire Line
	6950 5650 6950 5750
Wire Wire Line
	7650 6250 7450 6250
Wire Wire Line
	7650 5850 7650 6250
Connection ~ 7050 5950
Wire Wire Line
	7050 6250 7250 6250
Wire Wire Line
	7050 5950 7050 6250
$Comp
L Device:R_Small R?
U 1 1 608215B9
P 7350 6250
F 0 "R?" V 7154 6250 50  0001 C CNN
F 1 "100k" V 7245 6250 50  0000 C CNN
F 2 "" H 7350 6250 50  0001 C CNN
F 3 "~" H 7350 6250 50  0001 C CNN
	1    7350 6250
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 608215C3
P 6850 5950
F 0 "R?" V 6654 5950 50  0001 C CNN
F 1 "100k" V 6745 5950 50  0000 C CNN
F 2 "" H 6850 5950 50  0001 C CNN
F 3 "~" H 6850 5950 50  0001 C CNN
	1    6850 5950
	0    1    1    0   
$EndComp
Wire Wire Line
	6950 5950 7050 5950
Connection ~ 6650 5950
Wire Wire Line
	6750 5950 6650 5950
Wire Wire Line
	5650 5850 5750 5850
Wire Wire Line
	5650 5600 5650 5850
$Comp
L power:+5V #PWR?
U 1 1 608215D2
P 5650 5500
F 0 "#PWR?" H 5650 5350 50  0001 C CNN
F 1 "+5V" H 5665 5673 50  0000 C CNN
F 2 "" H 5650 5500 50  0001 C CNN
F 3 "" H 5650 5500 50  0001 C CNN
	1    5650 5500
	1    0    0    -1  
$EndComp
Connection ~ 6050 5850
Wire Wire Line
	5950 5850 6050 5850
$Comp
L Device:R_Small R?
U 1 1 608215DE
P 5850 5850
F 0 "R?" V 5654 5850 50  0001 C CNN
F 1 "100k" V 5745 5850 50  0000 C CNN
F 2 "" H 5850 5850 50  0001 C CNN
F 3 "~" H 5850 5850 50  0001 C CNN
	1    5850 5850
	0    1    1    0   
$EndComp
$Comp
L Amplifier_Operational:TL062 U?
U 2 1 608215E8
P 6350 5950
F 0 "U?" H 6350 6317 50  0001 C CNN
F 1 "TL062" H 6350 6226 50  0000 C CNN
F 2 "" H 6350 5950 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl061.pdf" H 6350 5950 50  0001 C CNN
	2    6350 5950
	1    0    0    1   
$EndComp
Wire Wire Line
	6050 5600 6050 5850
Wire Wire Line
	6250 5600 6050 5600
Wire Wire Line
	6650 5600 6650 5950
Wire Wire Line
	6450 5600 6650 5600
$Comp
L Amplifier_Operational:TL062 U?
U 1 1 608215F6
P 7350 5850
F 0 "U?" H 7350 6217 50  0001 C CNN
F 1 "TL062" H 7350 6126 50  0000 C CNN
F 2 "" H 7350 5850 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl061.pdf" H 7350 5850 50  0001 C CNN
	1    7350 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 4800 4500 4800
Wire Wire Line
	3700 6050 4500 6050
Wire Wire Line
	4500 4900 4000 4900
Wire Wire Line
	4000 4900 4000 6150
Wire Wire Line
	4000 6150 4500 6150
Wire Wire Line
	4350 4300 4350 4700
Wire Wire Line
	4350 4700 4500 4700
Wire Wire Line
	4350 4700 4350 5950
Wire Wire Line
	4350 5950 4500 5950
Connection ~ 4350 4700
Wire Wire Line
	4200 4400 4200 5000
Wire Wire Line
	4200 5000 4500 5000
Wire Wire Line
	4200 5000 4200 6250
Wire Wire Line
	4200 6250 4500 6250
Connection ~ 4200 5000
Connection ~ 2800 4700
$Comp
L Connector:Conn_01x03_Male J?
U 1 1 60938F1B
P 7850 5100
F 0 "J?" H 7958 5381 50  0001 C CNN
F 1 "Conn_01x03_Male" H 7958 5290 50  0001 C CNN
F 2 "" H 7850 5100 50  0001 C CNN
F 3 "~" H 7850 5100 50  0001 C CNN
	1    7850 5100
	-1   0    0    -1  
$EndComp
Connection ~ 7650 5000
Wire Wire Line
	7650 5200 6650 5200
Wire Wire Line
	6650 5200 6650 4700
$Comp
L power:GND #PWR?
U 1 1 6096E335
P 7650 5100
F 0 "#PWR?" H 7650 4850 50  0001 C CNN
F 1 "GND" H 7655 4927 50  0001 C CNN
F 2 "" H 7650 5100 50  0001 C CNN
F 3 "" H 7650 5100 50  0001 C CNN
	1    7650 5100
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x03_Male J?
U 1 1 60995AE6
P 7850 6350
F 0 "J?" H 7958 6631 50  0001 C CNN
F 1 "Conn_01x03_Male" H 7958 6540 50  0001 C CNN
F 2 "" H 7850 6350 50  0001 C CNN
F 3 "~" H 7850 6350 50  0001 C CNN
	1    7850 6350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7650 6450 6650 6450
$Comp
L power:GND #PWR?
U 1 1 60995AF1
P 7650 6350
F 0 "#PWR?" H 7650 6100 50  0001 C CNN
F 1 "GND" H 7655 6177 50  0001 C CNN
F 2 "" H 7650 6350 50  0001 C CNN
F 3 "" H 7650 6350 50  0001 C CNN
	1    7650 6350
	0    1    1    0   
$EndComp
Connection ~ 7650 6250
Wire Wire Line
	6650 6450 6650 5950
Connection ~ 6150 2550
Wire Wire Line
	6150 2350 6150 2550
$Comp
L pspice:DIODE D?
U 1 1 60829511
P 6350 2550
F 0 "D?" H 6350 2815 50  0001 C CNN
F 1 "DIODE" H 6350 2724 50  0001 C CNN
F 2 "" H 6350 2550 50  0001 C CNN
F 3 "~" H 6350 2550 50  0001 C CNN
	1    6350 2550
	-1   0    0    1   
$EndComp
$Comp
L pspice:DIODE D?
U 1 1 60845DE5
P 6350 2350
F 0 "D?" H 6350 2615 50  0001 C CNN
F 1 "DIODE" H 6350 2524 50  0001 C CNN
F 2 "" H 6350 2350 50  0001 C CNN
F 3 "~" H 6350 2350 50  0001 C CNN
	1    6350 2350
	-1   0    0    1   
$EndComp
Connection ~ 6550 2550
Connection ~ 6550 2350
Connection ~ 7600 2200
Connection ~ 7600 2550
Wire Wire Line
	7850 2200 7600 2200
$Comp
L Device:R_Small R?
U 1 1 60796465
P 7950 2200
F 0 "R?" V 7754 2200 50  0000 C CNN
F 1 "R_Small" V 7845 2200 50  0000 C CNN
F 2 "" H 7950 2200 50  0001 C CNN
F 3 "~" H 7950 2200 50  0001 C CNN
	1    7950 2200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8200 2200 8050 2200
Wire Wire Line
	8200 2450 8200 2200
Wire Wire Line
	7600 2200 7600 2550
$Comp
L Amplifier_Operational:TL062 U?
U 1 1 60796458
P 7900 2550
F 0 "U?" H 7900 2917 50  0000 C CNN
F 1 "TL062" H 7900 2826 50  0000 C CNN
F 2 "" H 7900 2550 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl061.pdf" H 7900 2550 50  0001 C CNN
	1    7900 2550
	-1   0    0    1   
$EndComp
Wire Wire Line
	7500 2950 7400 2950
Wire Wire Line
	7500 2350 7500 2950
Wire Wire Line
	7400 2350 7500 2350
Wire Wire Line
	7600 2550 7400 2550
Wire Wire Line
	7600 1950 7600 2200
Wire Wire Line
	7400 1950 7600 1950
Connection ~ 7150 2350
Wire Wire Line
	7150 2350 7200 2350
$Comp
L Device:R_Small R?
U 1 1 6076015F
P 6900 2350
F 0 "R?" V 6704 2350 50  0001 C CNN
F 1 "47k" V 7004 2350 50  0000 C CNN
F 2 "" H 6900 2350 50  0001 C CNN
F 3 "~" H 6900 2350 50  0001 C CNN
	1    6900 2350
	0    -1   1    0   
$EndComp
Wire Wire Line
	6800 2350 6550 2350
Wire Wire Line
	7150 2350 7000 2350
$Comp
L Device:R_Small R
U 1 1 60760149
P 7300 1950
F 0 "R" V 7496 1950 50  0001 C CNN
F 1 "470" V 7404 1950 50  0000 C CNN
F 2 "" H 7300 1950 50  0001 C CNN
F 3 "~" H 7300 1950 50  0001 C CNN
	1    7300 1950
	0    -1   1    0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 6076013F
P 7300 2350
F 0 "R?" V 7496 2350 50  0001 C CNN
F 1 "470" V 7404 2350 50  0000 C CNN
F 2 "" H 7300 2350 50  0001 C CNN
F 3 "~" H 7300 2350 50  0001 C CNN
	1    7300 2350
	0    -1   1    0   
$EndComp
Connection ~ 7150 2950
Wire Wire Line
	7150 2950 7200 2950
Wire Wire Line
	7150 2950 7150 3100
$Comp
L power:GND #PWR?
U 1 1 60674E59
P 6150 3100
F 0 "#PWR?" H 6150 2850 50  0001 C CNN
F 1 "GND" H 6155 2927 50  0001 C CNN
F 2 "" H 6150 3100 50  0001 C CNN
F 3 "" H 6150 3100 50  0001 C CNN
	1    6150 3100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60730A20
P 7150 3300
F 0 "#PWR?" H 7150 3050 50  0001 C CNN
F 1 "GND" H 7155 3127 50  0001 C CNN
F 2 "" H 7150 3300 50  0001 C CNN
F 3 "" H 7150 3300 50  0001 C CNN
	1    7150 3300
	1    0    0    -1  
$EndComp
Connection ~ 7150 2550
Wire Wire Line
	7150 2550 7200 2550
$Comp
L Device:R_Small R?
U 1 1 606D0026
P 7150 3200
F 0 "R?" H 7091 3154 50  0001 R CNN
F 1 "47k" H 7091 3200 50  0000 R CNN
F 2 "" H 7150 3200 50  0001 C CNN
F 3 "~" H 7150 3200 50  0001 C CNN
	1    7150 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 2750 7150 2550
Wire Wire Line
	6550 2850 6550 2550
$Comp
L Amplifier_Operational:TL062 U?
U 1 1 605AE477
P 6850 2850
F 0 "U?" H 6850 3217 50  0001 C CNN
F 1 "TL062" H 6850 3125 50  0000 C CNN
F 2 "" H 6850 2850 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl061.pdf" H 6850 2850 50  0001 C CNN
	1    6850 2850
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60655284
P 6900 2550
F 0 "R?" V 6704 2550 50  0001 C CNN
F 1 "47k" V 6796 2550 50  0000 C CNN
F 2 "" H 6900 2550 50  0001 C CNN
F 3 "~" H 6900 2550 50  0001 C CNN
	1    6900 2550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6800 2550 6550 2550
Wire Wire Line
	7150 2550 7000 2550
$Comp
L Device:R_Small R?
U 1 1 6066EFD1
P 7300 2950
F 0 "R?" V 7104 2950 50  0001 C CNN
F 1 "470" V 7196 2950 50  0000 C CNN
F 2 "" H 7300 2950 50  0001 C CNN
F 3 "~" H 7300 2950 50  0001 C CNN
	1    7300 2950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 6066EADA
P 7300 2550
F 0 "R?" V 7104 2550 50  0001 C CNN
F 1 "470" V 7196 2550 50  0000 C CNN
F 2 "" H 7300 2550 50  0001 C CNN
F 3 "~" H 7300 2550 50  0001 C CNN
	1    7300 2550
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60760153
P 7150 1700
F 0 "R?" H 7091 1654 50  0001 R CNN
F 1 "47k" H 7091 1700 50  0000 R CNN
F 2 "" H 7150 1700 50  0001 C CNN
F 3 "~" H 7150 1700 50  0001 C CNN
	1    7150 1700
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6076018B
P 7150 1600
F 0 "#PWR?" H 7150 1350 50  0001 C CNN
F 1 "GND" H 7155 1427 50  0001 C CNN
F 2 "" H 7150 1600 50  0001 C CNN
F 3 "" H 7150 1600 50  0001 C CNN
	1    7150 1600
	1    0    0    1   
$EndComp
$Comp
L pspice:DIODE D?
U 1 1 60DF4F05
P 5950 2550
F 0 "D?" H 5950 2815 50  0001 C CNN
F 1 "DIODE" H 5950 2724 50  0001 C CNN
F 2 "" H 5950 2550 50  0001 C CNN
F 3 "~" H 5950 2550 50  0001 C CNN
	1    5950 2550
	1    0    0    1   
$EndComp
$Comp
L pspice:DIODE D?
U 1 1 60DF4F0F
P 5950 2350
F 0 "D?" H 5950 2615 50  0001 C CNN
F 1 "DIODE" H 5950 2524 50  0001 C CNN
F 2 "" H 5950 2350 50  0001 C CNN
F 3 "~" H 5950 2350 50  0001 C CNN
	1    5950 2350
	1    0    0    1   
$EndComp
Connection ~ 5750 2550
Connection ~ 5750 2350
Connection ~ 4700 2200
Connection ~ 4700 2550
Wire Wire Line
	4450 2200 4700 2200
$Comp
L Device:R_Small R?
U 1 1 60DF4F1E
P 4350 2200
F 0 "R?" V 4154 2200 50  0000 C CNN
F 1 "R_Small" V 4245 2200 50  0000 C CNN
F 2 "" H 4350 2200 50  0001 C CNN
F 3 "~" H 4350 2200 50  0001 C CNN
	1    4350 2200
	0    1    -1   0   
$EndComp
Wire Wire Line
	4100 2200 4250 2200
Wire Wire Line
	4100 2450 4100 2200
Wire Wire Line
	4700 2200 4700 2550
$Comp
L Amplifier_Operational:TL062 U?
U 1 1 60DF4F2B
P 4400 2550
F 0 "U?" H 4400 2917 50  0000 C CNN
F 1 "TL062" H 4400 2826 50  0000 C CNN
F 2 "" H 4400 2550 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl061.pdf" H 4400 2550 50  0001 C CNN
	1    4400 2550
	1    0    0    1   
$EndComp
Wire Wire Line
	4800 2950 4900 2950
Wire Wire Line
	4800 2350 4800 2950
Wire Wire Line
	4900 2350 4800 2350
Wire Wire Line
	4700 2550 4900 2550
Wire Wire Line
	4700 1950 4700 2200
Wire Wire Line
	4900 1950 4700 1950
Connection ~ 5150 2350
Wire Wire Line
	5150 2350 5100 2350
$Comp
L Device:R_Small R?
U 1 1 60DF4F4C
P 5400 2350
F 0 "R?" V 5204 2350 50  0001 C CNN
F 1 "47k" V 5504 2350 50  0000 C CNN
F 2 "" H 5400 2350 50  0001 C CNN
F 3 "~" H 5400 2350 50  0001 C CNN
	1    5400 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	5500 2350 5750 2350
Wire Wire Line
	5150 2350 5300 2350
$Comp
L Device:R_Small R?
U 1 1 60DF4F58
P 5000 1950
F 0 "R?" V 5196 1950 50  0001 C CNN
F 1 "470" V 5104 1950 50  0000 C CNN
F 2 "" H 5000 1950 50  0001 C CNN
F 3 "~" H 5000 1950 50  0001 C CNN
	1    5000 1950
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60DF4F62
P 5000 2350
F 0 "R?" V 5196 2350 50  0001 C CNN
F 1 "470" V 5104 2350 50  0000 C CNN
F 2 "" H 5000 2350 50  0001 C CNN
F 3 "~" H 5000 2350 50  0001 C CNN
	1    5000 2350
	0    1    1    0   
$EndComp
Connection ~ 5150 2950
Wire Wire Line
	5150 2950 5100 2950
Wire Wire Line
	5150 2950 5150 3100
$Comp
L power:GND #PWR?
U 1 1 60DF4F6F
P 5150 3300
F 0 "#PWR?" H 5150 3050 50  0001 C CNN
F 1 "GND" H 5155 3127 50  0001 C CNN
F 2 "" H 5150 3300 50  0001 C CNN
F 3 "" H 5150 3300 50  0001 C CNN
	1    5150 3300
	-1   0    0    -1  
$EndComp
Connection ~ 5150 2550
Wire Wire Line
	5150 2550 5100 2550
$Comp
L Device:R_Small R?
U 1 1 60DF4F7B
P 5150 3200
F 0 "R?" H 5091 3154 50  0001 R CNN
F 1 "47k" H 5091 3200 50  0000 R CNN
F 2 "" H 5150 3200 50  0001 C CNN
F 3 "~" H 5150 3200 50  0001 C CNN
	1    5150 3200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5150 2750 5150 2550
Wire Wire Line
	5750 2850 5750 2550
$Comp
L Amplifier_Operational:TL062 U?
U 1 1 60DF4F87
P 5450 2850
F 0 "U?" H 5450 3217 50  0001 C CNN
F 1 "TL062" H 5450 3125 50  0000 C CNN
F 2 "" H 5450 2850 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl061.pdf" H 5450 2850 50  0001 C CNN
	1    5450 2850
	1    0    0    1   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60DF4F91
P 5400 2550
F 0 "R?" V 5204 2550 50  0001 C CNN
F 1 "47k" V 5296 2550 50  0000 C CNN
F 2 "" H 5400 2550 50  0001 C CNN
F 3 "~" H 5400 2550 50  0001 C CNN
	1    5400 2550
	0    1    -1   0   
$EndComp
Wire Wire Line
	5500 2550 5750 2550
Wire Wire Line
	5150 2550 5300 2550
$Comp
L Device:R_Small R?
U 1 1 60DF4F9D
P 5000 2950
F 0 "R?" V 4804 2950 50  0001 C CNN
F 1 "470" V 4896 2950 50  0000 C CNN
F 2 "" H 5000 2950 50  0001 C CNN
F 3 "~" H 5000 2950 50  0001 C CNN
	1    5000 2950
	0    1    -1   0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60DF4FA7
P 5000 2550
F 0 "R?" V 4804 2550 50  0001 C CNN
F 1 "470" V 4896 2550 50  0000 C CNN
F 2 "" H 5000 2550 50  0001 C CNN
F 3 "~" H 5000 2550 50  0001 C CNN
	1    5000 2550
	0    1    -1   0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60DF4FB1
P 5150 1700
F 0 "R?" H 5091 1654 50  0001 R CNN
F 1 "47k" H 5091 1700 50  0000 R CNN
F 2 "" H 5150 1700 50  0001 C CNN
F 3 "~" H 5150 1700 50  0001 C CNN
	1    5150 1700
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60DF4FBB
P 5150 1600
F 0 "#PWR?" H 5150 1350 50  0001 C CNN
F 1 "GND" H 5155 1427 50  0001 C CNN
F 2 "" H 5150 1600 50  0001 C CNN
F 3 "" H 5150 1600 50  0001 C CNN
	1    5150 1600
	-1   0    0    1   
$EndComp
Connection ~ 6150 2350
$Comp
L Connector:Conn_01x02_Female J?
U 1 1 6106DD49
P 8750 3500
F 0 "J?" H 8778 3476 50  0001 L CNN
F 1 "Conn_01x02_Female" H 8778 3385 50  0001 L CNN
F 2 "" H 8750 3500 50  0001 C CNN
F 3 "~" H 8750 3500 50  0001 C CNN
	1    8750 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 2650 8400 2650
Wire Wire Line
	8400 2650 8400 3500
Wire Wire Line
	8400 3500 8550 3500
Wire Wire Line
	8550 3600 3900 3600
Wire Wire Line
	3900 3600 3900 2650
Wire Wire Line
	3900 2650 4100 2650
Wire Wire Line
	4800 2950 4800 3850
Wire Wire Line
	4800 3850 6650 3850
Wire Wire Line
	6650 3850 6650 4350
Connection ~ 4800 2950
Connection ~ 6650 4350
Wire Wire Line
	6650 5600 6650 5400
Wire Wire Line
	6650 5400 8100 5400
Wire Wire Line
	8100 5400 8100 3900
Wire Wire Line
	8100 3900 7500 3900
Wire Wire Line
	7500 3900 7500 2950
Connection ~ 6650 5600
Connection ~ 7500 2950
Wire Wire Line
	900  4300 4350 4300
Wire Wire Line
	900  4400 4200 4400
Wire Wire Line
	900  4700 2800 4700
Wire Wire Line
	2950 5300 2950 4600
Wire Wire Line
	2950 4600 900  4600
Wire Wire Line
	4000 4900 4000 4500
Connection ~ 4000 4900
$Comp
L Connector:Conn_01x07_Female J?
U 1 1 6071A335
P 700 4500
F 0 "J?" H 728 4526 50  0001 L CNN
F 1 "Conn_01x07_Female" H 728 4435 50  0001 L CNN
F 2 "" H 700 4500 50  0001 C CNN
F 3 "~" H 700 4500 50  0001 C CNN
	1    700  4500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	900  4500 1500 4500
Wire Wire Line
	900  4800 1350 4800
Wire Wire Line
	1350 4800 1350 5650
Connection ~ 1350 5650
Wire Wire Line
	1500 5350 1500 4500
Connection ~ 1500 4500
Wire Wire Line
	1500 4500 4000 4500
Wire Wire Line
	6150 2650 6150 2550
Wire Wire Line
	6150 3100 6150 2850
$Comp
L Device:R_Small R?
U 1 1 6066ECC6
P 6150 2750
F 0 "R?" V 5954 2750 50  0001 C CNN
F 1 "100k" H 6209 2750 50  0000 L CNN
F 2 "" H 6150 2750 50  0001 C CNN
F 3 "~" H 6150 2750 50  0001 C CNN
	1    6150 2750
	-1   0    0    1   
$EndComp
$Comp
L Transistor_BJT:BC414 Q?
U 1 1 60666583
P 4350 1400
F 0 "Q?" H 4541 1446 50  0000 L CNN
F 1 "BC414" H 4541 1355 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4550 1325 50  0001 L CIN
F 3 "http://www.cdil.com/datasheets/bc413_14_b_c.pdf" H 4350 1400 50  0001 L CNN
	1    4350 1400
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60603338
P 4650 1400
F 0 "R?" V 4454 1400 50  0001 C CNN
F 1 "100k" H 4709 1400 50  0000 L CNN
F 2 "" H 4650 1400 50  0001 C CNN
F 3 "~" H 4650 1400 50  0001 C CNN
	1    4650 1400
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 606A1BA0
P 4250 1100
F 0 "R?" V 4054 1100 50  0001 C CNN
F 1 "5k" H 4309 1100 50  0000 L CNN
F 2 "" H 4250 1100 50  0001 C CNN
F 3 "~" H 4250 1100 50  0001 C CNN
	1    4250 1100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 606C2708
P 4250 1600
F 0 "#PWR?" H 4250 1350 50  0001 C CNN
F 1 "GND" H 4255 1427 50  0001 C CNN
F 2 "" H 4250 1600 50  0001 C CNN
F 3 "" H 4250 1600 50  0001 C CNN
	1    4250 1600
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 606ECE46
P 4250 1000
F 0 "#PWR?" H 4250 850 50  0001 C CNN
F 1 "+5V" H 4265 1173 50  0000 C CNN
F 2 "" H 4250 1000 50  0001 C CNN
F 3 "" H 4250 1000 50  0001 C CNN
	1    4250 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 1250 900  1250
Wire Wire Line
	900  1250 900  4200
Connection ~ 7150 1950
Wire Wire Line
	7150 1950 7150 1800
Wire Wire Line
	7150 1950 7200 1950
Wire Wire Line
	7150 2150 7150 2350
Wire Wire Line
	6550 2050 6550 2350
Wire Wire Line
	5150 1950 5150 1800
Wire Wire Line
	5150 1950 5100 1950
Connection ~ 5150 1950
Wire Wire Line
	5150 2150 5150 2350
Wire Wire Line
	5750 2050 5750 2350
$Comp
L Amplifier_Operational:TL062 U?
U 1 1 60760169
P 6850 2050
F 0 "U?" H 6850 2417 50  0001 C CNN
F 1 "TL062" H 6850 1775 50  0000 C CNN
F 2 "" H 6850 2050 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl061.pdf" H 6850 2050 50  0001 C CNN
	1    6850 2050
	-1   0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TL062 U?
U 1 1 60DF4F42
P 5450 2050
F 0 "U?" H 5450 2417 50  0001 C CNN
F 1 "TL062_x" H 5450 1775 50  0000 C CNN
F 2 "" H 5450 2050 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl061.pdf" H 5450 2050 50  0001 C CNN
	1    5450 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 1500 6150 2350
Wire Wire Line
	6150 1050 6150 1300
Connection ~ 5550 1050
Wire Wire Line
	5550 1000 5550 1050
Connection ~ 6150 1050
Wire Wire Line
	6150 1000 6150 1050
Wire Wire Line
	6150 1050 5550 1050
$Comp
L power:GND #PWR?
U 1 1 6095BE6F
P 5550 800
F 0 "#PWR?" H 5550 550 50  0001 C CNN
F 1 "GND" H 5555 627 50  0001 C CNN
F 2 "" H 5550 800 50  0001 C CNN
F 3 "" H 5550 800 50  0001 C CNN
	1    5550 800 
	1    0    0    1   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60900FD3
P 5550 900
F 0 "R?" H 5491 854 50  0001 R CNN
F 1 "15k" V 5446 900 50  0000 C CNN
F 2 "" H 5550 900 50  0001 C CNN
F 3 "~" H 5550 900 50  0001 C CNN
	1    5550 900 
	-1   0    0    1   
$EndComp
Wire Wire Line
	5550 1100 5550 1050
Wire Wire Line
	5550 1300 5550 1400
$Comp
L Device:R_Small R?
U 1 1 609D56D5
P 5550 1200
F 0 "R?" H 5491 1154 50  0001 R CNN
F 1 "250l" H 5492 1200 50  0000 R CNN
F 2 "" H 5550 1200 50  0001 C CNN
F 3 "~" H 5550 1200 50  0001 C CNN
	1    5550 1200
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60760175
P 6150 900
F 0 "R?" H 6091 854 50  0001 R CNN
F 1 "35k" V 6046 900 50  0000 C CNN
F 2 "" H 6150 900 50  0001 C CNN
F 3 "~" H 6150 900 50  0001 C CNN
	1    6150 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 750  6150 800 
$Comp
L Amplifier_Operational:TL062 U?
U 2 1 6060E2C6
P 5850 1400
F 0 "U?" H 5850 1767 50  0001 C CNN
F 1 "TL062_x" H 5850 1675 50  0000 C CNN
F 2 "" H 5850 1400 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl061.pdf" H 5850 1400 50  0001 C CNN
	2    5850 1400
	-1   0    0    -1  
$EndComp
$Comp
L power:+15V #PWR?
U 1 1 609214BF
P 6150 750
F 0 "#PWR?" H 6150 600 50  0001 C CNN
F 1 "+15V" V 6165 878 50  0000 L CNN
F 2 "" H 6150 750 50  0001 C CNN
F 3 "" H 6150 750 50  0001 C CNN
	1    6150 750 
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4750 1400 5550 1400
Connection ~ 5550 1400
$EndSCHEMATC
