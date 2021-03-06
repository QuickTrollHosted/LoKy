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
L ARDUINO_PRO_MINI:ARDUINO_PRO_MINI U1
U 1 1 60247FED
P 5494 3666
F 0 "U1" H 5494 5033 50  0000 C CNN
F 1 "ARDUINO_PRO_MINI" H 5494 4942 50  0000 C CNN
F 2 "ARDUINO_PRO_MINI:MODULE_ARDUINO_PRO_MINI" H 5494 3666 50  0001 L BNN
F 3 "" H 5494 3666 50  0001 L BNN
F 4 "SparkFun Electronics" H 5494 3666 50  0001 L BNN "MANUFACTURER"
F 5 "N/A" H 5494 3666 50  0001 L BNN "PARTREV"
F 6 "Manufacturer Recommendations" H 5494 3666 50  0001 L BNN "STANDARD"
F 7 "N/A" H 5494 3666 50  0001 L BNN "MAXIMUM_PACKAGE_HEIGHT"
	1    5494 3666
	1    0    0    -1  
$EndComp
NoConn ~ 4794 2966
NoConn ~ 4794 3066
NoConn ~ 4794 3266
NoConn ~ 4794 3366
NoConn ~ 4794 3566
NoConn ~ 4794 3666
NoConn ~ 4794 3866
NoConn ~ 4794 3966
NoConn ~ 6194 2766
NoConn ~ 6194 3366
NoConn ~ 6194 4566
NoConn ~ 6194 2566
Text Label 6194 2666 0    50   ~ 0
3V3
Text Label 4794 4066 2    50   ~ 0
SCK
Text Label 4794 4166 2    50   ~ 0
MISO
Text Label 4794 4266 2    50   ~ 0
MOSI
Text Label 4794 4366 2    50   ~ 0
NSS
Text Label 6194 4266 0    50   ~ 0
RST
Text Label 6194 3666 0    50   ~ 0
DIO0
Text Label 6194 4166 0    50   ~ 0
DIO1
Text Label 6194 4366 0    50   ~ 0
DIO2
NoConn ~ 6194 4666
NoConn ~ 6194 2966
NoConn ~ 6194 3066
NoConn ~ 6194 3166
$Comp
L header:HEADER_F_2.54MM_1R4P_ST_AU_PTH J1
U 1 1 60252358
P 6344 3916
F 0 "J1" H 6422 3954 40  0000 L CNN
F 1 "H1" H 6422 3878 40  0000 L CNN
F 2 "Header:HEADER_F_2.54MM_1R4P_ST_SN_PTH" H 6344 3916 60  0001 C CNN
F 3 "" H 6344 3916 60  0000 C CNN
	1    6344 3916
	1    0    0    -1  
$EndComp
$Comp
L header:HEADER_F_2.54MM_1R2P_ST_AU_PTH J2
U 1 1 602533F2
P 6344 3516
F 0 "J2" H 6422 3554 40  0000 L CNN
F 1 "H2" H 6422 3478 40  0000 L CNN
F 2 "Header:HEADER_F_2.54MM_1R2P_ST_AU_PTH" H 6344 3516 60  0001 C CNN
F 3 "" H 6344 3516 60  0000 C CNN
	1    6344 3516
	1    0    0    -1  
$EndComp
NoConn ~ 4794 3766
Text Label 6194 4766 0    50   ~ 0
GND
$EndSCHEMATC
