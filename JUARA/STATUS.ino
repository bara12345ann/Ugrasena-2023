/*
   0 = ready to flight
   1 = ascent
   2 = model satellite descend
   3 = release
   4 = science payload descend
   5 = Recovery (Payload Ground Contact)
   6 = Packet Video (500 KB) Received
   7 = Packet Video (500 KB) Sent (Bonus Mission)
*/

void state() {
  if (satellite_status == 0 && ascent_rate > 3) { //kecepatan naik (testing ascent rate sesuaikan) (3  1)
    satellite_status = 1; //ascent
  }
  else if (satellite_status == 1 && apogee == true) {
    satellite_status = 2; //model sattelite descend
  }
  else if ((satellite_status == 2 && altitude1 <= 400) || manual == true) { //tinggi separasi disesuaikan (400   20)
    satellite_status = 4; //release
    manual = false;
  }
  else if (satellite_status == 4 && descend_rate < 2) {
    satellite_status = 5; //recovery
  }
  else if (satellite_status == 5 && videoTransfer == 1) { // ini state ke 6 setelah landing atau setelah bisa langsung state 6 (?)
    satellite_status = 6; //recovery
  }
  else if (satellite_status == 6 && bonusMission == 1) {
    satellite_status = 7; //recovery
  }
}
