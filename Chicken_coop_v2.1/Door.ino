

void Door() {

  if (cfg.door != prev_door) {
    if (cfg.door == 1) {
      digitalWrite(DOOR_C_PIN, LOW);
      digitalWrite(DOOR_O_PIN, HIGH);
      DEBUGLN("Открываю дверь");
      prev_door = 1;
    }
    if (cfg.door == 0) {
      digitalWrite(DOOR_O_PIN, LOW);
      digitalWrite(DOOR_C_PIN, HIGH);
      DEBUGLN("Закрываю дверь");
      prev_door = 0;
    }
    hub.sendUpdate("door");
    hub.sendGet("door");
    Timer_door.setInterval(cfg.tdoor * 1000);
    Timer_door.start();
    EE_update();
  }

  if (cfg.adoor != prev_adoor) {
    if (cfg.adoor == 1) {
      prev_adoor = cfg.adoor;
      DEBUGLN("Автодверь включена");
    }
    if (cfg.adoor == 0) {
      prev_adoor = cfg.adoor;
      DEBUGLN("Автодверь выключена");
    }
    hub.sendUpdate("adoor");
    hub.sendGet("adoor");
    EE_update();
  }

  if (cfg.adoor == 1) {
    if (cfg.door_time_on == (ntp.hour() * 3600 + ntp.minute() * 60 + ntp.second())) {
      if (cfg.door == 0) cfg.door = 1;
      hub.sendUpdate("door");
      EE_update();
    }
    if (cfg.door_time_off == (ntp.hour() * 3600 + ntp.minute() * 60 + ntp.second())) {
      if (cfg.door == 1) cfg.door = 0;
      hub.sendUpdate("door");
      EE_update();
    }
  }

  if (Timer_door.isReady()) {
    if (cfg.door == 1) Door_open();
    if (cfg.door == 0) Door_close();
  }
}


void Door_open() {
  DEBUGLN("Дверь открыта");
  Timer_door.stop();
  digitalWrite(DOOR_O_PIN, LOW);
  hub.sendUpdate("door");
  // hub.refresh();
}

void Door_close() {
  DEBUGLN("Дверь закрыта");
  Timer_door.stop();
  digitalWrite(DOOR_C_PIN, LOW);
  hub.sendUpdate("door");
  // hub.refresh();
}
