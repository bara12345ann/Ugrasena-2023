

String dataIn = "", dataIn_command = "";
String dt[10], dt_command[10];
int i;
boolean parsing = false;
String altitudeBMP2, pressureBMP2, latGPS2, longGPS2, alt_GPS2, separate, data_command;

void pisah() {
  //Serial.println(Serial1.available());
  if (Serial2.available() > 0) {
    char inChar = (char)Serial2.read();
    dataIn += inChar;
    //Serial.println("cok");
    if (inChar == '\n') {
      parsing = true;
    }
  }


  if (parsing) {
    parsingData();
    parsing = false;
    dataIn = "";
  }
}
void parsingData() {
  int j = 0;

  //kirim data yang telah diterima sebelumnya
  //Serial.print("data masuk : ");
  //Serial.print(dataIn);

  //inisialisasi variabel, (reset isi variabel)
  dt[j] = "";
  //proses parsing data

  for (i = 1; i < 50; i++) {

    //pengecekan tiap karakter dengan karakter (#) dan (,)
    if ((dataIn[i] == '#') || (dataIn[i] == ','))
    {
      //increment variabel j, digunakan untuk merubah index array penampung
      j++;
      dt[j] = "";     //inisialisasi variabel array dt[j]

    }
    else
    {
      //proses tampung data saat pengecekan karakter selesai.
      dt[j] = dt[j] + dataIn[i];
    }
  }
  pressureBMP2 = dt[0];
  altitudeBMP2 = dt[1];
  latGPS2 = dt[2];
  longGPS2 = dt[3];
  alt_GPS2 = dt[4];

  lat2ias = longGPS2.toFloat();

  altitude2 = altitudeBMP2.toFloat();
  pressure2 = pressureBMP2.toFloat();
  lat2 = latGPS2.toFloat();
  long2 = longGPS2.toFloat();
  alt2 = alt_GPS2.toFloat();

  //kirim data hasil parsing
  Serial.print("data 1 : ");
  Serial.println(dt[0]);
  Serial.print("data 2 : ");
  Serial.println(dt[1]);
  Serial.print("data 3 : ");
  Serial.println(dt[2]);
  Serial.print("data 4 : ");
  Serial.println(dt[3]);
  Serial.print("data 5 : ");
  Serial.println(dt[4]);
  Serial.print("\n\n");
 
}



String dataInC = "", dataIn_commandC = "";
String dtC[10], dt_commandC[10];
int iC;
boolean parsingC = false;

void pisahC() {
  //Serial.println(Serial1.available());
  if (Serial1.available() > 0) {
    char inCharC = (char)Serial1.read();
    dataInC += inCharC;
    
    if (inCharC == '\n') {
      parsingC = true;
    }
  }


  if (parsingC) {
    parsingDataC();
    parsingC = false;
    dataInC = "";
  }
}
void parsingDataC() {
  int j = 0;

  //kirim data yang telah diterima sebelumnya
  //Serial.print("data masuk : ");
  //Serial.print(dataIn);

  //inisialisasi variabel, (reset isi variabel)
  dtC[j] = "";
  //proses parsing data

  for (iC = 1; iC < 50; iC++) {
    //pengecekan tiap karakter dengan karakter (#)
    if ((dataInC[iC] == '#'))
    {
      //increment variabel j, digunakan untuk merubah index array penampung
      j++;
      dtC[j] = "";     //inisialisasi variabel array dt[j]

    }
    else
    {
      //proses tampung data saat pengecekan karakter selesai.
      dtC[j] = dtC[j] + dataInC[iC];
    }
  }
  data_command = dtC[0];
  Serial.println(data_command);
  if (data_command == "separate\n") {
    Serial.println("rilis mas bro");
    manual = true;
  }
}
