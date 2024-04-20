void inisialisasiBME() {
  unsigned status;
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin();
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                     "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void hitungBME() {
  pressure1 = bmp.readPressure();

  altitude_mdpl = bmp.readAltitude(SEALEVELPRESSURE_HPA);

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
  altPrev = altitude1;
}
