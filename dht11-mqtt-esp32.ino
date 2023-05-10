//Wifi and Client
#include <stdio.h>
#include <PubSubClient.h>
#include <WiFi.h>
//DHT11
#include <Adafruit_Sensor.h>
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int t = 0;
int h = 0;
char T[20];
char H[20];

//SSID and PSWD
const char *ssid = "INFINITUM4E1C"; //Casa ssid
const char *password = "hhDESp3bSC"; //Casa pswd
//const char *ssid = "Doctorado"; // WiFi name
//const char *password = "docInge2018$";  // WiFi password
WiFiClient espClient;

// mqtt brocker:
const char *mqttBrocker = "broker.emqx.io";
const char *topic1 = "temp/esp32";
const char *topic2 = "hum/esp32";
const char *mqttUsername = "emqx";
const char *mqttPassword = "public";
const int mqttPort = 1883;
PubSubClient client(espClient);

void setup(){
  //serial communication
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print("Connecting to ");
    Serial.println(ssid); 
  }
  Serial.println("Connection done.");
  //connecting to a mqtt brocker:
  client.setServer(mqttBrocker, mqttPort);
  client.setCallback(callback);
  while(!client.connected()){
    String clientID = "Mata";
    clientID += String(WiFi.macAddress());
    Serial.printf("The %s tries to connect to mqtt borcker...\n",clientID.c_str());
    if(client.connect(clientID.c_str(), mqttUsername, mqttPassword)){
      Serial.println("mqtt brocker connected");
    }
    else {
      Serial.print("mqtt connection failed");
      Serial.println(client.state());
      delay(2000);
    }
  }
  //once connected publish and suscribe:
  client.publish(topic1, "Hi EMQX broker I'm a ESP32 :)");
  client.subscribe(topic1);
  client.publish(topic2, "Hi EMQX broker I'm a ESP32 :)");
  client.subscribe(topic2);
}

void loop(){
  client.loop();
  //Measure and pulibsh Temperature
  t = dht.readTemperature();
  sprintf(T, "%d", t);
  client.publish(topic1, T);
  Serial.print("The temperature is: ");
  Serial.print(t);
  Serial.println(" °C");
  //Measure and publish Humidity
  h = dht.readHumidity();
  sprintf(H, "%d", t);
  client.publish(topic2, H);
  Serial.print("The humidity is: ");
  Serial.println(h);
  delay(3000);
}

void callback(char *topic, byte *payload, unsigned int length){
  Serial.print("Message recived in topic: ");
  Serial.println(topic);
  Serial.print("The message is: ");
  for(int i=0;i<length; i++){
    Serial.print((char) payload[i]);
  }
  Serial.println();
  Serial.println("-+-+-+End+-+-+-+");
}
