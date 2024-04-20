
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <HardwareSerial.h>
#include <TinyGPS++.h>

#include  "pitches.h"
int buzzerPin = 4;

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP280 bmp; // I2C

uint32_t startKirim = 0;

// The TinyGPS++ object
TinyGPSPlus gps;

float lat1, long1, alt1, pressure1, altitude1, altitude_mdpl, alt0, altPrev;
String data_gps, packet;


void setup() {
  initBuzzer();
  
  Serial3.begin(9600);
  Serial1.begin(9600);
  Serial.begin(9600);
  inisialisasiBME();
  
  
}

void loop() {
  //Pressure, alt, lat, long, altGPS
  // dataRead
  hitungGPS();
  hitungBME();

  packet = ("#" + String(pressure1) + "," + String(altitude1) + "," + String(lat1,6) + "," + String(long1,6) + "," + String(alt1));
  if (millis() - startKirim > 1000) { // &&  mulaiKirim==true) {       //Send data every 1 sec

    Serial.println(packet);
    Serial1.println(packet);
    startKirim = millis();
  }
}
