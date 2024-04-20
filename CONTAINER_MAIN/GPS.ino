static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (Serial3.available())
      gps.encode(Serial3.read());
  } while (millis() - start < ms);
}

void hitungGPS() {
  lat1 = gps.location.lat();
  long1 = gps.location.lng();
  alt1 = gps.altitude.meters();
  //mission_time = (String(hari) + "/" + String(bulan) + "/" + String(tahun) + "," + String(jam) + "/" + String(menit) + "/" + String(detik));
  data_gps = (String(lat1, 6) + "," + String(long1, 6) + "," + String(alt1));
  smartDelay(0);
}
