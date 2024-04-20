/*
  0. At values other than 12-14 m/s of the Container landing rate (jika status == 0, maka nilai error 0 dan 1 adalah 0
  1. At values other than 6-8 m/s of the Science Payload landing rate
  2. In case of the Container position data failure
  3. In case of the Science Payload position data failure
  4. In case of the release failure,
*/
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

void IAScheck() {
  /////////////////////////////////BEFORE SEPARATION/////////////////////////////////////////////////////////////////////////////////////////////
  // GPS1 check
  if (lat1 == 0) {
    IAS1[3] = '1';
  } else {
    IAS1[3] = '0';
  }


  //Descend rate before separation
  if (satellite_status <= 1) {
    IAS1[0] = '0';
  } else {
    if (descend_rate >= 12 || descend_rate <= 14) {
      IAS1[0] = '1';
    } else {
      IAS1[0] = '0';
    }
  }


  /////////////////////////////////AFTER SEPARATION/////////////////////////////////////////////////////////////////////////////////////////////
  // Pressure check
  if (pressure2 == 0) {
    IAS2[2] = '1';
  } else {
    IAS2[2] = '0';
  }

  if (lat1 == 0) {
    IAS2[3] = '1';
  } else {
    IAS2[3] = '0';
  }

  //Descend rate before separation
  if (descend_rate >= 6 || descend_rate <= 8) {
    IAS2[1] = '1';
  } else {
    IAS2[1] = '0';
  }
  //descend rate di atas 12 m/s tapi altitude < 400m
  if (descend_rate >= 12 && altitude1 <= 400) {
    IAS2[4] = '1';
  } else {
    IAS2[4] = '0';
  }
}
