# Hardware
- Optimize the dimension of the PCB design to fit in the TIC space
![TIC_Dimension](https://github.com/hovuduybao/GeeLink/blob/master/Images/TIC_Dimension.jpg)
- Add the protection for electrical components 
![Protection_GeeLink](https://github.com/hovuduybao/GeeLink/blob/master/Images/Protection_GeeLink.PNG)

#### Antenna
- Choose another type or redesign the PCB antenna based on the open-source design from Texas Instruments [here](https://github.com/hovuduybao/GeeLink/blob/master/Datasheet/LoRa%20Modules%20%2B%20Antenna/Antenna%20Selection%20Quick%20Guide%20-%20Texas%20Instruments.pdf)

# Software
## GeeLink Firmware
- Improve the operation of GeeLink as well as increase the number of indexs collected from Linky meter
- Test the [not-tested-yet-libraries](https://github.com/hovuduybao/GeeLink/tree/master/Arduino_Code/libraries/Un-tested)
## Network server
- Use the private network server built on Ubuntu-VPS --> [ChirpStack](https://www.chirpstack.io/) instead of `TheThingsNetwork`
## Application server
- Add the account management and security for [Node-RED](https://notenoughtech.com/home-automation/nodered-home-automation/nodered-security/) and [Grafana](https://www.digitalocean.com/community/tutorials/how-to-install-and-secure-grafana-on-ubuntu-18-04)
- Intergrate the local server into the datacenter