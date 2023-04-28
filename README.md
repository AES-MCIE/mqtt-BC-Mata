# Introduction

The present task's main objective is to develop and test an *MQTT Broker* based on the MQTT (Mosquitto) protocol. 

Thus, the student must run the Mosquitto service in the BeagleBone to create the Broker. Then, an ESP32 client must publish the temperature data logged by a sensor. Furthermore, the Node-RED App should be used as a client to show the data as a Graphical User Interface from the ESP32 client. 

Finally, the student must implement a basic **Alarm** indicator that turns ON when the temperature exceeds a limit value or remains OFF if the value is lower.

![](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2018/05/ESP32-MQTT-bme280.png?w=800&quality=100&strip=all&ssl=1)

# Technical Report (Readme file)

The students must consider presenting a detailed document that includes:

- MQTT Broker installation and configuration 
- ESP32 client connection (schematics) and programming code with detailed explanation
- Node-RED installation, configuration, and views

# MQTT SERVER 

## Mosquitto Installation

It is necesary to update and upgrade the actual system using these commands in the terminal:

```
sudo apt udate
sudo apt upgrate
```

Then we have to install Mosquitto

```
sudo apt install mosquitto
```

To know if the moquitto service is working, type the next command:

```
sudo systemctl status mosquitto.service
```

If the status is disabled, then type

```
sudo systemctl enable mosquitto.service
```

Then, as you can see in the next image, now if type the status command, we can see the service is enabled

*imagen de mosquitto habilitado*

## Configuration

To modificate the configuration of mosquitto, it is necessary to replace the default configuration file that is in this repository:

```
sudo cp ./mosquitto.conf /etc/mosquitto/mosquitto.conf
```

Then, create a password file instanced on the mosquitto.conf file with

```
sudo touch /etc/mosquitto/passwd
```

And finally, restart the mosquitto service

```
sudo systemctl restart mosquitto
```

## Node-REd Installation

In the terminal type

```
sudo apt install nodejs
sudo apt install npm
```

Now using the npm (Node Package Manager), install the Node-red app and the Dashboard

```
npm install node-red
npm install node-red-dashboard
```

Finally, run the app in the background and verify if node-red is runnig

```
node-red &
sudo netstat -plnt
```

To access to Node-red, go to your browser and type your localhost name with the extention ":1880", example:

```
beaglebone.local:1880
```







