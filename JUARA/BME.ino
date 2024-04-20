

unsigned long waktu = 0;

bool apogee = false;

void inisialisasiBME() {
  unsigned bme_status;
  bme_status = bme.begin();
  
  if (!bme_status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
     //-while(1)delay(10);
  }

  bme.setSampling(Adafruit_BME280::MODE_FORCED,    /* mode pengukuran */
                   Adafruit_BME280::SAMPLING_X16,   /* faktor pengambilan sampel suhu */
                   Adafruit_BME280::SAMPLING_X16,   /* faktor pengambilan sampel tekanan */
                   Adafruit_BME280::SAMPLING_NONE,  /* faktor pengambilan sampel kelembaban */
                   Adafruit_BME280::FILTER_X16,     /* faktor penyaringan data */
                   Adafruit_BME280::STANDBY_MS_0_5); /* waktu standby */
  
 // bme.setSampling(Adafruit_BME280::MODE_NORMAL,     /* mode pengukuran */
 //                  Adafruit_BME280::SAMPLING_X2,     /* faktor pengambilan sampel suhu */
 //                  Adafruit_BME280::SAMPLING_X16,    /* faktor pengambilan sampel tekanan */
 //                  Adafruit_BME280::SAMPLING_X1,    /* faktor pengambilan sampel kelembaban */
 //                  Adafruit_BME280::FILTER_X16,      /* faktor penyaringan data */
 //                  Adafruit_BME280::STANDBY_MS_0_5); /* waktu standby */
  
}

void hitungBME() {
  bme.takeForcedMeasurement(); // melakukan pengukuran paksa untuk mempercepat respons sensor
  
  temp = bme.readTemperature();
  pressure1 = bme.readPressure();

  altitude_mdpl = bme.readAltitude(SEALEVELPRESSURE_HPA);

  // kalibrasi (biar alt awal = 0
  if (altitude_mdpl != 0 && millis() < 10000) {
    alt0 = altitude_mdpl;
  }

  if (altitude_mdpl < alt0) {
    alt0 = altitude_mdpl;
  }
 
  // set actual altitude
  altitude1 = altitude_mdpl - alt0;
  
  if (altitude1 < 0) {
    altitude1 = 0;
  }

  if (altitude1 > 20.0 && altPrev > altitude1) {
    apogee = true;
  }
  altPrev = altitude1;
  
}

void hitungDESCEND() {
  /*
  if ((now_ - waktu) >= 100) {
    alt_now = altitude1 - alt_prev; //A1-A0
    descend_rate = alt_now / (float)1; //(INI MASIH KECEPATAN NAIK BUKAN TURUN)
    ascent_rate = -(descend_rate);
    alt_prev = altitude1;
    waktu = now_;
  }
  */
}
