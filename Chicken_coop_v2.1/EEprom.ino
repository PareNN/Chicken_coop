void EE_startup() {
  // старт епром
  EEPROM.begin(1000);  // старт епром
  delay(100);
  EEPROM.get(0, cfg);
 }

void EE_update() {
  EEPROM.put(0, cfg);
  
  EEPROM.commit();
}

