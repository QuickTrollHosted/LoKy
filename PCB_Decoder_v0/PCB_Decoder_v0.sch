EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "LoKy Decoder "
Date "2021-02-10"
Rev "0.1"
Comp "HO Vu Duy Bao"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
NoConn ~ 8842 1898
NoConn ~ 8842 1998
NoConn ~ 8842 2098
NoConn ~ 1972 2724
NoConn ~ 1972 2824
NoConn ~ 1972 3024
NoConn ~ 1972 3124
NoConn ~ 1972 3324
NoConn ~ 1972 3424
NoConn ~ 1972 3524
NoConn ~ 1972 3624
NoConn ~ 1972 3724
NoConn ~ 3372 2724
NoConn ~ 3372 2824
NoConn ~ 3372 2924
NoConn ~ 3372 2524
NoConn ~ 3372 3124
NoConn ~ 3372 3224
NoConn ~ 3372 3324
$Comp
L PC814:PC814 OK1
U 1 1 602580C8
P 7366 5548
F 0 "OK1" H 7416 5918 50  0000 C CNN
F 1 "PC814" H 7416 5827 50  0000 C CNN
F 2 "PC814:DIL04" H 7366 5548 50  0001 L BNN
F 3 "" H 7366 5548 50  0001 L BNN
F 4 "" H 7366 5548 50  0001 L BNN "MPN"
F 5 "9707662" H 7366 5548 50  0001 L BNN "OC_FARNELL"
F 6 "unknown" H 7366 5548 50  0001 L BNN "OC_NEWARK"
F 7 "" H 7366 5548 50  0001 L BNN "MF"
	1    7366 5548
	1    0    0    -1  
$EndComp
Wire Wire Line
	8842 2198 8906 2198
Text Label 8906 2198 0    50   ~ 0
DIO2
Wire Wire Line
	8842 2298 8908 2298
Text Label 8908 2298 0    50   ~ 0
DIO1
Wire Wire Line
	8842 2398 8908 2398
Text Label 8908 2398 0    50   ~ 0
DIO0
$Comp
L Device:Antenna AE1
U 1 1 6026053C
P 8952 1498
F 0 "AE1" H 9032 1487 50  0000 L CNN
F 1 "Antenna" H 9032 1396 50  0000 L CNN
F 2 "" H 8952 1498 50  0001 C CNN
F 3 "~" H 8952 1498 50  0001 C CNN
	1    8952 1498
	1    0    0    -1  
$EndComp
Wire Wire Line
	8842 1698 8952 1698
Wire Wire Line
	1972 4024 1876 4024
Wire Wire Line
	1972 3924 1876 3924
Wire Wire Line
	1972 4124 1874 4124
Text Label 1874 4124 2    50   ~ 0
SS
Text Label 1876 4024 2    50   ~ 0
MOSI
Text Label 1876 3924 2    50   ~ 0
MISO
Wire Wire Line
	1972 3824 1876 3824
Text Label 1876 3824 2    50   ~ 0
SCK
$Comp
L power:GNDREF #PWR01
U 1 1 60268EDB
P 3372 4524
F 0 "#PWR01" H 3372 4274 50  0001 C CNN
F 1 "GNDREF" H 3377 4351 50  0000 C CNN
F 2 "" H 3372 4524 50  0001 C CNN
F 3 "" H 3372 4524 50  0001 C CNN
	1    3372 4524
	1    0    0    -1  
$EndComp
Wire Wire Line
	7842 1698 7774 1698
Wire Wire Line
	7842 1798 7778 1798
Wire Wire Line
	7842 1898 7784 1898
Wire Wire Line
	7842 1998 7780 1998
Wire Wire Line
	7842 2198 7778 2198
Text Label 7774 1698 2    50   ~ 0
SCK
Text Label 7778 1798 2    50   ~ 0
MOSI
Text Label 7784 1898 2    50   ~ 0
MISO
Text Label 7780 1998 2    50   ~ 0
SS
Text Label 7778 2198 2    50   ~ 0
RST
$Comp
L power:+3V3 #PWR02
U 1 1 6026DB85
P 3458 2258
F 0 "#PWR02" H 3458 2108 50  0001 C CNN
F 1 "+3V3" H 3473 2431 50  0000 C CNN
F 2 "" H 3458 2258 50  0001 C CNN
F 3 "" H 3458 2258 50  0001 C CNN
	1    3458 2258
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR05
U 1 1 6026E6BB
P 8342 1374
F 0 "#PWR05" H 8342 1224 50  0001 C CNN
F 1 "+3V3" H 8357 1547 50  0000 C CNN
F 2 "" H 8342 1374 50  0001 C CNN
F 3 "" H 8342 1374 50  0001 C CNN
	1    8342 1374
	1    0    0    -1  
$EndComp
Wire Wire Line
	7866 5448 7972 5448
$Comp
L Device:R R3
U 1 1 60270919
P 7972 5248
F 0 "R3" H 8042 5294 50  0000 L CNN
F 1 "3.3K" H 8042 5203 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 7902 5248 50  0001 C CNN
F 3 "~" H 7972 5248 50  0001 C CNN
	1    7972 5248
	1    0    0    -1  
$EndComp
Wire Wire Line
	7972 5398 7972 5448
Connection ~ 7972 5448
Wire Wire Line
	7972 5098 7972 5066
