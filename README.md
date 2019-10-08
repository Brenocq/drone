# ARDrone with MQTT

Our very project for interfacins UAVs (aka drones) into IoT. In this project we developed a way to send the data collected by the drone ** Parrot ARDrone 2.0 ** to other devices using an MQTT broker.

To perform this communication we use a FIFO to transfer data between a program connected to the SDK and another connected to the MQTT. As soon as the first program receives the data, this data is sent to the program that communicates with MQTT, which sends the data to the internet.

_Developed by:_

- Breno Cunha Queiroz

- Henrique Hiram Libutti Núñez


__LRM - LABORATÓRIO DE ROBÓTICA MÓVEL - USP - ICMC__
