//Deklarasi library
#include <Wire.h>
#include <SPI.h>
#include <HardwareSerial.h>

#include "EEPROM.h"
#include "SdFat.h"

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <MPU6050_light.h>
#include <TinyGPS++.h>
#include <PWMServo.h>

PWMServo myservo1;
PWMServo myservo2;
MPU6050 mpu(Wire);

#define SEALEVELPRESSURE_HPA (1013.25)
#define SPI_SPEED SD_SCK_MHZ(4)
#define CS 10

SdFat sd;
Adafruit_BME280 bme; // I2C

/*
   <PACKET NUMBER>v , <SATELLITE STATUS>v, <ERROR CODE>, <MISSION TIME>v,
  <PRESSURE1>v, <PRESSURE2>, <ALTITUDE1>v, <ALTITUDE2>, <ALTITUDE DIFFERENCE>,
  <DESCENT RATE>v, <TEMP>v, <BATTERY VOLTAGE>v, <GPS1 LATITUDE>v, <GPS1 LONGITUDE>v,
  <GPS1 ALTITUDE>v, <GPS2 LATITUDE>, <GPS2 LONGITUDE>, <GPS2 ALTITUDE>, <PITCH>v,
  <ROLL>v, <YAW>v, <TEAM ID>v
*/
unsigned long packet_number = 1;
int satellite_status = 0, team_id = 213111, pos = 50;
String error_code, mission_time;
float pressure2, altitude2, lat2, long2, alt2, ascent_rate;
float altitude_mdpl, pressure1, altitude1, altitude_difference, descend_rate, temp, voltage, lat1, long1, alt1, pitch, roll, yaw, lat2ias;
bool manual = false, videoTransfer = 0, bonusMission = 0;
unsigned long now_;
float initAlt,
      altPrev,
      time_prev = 0,
      time_now,
      turun = 0,
      alt0,
      alt_prev,
      alt_now;

//Deklarasi variabel
uint32_t startKirim = 0;
String packet1, packet2;
String paketKirim;
char IAS1[] = {'0', '0', '0', '0', '0'},
     IAS2[] = {'0', '0', '0', '0', '0'};

//Deklari fungsi
void initiate();
void hitung_data();
void status_check();
void pakcet_send();

void hitungGYRO();
void hitungBME();
void hitungGPS();
void hitungVOLT();
void hitungDESCEND();
void state();
void IAScheck();

void initBuzzer();
void inisialisasiGYRO();
void inisialisasiBME();
void inisialisasiGPS();
void inisialisasiVOLT();
void inisialisasiAlarm();


void packet_call1();
void packet_call2();

File sensorData;
bool IsSD = false;

int tf = 17, bn = 16;
// esp   27       25
void setup() {
  Wire.begin();
  pinMode(tf, INPUT);
  pinMode(bn, INPUT);
  /*mapping communication
     Serial1 payload gcs
     Serial2 RX data container
  */
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial5.begin(9600); // Buat komunikasi container
  pinMode(A7, INPUT);
  pinMode(A8, INPUT);
  digitalWrite(5, HIGH); //camera
  digitalWrite(6, HIGH);
  myservo1.attach(3);
  myservo2.attach(4);
  inisialisasiAlarm();

  initiate();
  initBuzzer();

  pinMode(CS, OUTPUT);

  IsSD = sd.begin(CS, SPI_SPEED);

  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(true, true); // gyro and accelero

}

void loop() {
  mpu.update();
  now_ = millis();

  //Serial.println("tes");

  if (manual == true || satellite_status >= 3) {
    //myservo1.write(10); //pin 3 60
    // myservo2.write(10); //pin 4 40

    for (pos; pos >= 0; pos--) { // goes from 0 degrees to 180 degrees, 1 degree steps
      myservo1.write(pos);              // tell servo to go to position in variable 'pos'
      myservo2.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }

  }
  else {
    myservo1.write(25);
    myservo2.write(45 );
  }

  hitung_data();

  //Serial.println(analogRead(A7));
  if (millis() - startKirim > 1000) { // &&  mulaiKirim==true) {       //Send data every 1 sec
    /*
      Serial.print(satellite_status);
      Serial.print(", ");
      Serial.print(ascent_rate);
      Serial.print(", ");
      Serial.print(altitude1);
      Serial.print(", ");
      Serial.print(IAS1);
      Serial.print(", ");
      Serial.print(IAS2);
      Serial.println(" ");
    */


    Serial.print("1 : ");
    Serial.println(packet1);
    Serial.print("2 : ");
    Serial.println(packet2);
    Serial.print("videoTransfer : ");
    Serial.println(videoTransfer);
    Serial.print("bonusMission : ");
    Serial.println(bonusMission);

    if (satellite_status >= 3) {
      Serial1.println(packet2);
    } else {
      Serial1.println(packet1);
    }
    hitungBME();
    writeEEPROM();

    alt_now = altitude1 - alt_prev; //A1-A0
    descend_rate = -(alt_now / (float)1); //(INI MASIH KECEPATAN NAIK BUKAN TURUN)
    ascent_rate = -(descend_rate);
    alt_prev = altitude1;

    /*
      if (satellite_status < 3) {
      Serial.println(packet2);
      } else {
      Serial.println(packet1);
      }*/

    saveData();
    packet_number++;
    startKirim = millis();
  }
}

void initiate() {
  assignEEPROM();
  inisialisasiGYRO();
  inisialisasiBME();
  inisialisasiGPS();
  inisialisasiVOLT();

}

void hitung_data() {
  hitungGYRO();

  hitungDESCEND();
  hitungGPS();
  hitungVOLT();
  pisah();
  pisahC();

  state();
  IAScheck();
  packet_call1();
  packet_call2();
  //pakcet_send();

  videoTransfer = digitalRead(tf);
  bonusMission = digitalRead(bn);
}

void packet_call1() {
  packet1 = (String(packet_number) + "," + String(satellite_status) + "," + String(IAS1) + "," + String(mission_time) + "," + String(pressure1) + ",0," + String(altitude1) + ",0,0," + String(descend_rate) + "," + String(temp) + "," + String(voltage) + "," + String(lat1, 6) + "," + String(long1, 6) + "," + String(alt1) + ",0,0,0," + String(pitch) + "," + String(roll) + "," + String(yaw) + "," + String(team_id));
}
void packet_call2() {
  altitude_difference = altitude2 - altitude1;
  packet2 = (String(packet_number) + "," + String(satellite_status) + "," + String(IAS2) + "," + String(mission_time) + "," + String(pressure1) + "," + String(pressure2) + "," + String(altitude1) + "," + String(altitude2) + "," + String(altitude_difference) + "," + String(descend_rate) + "," + String(temp) + "," + String(voltage) + "," + String(lat1, 5) + "," + String(long1, 5) + "," + String(alt1,1) + "," + String(lat2, 5) + "," + String(long2, 5) + "," + String(alt2, 1) + "," + String(pitch,0) + "," + String(roll,0) + "," + String(yaw,0) + "," + String(team_id));
}

void inisialisasiAlarm() {

}
