#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  float H = dht.readHumidity();
  float T = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.println(H);
  Serial.print("Temperature: ");
  Serial.print(T);
  Serial.println(" °C");
  delay(3000);
}
