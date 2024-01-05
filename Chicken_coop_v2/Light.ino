
void Light() {

  if (cfg.light != prev_light) {
    digitalWrite(LIGHT_PIN, cfg.light);
    if (cfg.light == 0) {
      DEBUGLN("Свет выключен");
    }
    if (cfg.light == 1) {
      DEBUGLN("Свет включен");
    }
    hub.update("alight");
    // hub.sendGet("light");
    prev_light = cfg.light;
    EE_update();
  }

 if (cfg.alight != prev_alight) {
    if (cfg.alight == 0) {
      DEBUGLN("Автосвет выключен");
    }
    if (cfg.alight == 1) {
      DEBUGLN("Автосвет включен");
    }
    hub.update("alight");
    // hub.sendGet("alight");
    prev_alight = cfg.alight;
    EE_update();
  }


  if (cfg.alight == 1) {
    if (cfg.light1_on == (ntp.hour() * 3600 + ntp.minute() * 60 + ntp.second())) {
      if (cfg.light == 0) {
        cfg.light = 1;
      }
    }
    if (cfg.light2_on == (ntp.hour() * 3600 + ntp.minute() * 60 + ntp.second())) {
      if (cfg.light == 0) {
        cfg.light = 1;
      }
    }

    if (cfg.light1_off == (ntp.hour() * 3600 + ntp.minute() * 60 + ntp.second())) {
      if (cfg.light == 1) {
        cfg.light = 0;
      }
    }
    if (cfg.light2_off == (ntp.hour() * 3600 + ntp.minute() * 60 + ntp.second())) {
      if (cfg.light == 1) {
        cfg.light = 0;
      }
    }
  }

}

