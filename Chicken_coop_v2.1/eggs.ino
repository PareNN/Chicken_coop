void Eggs() {

  lazer = digitalRead(LAZER_PIN);

  if (prev_lazer != lazer) {
    if (lazer == LOW) {
      cfg.eggs = cfg.eggs + 1;
      DEBUG("Яйца - ");
      DEBUGLN(cfg.eggs);
      EE_update();
      hub.sendUpdate("eggs");
      hub.sendGetStr("eggs", String(cfg.eggs));
    }
    prev_lazer = lazer;
  }
}
