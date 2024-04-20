//khusus batre < 10V
//Gain = 1/2 * 10 = 5(sesuai input maks arduino uno, teensy input maks 3.3v)
//R1 & R2 == 10kOhm
#define VoltPin (A8) //Sesuaikan pin
int adcValue;
float adcVolt;

void inisialisasiVOLT() {
  pinMode(VoltPin, INPUT);
}

void hitungVOLT(){
  adcValue = analogRead(VoltPin); 
  adcVolt = (adcValue/1023.0) ; //ini intinya buat baca voltase dari 0-5V, harusnya adcVal * 5 / 1023
  //1023 tergantung input bit kontroller, arduino 10 bit, 2^10 (cari tau teensy 4.0!)
  voltage = (560+2000)*adcVolt/560 *3.3 ;//volt; //tapi 5 ditaruh disini (5 * 2), 2 dari rumus vdevider karena out 4.5V dari 9v
}