Wire Wire Line
	7972 5066 8214 5066
Wire Wire Line
	8214 5066 8214 5044
$Comp
L power:+3V3 #PWR03
U 1 1 602743F7
P 8214 5044
F 0 "#PWR03" H 8214 4894 50  0001 C CNN
F 1 "+3V3" H 8229 5217 50  0000 C CNN
F 2 "" H 8214 5044 50  0001 C CNN
F 3 "" H 8214 5044 50  0001 C CNN
	1    8214 5044
	1    0    0    -1  
$EndComp
Text Label 8208 5648 0    50   ~ 0
infoTIC_GND
$Comp
L Device:R R1
U 1 1 6022FEC0
P 6682 5448
F 0 "R1" V 6475 5448 50  0000 C CNN
F 1 "1.2K" V 6566 5448 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 6612 5448 50  0001 C CNN
F 3 "~" H 6682 5448 50  0001 C CNN
	1    6682 5448
	0    1    1    0   
$EndComp
Wire Wire Line
	6832 5448 6966 5448
Wire Wire Line
	6532 5448 6326 5448
$Comp
L Connector:Conn_01x02_Male J1
U 1 1 6023383F
P 6126 5448
F 0 "J1" H 6340 5288 50  0000 C CNN
F 1 " " H 6234 5538 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 6126 5448 50  0001 C CNN
F 3 "~" H 6126 5448 50  0001 C CNN
	1    6126 5448
	1    0    0    -1  
$EndComp
Wire Wire Line
	6326 5548 6452 5548
Wire Wire Line
	6452 5548 6452 5648
Wire Wire Line
	6452 5648 6966 5648
NoConn ~ 3372 3424
NoConn ~ 3372 3524
NoConn ~ 3372 3624
Wire Wire Line
	3372 3924 3530 3924
Wire Wire Line
	3372 4024 3528 4024
Wire Wire Line
	3372 4124 3526 4124
Text Label 3522 3824 0    50   ~ 0
RST
Text Label 3528 4024 0    50   ~ 0
DIO1
Text Label 3526 4124 0    50   ~ 0
DIO2
Text Label 3530 3924 0    50   ~ 0
DIO0
Text Label 8206 5448 0    50   ~ 0
infoTIC_TX
Wire Wire Line
	8784 5548 8784 5648
Wire Wire Line
	7866 5648 8784 5648
Wire Wire Line
	8784 5548 8848 5548
Wire Wire Line
	7972 5448 8848 5448
$Comp
L Connector:Conn_01x02_Female J2
U 1 1 6023D362
P 9048 5448
F 0 "J2" H 8822 5282 50  0000 L CNN
F 1 " " H 9076 5333 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 9048 5448 50  0001 C CNN
F 3 "~" H 9048 5448 50  0001 C CNN
	1    9048 5448
	1    0    0    -1  
$EndComp
Wire Wire Line
	8342 1374 8342 1498
$Comp
L RF_Module:RFM95W-868S2 U2
U 1 1 602429BF
P 8342 1998
F 0 "U2" H 8032 2576 50  0000 C CNN
F 1 "RFM95W" H 8078 2474 50  0000 C CNN
F 2 "RF_Module:HOPERF_RFM9XW_SMD" H 5042 3648 50  0001 C CNN
F 3 "https://www.hoperf.com/data/upload/portal/20181127/5bfcbea20e9ef.pdf" H 5042 3648 50  0001 C CNN
	1    8342 1998
	1    0    0    -1  
$EndComp
Wire Wire Line
	3372 2424 3458 2424
NoConn ~ 8442 2598
$Comp
L power:GNDREF #PWR04
U 1 1 6026550F
P 8342 2598
F 0 "#PWR04" H 8342 2348 50  0001 C CNN
F 1 "GNDREF" H 8347 2425 50  0000 C CNN
F 2 "" H 8342 2598 50  0001 C CNN
F 3 "" H 8342 2598 50  0001 C CNN
	1    8342 2598
	1    0    0    -1  
$EndComp
NoConn ~ 3372 4324
Wire Wire Line
	3458 2258 3458 2424
NoConn ~ 3372 2324
NoConn ~ 8242 2598
$Comp
L ARDUINO_PRO_MINI:ARDUINO_PRO_MINI U1
U 1 1 6024145F
P 2672 3424
F 0 "U1" H 2672 4791 50  0000 C CNN
F 1 "PRO_MINI" H 2672 4700 50  0000 C CNN
F 2 "ARDUINO_PRO_MINI:MODULE_ARDUINO_PRO_MINI" H 2672 3424 50  0001 L BNN
F 3 "" H 2672 3424 50  0001 L BNN
F 4 "SparkFun Electronics" H 2672 3424 50  0001 L BNN "MANUFACTURER"
F 5 "N/A" H 2672 3424 50  0001 L BNN "PARTREV"
F 6 "Manufacturer Recommendations" H 2672 3424 50  0001 L BNN "STANDARD"
F 7 "N/A" H 2672 3424 50  0001 L BNN "MAXIMUM_PACKAGE_HEIGHT"
	1    2672 3424
	1    0    0    -1  
$EndComp
NoConn ~ 3372 4424
Wire Wire Line
	3372 3824 3522 3824
NoConn ~ 3372 3724
$EndSCHEMATC
