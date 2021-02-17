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
L header:HEADER_M_2.54MM_1R7P_ST_AU_PTH P1
U 1 1 60249194
P 4118 4126
F 0 "P1" H 4242 4066 40  0000 C CNN
F 1 "H1" H 4240 4150 40  0000 C CNN
F 2 "Header:HEADER_M_2.54MM_1R7P_ST_AU_PTH" H 4118 4126 60  0001 C CNN
F 3 "" H 4118 4126 60  0000 C CNN
	1    4118 4126
	-1   0    0    -1  
$EndComp
Text Label 4268 3826 0    50   ~ 0
GND
Text Label 4268 4126 0    50   ~ 0
3V3
Text Label 4268 4226 0    50   ~ 0
DIO0
Text Label 4268 4326 0    50   ~ 0
DIO1
Text Label 4268 4426 0    50   ~ 0
DIO2
NoConn ~ 4268 3926
NoConn ~ 4268 4026
NoConn ~ 6898 3878
Text Label 6898 3778 2    50   ~ 0
GND
$Comp
L header:HEADER_M_2.54MM_1R8P_ST_AU_PTH P2
U 1 1 6024B676
P 7048 4128
F 0 "P2" H 7126 4166 40  0000 L CNN
F 1 "H2" H 7126 4090 40  0000 L CNN
F 2 "Header:HEADER_M_2.54MM_1R8P_ST_AU_PTH" H 7048 4128 60  0001 C CNN
F 3 "" H 7048 4128 60  0000 C CNN
	1    7048 4128
	1    0    0    -1  
$EndComp
Text Label 6898 3978 2    50   ~ 0
RST
Text Label 6898 4078 2    50   ~ 0
NSS
Text Label 6898 4178 2    50   ~ 0
SCK
Text Label 6898 4278 2    50   ~ 0
MOSI
Text Label 6898 4378 2    50   ~ 0
MISO
Text Label 6898 4478 2    50   ~ 0
GND
Text Label 5748 4706 3    50   ~ 0
GND
NoConn ~ 6148 3806
NoConn ~ 6148 4106
NoConn ~ 6148 4206
NoConn ~ 6148 4006
Text Label 5548 4706 3    50   ~ 0
GND
Text Label 5148 4106 2    50   ~ 0
NSS
Text Label 5148 3906 2    50   ~ 0
MOSI
Text Label 5148 4006 2    50   ~ 0
MISO
Text Label 5148 3806 2    50   ~ 0
SCK
Text Label 5648 4706 3    50   ~ 0
GND
Text Label 5148 4306 2    50   ~ 0
RST
Text Label 6148 4506 0    50   ~ 0
DIO0
Text Label 6148 4406 0    50   ~ 0
DIO1
Text Label 6148 4306 0    50   ~ 0
DIO2
Text Label 5648 3606 0    50   ~ 0
3V3
$Comp
L RF_Module:RFM95W-868S2 U1
U 1 1 60254BE6
P 5648 4106
F 0 "U1" H 5468 4670 50  0000 C CNN
F 1 "RFM95" H 5376 4568 50  0000 C CNN
F 2 "RF_Module:HOPERF_RFM9XW_SMD" H 2348 5756 50  0001 C CNN
F 3 "https://www.hoperf.com/data/upload/portal/20181127/5bfcbea20e9ef.pdf" H 2348 5756 50  0001 C CNN
	1    5648 4106
	1    0    0    -1  
$EndComp
$EndSCHEMATC
