# **BSPWon_nRF52**
Bio Sensor Platform designed to operate with BSPWon iOS/Android </br>
@Won Research Group, SKKU </br>
<img src="sensor.PNG" width="550" height = "350"> </br>
#####*(BLE chip integrated into circuit along with power source and an accelerometer)* </br>
Developed by Jihwan Kim, Sang Uk Park, Sang Hoon Lee</br> 
Photo taken by Hee Kyu Lee, Won Research Group 

## *Project Overview*
--------------------------------------------
> #### The objective of this project is to enable wireless communication among peripheral devices to receive and transmit data and commands. The NRF board provides a developer  environment where the user can manually configure low level application procedures, giving the creator freedom to manage the incoming and outgoing data. With this functional flexibility, the microprocessor can be programmed to transmit data at configured rates and also provide interrupts to execute commands at certain instances. Some key functions that will be implemented include:
>  * Wirelessly transmit custom-made sensor data
>  * Receive transmitted data from peripheral (The device is supposed to work as both central & peripheral and uses proprietary BLE service)
>  * Execute commands based on received data
>  * Feed pulses to a neuromorphic system
----------------------------------------------

## *Data Transmission*
------------------------------------------
> #### The BLE microprocessor will be integrated into a bio-sensor circuit which will continuously return data based on its current environment. The processor will receive the sensor's data and wirelessly transmit them to a central device, where a UI will be implemented to display the receieved raw data. 
----------------------------------------

## *Recieve Data from Peripheral* 
--------------------------------------------
> #### Enabling bi-directional communication is paramount in effective communication. Along with transmitting data, the BLE chip must be able to receieve data sent by the peripheral device. The received data will automatically be parsed to a string data format. The received string data can trigger certain commands that are programmed into the chip.
--------------------------------------------

## *Command Execution* 
--------------------------------------------
> #### The BLE chip will be programmed to trigger certain actions based on the received string data of the peripheral device. Currently, the chip can execute three key commands:
> Single LED ON/OFF | Cascade Multiple LED's | Toggle Control Pins | Feed Pulses to a Neuromorphic System integrated into the nRF Sensor System 

## * Pin Usage*
--------------------------------------------
> #### Analog Input Pins
P0.02 :: CH:U <br/>
P0.03 :: CH:V <br/>
P0.28 :: CH:W <br/>
P0.29 :: CH:X <br/>
P0.30 :: CH:Y <br/>
P0.31 :: CH:Z in BSPWon iOS Application <br/>

> #### Already Used Pins (On-Board)
P0.21 :: RESET Button <br/>


> #### Pulse Feeding Pins (12 GPIOs in total) 
P0.04 <br/>
P0.05 <br/>
P0.07 <br/>
P0.09 <br/>
P0.11 <br/>
P0.12 <br/>
P0.13 <br/>
P0.14 <br/>
P0.15 <br/>

> #### Control Pins
P0.11 :: Control Pin 1<br/>
P0.12 :: Control Pin 2<br/>
P0.13 :: Control Pin 3<br/>
P0.14 :: Control Pin 4<br/>

> #### Cascade Action Pins 
P0.11 <br/>
P0.12 <br/>
P0.13 <br/>  
P0.14 <br/> 
P0.15 <br/> 

> #### Input from the Neuromorphic ML Classification result
P0.16 <br/>
P0.17 <br/>
P0.18 <br/>  
P0.19 <br/>
P0.20 <br/>
