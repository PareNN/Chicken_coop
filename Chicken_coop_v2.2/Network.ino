void startWiFi() {
  DEBUGLN("Start WIFI");
  if (!cfg.WiFimode) setupAP();  // режим точки доступа
  else setupLocal();             // подключаемся к точке
}

void setupAP() {
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  delay(100);
  WiFi.softAP(apssid, appass);
  //server.begin();
  DEBUGLN("Setting AP Mode");
  DEBUG("AP IP: ");
  DEBUGLN(WiFi.softAPIP());
  delay(500);
}

void setupLocal() {
  if (cfg.ssid[0] == NULL && cfg.pass[0] == NULL) {
    DEBUGLN("WiFi not configured");
    setupAP();
  } else {
    DEBUG("Connecting to ... ");
    DEBUGLN(cfg.ssid);
    DEBUGLN(cfg.pass);
    WiFi.softAPdisconnect();
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    delay(100);
    uint32_t tmr = millis();
    bool connect = false;
    //    int8_t count = 0;
    byte failCount = 0;
    while (1) {
      WiFi.begin(cfg.ssid, cfg.pass);
      while (millis() - tmr < 10000) {
        if (WiFi.status() == WL_CONNECTED) {
          connect = true;
          break;
        }
      }
      if (connect) {
        Timer_connect.stop();
        DEBUG("Connected! Local IP: ");
        DEBUGLN(WiFi.localIP());
        delay(1000);

        ntp.begin();
        ntp.setHost("pool.ntp.org");
        
        if (cfg.mqtt == 1) hub.mqtt.config(cfg.mqttHost, cfg.mqttPort, cfg.mqttLogin, cfg.mqttPass);
        
        return;
      } else {
        DEBUGLN("Failed!");
        failCount++;

        tmr = millis();
        if (failCount >= 3) {
          Timer_connect.start();  // попробуем позже
          setupAP();
          return;
        }
      }
    }
  }
}


void tryReconnect() {
  if (Timer_connect.isReady()) {
    DEBUGLN("Reconnect");
    startWiFi();
  }
}