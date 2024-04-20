void assignEEPROM() {
  //Read EEPROM
  packet_number     = EEPROM.read(8) << 24  | EEPROM.read(9) << 16 | EEPROM.read(10) << 8   | EEPROM.read(11);
  packet_number++;
  //satellite_status   = EEPROM.read(4)<<24  |EEPROM.read(5)<<16 |EEPROM.read(6)<<8   |EEPROM.read(7);
  //altitude1          = EEPROM.read(8)<<24  |EEPROM.read(9)<<16 |EEPROM.read(10)<<8  |EEPROM.read(11);
}
void writeEEPROM() {

  // Save packet count Container to EEPROM
  EEPROM.write(8, (packet_number & 0xFF000000) >> 24);
  EEPROM.write(9, (packet_number & 0x00FF0000) >> 16);
  EEPROM.write(10, (packet_number & 0x0000FF00) >> 8);
  EEPROM.write(11,  packet_number & 0x000000FF);
  // Save Software State to EEPROM
  /*
    EEPROM.write(4, (satellite_status & 0xFF000000) >> 24);
    EEPROM.write(5, (satellite_status & 0x00FF0000) >> 16);
    EEPROM.write(6, (satellite_status & 0x0000FF00) >> 8);
    EEPROM.write(7,  satellite_status & 0x000000FF);
    // Save Altitude referance to EEPROM
    EEPROM.write(8, (altitude1 & 0xFF000000) >> 24);
    EEPROM.write(9, (altitude1 & 0x00FF0000) >> 16);
    EEPROM.write(10, (altitude1 & 0x0000FF00) >> 8);
    EEPROM.write(11,  (altitude1 & 0x000000FF));
    //print_message("Write to EEPROM");*/
}
