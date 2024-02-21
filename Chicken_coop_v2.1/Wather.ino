void Wather() {

  if (cfg.wather != prev_wather) {
    if (cfg.wather == 1) {
      digitalWrite(WATHER_PIN, cfg.wather);
      prev_wather = cfg.wather;
      hub.sendGet("wather");
      DEBUGLN("Наливаю воду");
      Timer_wather.setInterval(cfg.twather * 1000);
      Timer_wather.start();
      EE_update();
    }
  }


  if (Timer_wather.isReady()) {
    cfg.wather = 0;
    prev_wather = cfg.wather;
    digitalWrite(WATHER_PIN, cfg.wather);
    hub.sendGet("wather");
    hub.sendUpdate("wather");
    DEBUGLN("Вода налита");
    Timer_wather.stop();
    EE_update();
  }

  if (cfg.awather != prev_awather) {
    if (cfg.awather == 0) {
      DEBUGLN("Автовода выключена");
    }
    if (cfg.awather == 1) {
      DEBUGLN("Автовода включена");
    }
    hub.sendUpdate("awather");
    hub.sendGet("awather");
    prev_awather = cfg.awather;
    EE_update();
  }

  if (cfg.awather == 1) {
    if (cfg.wather_time1 == (ntp.hour() * 3600 + ntp.minute() * 60 + ntp.second())) {
      cfg.wather = 1;
    }

    if (cfg.wather_time2 == (ntp.hour() * 3600 + ntp.minute() * 60 + ntp.second())) {
      cfg.wather = 1;
    }

    if (cfg.wather_time3 == (ntp.hour() * 3600 + ntp.minute() * 60 + ntp.second())) {
      cfg.wather = 1;
    }

    if (cfg.wather_time4 == (ntp.hour() * 3600 + ntp.minute() * 60 + ntp.second())) {
      cfg.wather = 1;
    }
  }
}
