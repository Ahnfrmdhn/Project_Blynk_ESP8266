#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "Qw11fxl-uqLo5nbsCA6m24yT-rZjV9JZ";

char ssid[]="Hotspot";
char pass[]="ahnaf12345";

#define DHTPIN D4

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;
void sendSensor(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)){
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V1, t); //suhu
  Blynk.virtualWrite(V2, h); //kelembaban
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  dht.begin();

  timer.setInterval(1000L, sendSensor);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}
