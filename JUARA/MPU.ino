void inisialisasiGYRO() {
  byte status = mpu.begin();
  delay(1000);
  mpu.calcOffsets(); // gyro and accelero
}

void hitungGYRO() {
  //Set angular payload
  roll = (mpu.getAngleX());
  pitch = (mpu.getAngleY());
  yaw = (mpu.getAngleZ());
}
