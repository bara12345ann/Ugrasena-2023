int jam, menit, detik, bulan, hari, tahun;
const int UTC_offset = 7;

// The TinyGPS++ object
TinyGPSPlus gps;

void inisialisasiGPS() {
  Serial3.begin(9600);
}

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
  jam = gps.time.hour() + UTC_offset;
  hari = gps.date.day();
  menit = gps.time.minute();
  detik = gps.time.second();
  bulan = gps.date.month();
  tahun = gps.date.year();
  if (jam >= 24) {
    jam = gps.time.hour() + UTC_offset - 24;
    hari = gps.date.day() + 1;
  }
  mission_time = (String(hari) + "/" + String(bulan) + "/" + String(tahun) + "," + String(jam) + "/" + String(menit) + "/" + String(detik));
  //data_gps = (String(lat1,6) + "," + String(long1,6) + "," + String(alt1));
  smartDelay(0);
}
