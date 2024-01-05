
void Temperature() {

  if (cfg.heat != prev_heat) {
    digitalWrite(HEAT_PIN, cfg.heat);
    if (cfg.heat == 0) {
      DEBUGLN("Обогрев выключен");
    }
    if (cfg.heat == 1) {
      DEBUGLN("Обогрев включен");
    }
    //hub.update("alight");
    hub.sendGet("heat");
    prev_heat = cfg.heat;
    EE_update();
  }




  if (cfg.aheat != prev_aheat) {
    if (cfg.aheat == 0) {
      DEBUGLN("Автообогрев выключен");
    }
    if (cfg.aheat == 1) {
      DEBUGLN("Автообогрев включен");
    }
    hub.sendUpdate("aheat");
    hub.sendGet("aheat");
    prev_aheat = cfg.aheat;
    EE_update();
  }



  if (Timer_heat.isReady()) {

    sensor.requestTemperatures();
    temp = sensor.getTempCByIndex(0);
    hub.sendUpdate("temp");
    hub.sendGetFloat("temp",temp);
    DEBUGLN(temp);

    if (cfg.aheat == 1) {

      if (temp <= (cfg.temp_p - cfg.temp_g)) {
        digitalWrite(HEAT_PIN, HIGH);
        cfg.heat = 1;
        DEBUGLN("Обогрев включен");
      }

      if (temp >= (cfg.temp_p + cfg.temp_g)) {
        digitalWrite(HEAT_PIN, LOW);
        cfg.heat = 0;
        DEBUGLN("Обогрев выключен");
      }
      EE_update();
      hub.sendUpdate("heat");
      hub.sendGet("heat");
    }
  }
}
