
void saveData() {
  
  if (sd.exists("Data.csv")) { // check the card is still there
    // now append new data file
    sensorData = sd.open("Data.csv", FILE_WRITE);
    Serial.println("Tersimpan");
    if (sensorData) {
      Serial.println("Tersimpan");
      if (satellite_status >= 4) {
      sensorData.println(packet2);
    } else {
      sensorData.println(packet1);
    }
      sensorData.close(); // close the file
    }
  }
}
