/*
void but_feed() {
  digitalWrite(FEED_PIN, HIGH);
  DEBUGLN("Насыпаем корм");
  hub.sendGet("feed");
  Timer_feed.setInterval(cfg.porc * 1000);
  Timer_feed.start();
}
*/

void Feed() {

  if (cfg.feed != prev_feed) {
    if (cfg.feed == 1) {
      digitalWrite(FEED_PIN, cfg.feed);
      prev_feed = cfg.feed;
      DEBUGLN("Насыпаем корм");
      hub.sendGet("feed");
      Timer_feed.setInterval(cfg.porc * 1000);
      Timer_feed.start();
      EE_update();
    }
  }


  if (Timer_feed.isReady()) {
    cfg.feed = 0;
    prev_feed = cfg.feed;
    hub.sendGet("feed");
    hub.sendUpdate("feed");
    digitalWrite(FEED_PIN, cfg.feed);
    DEBUGLN("Корм насыпан");
    Timer_feed.stop();
    EE_update();
  }

  if (cfg.afeed != prev_afeed) {
    if (cfg.afeed == 0) {
      DEBUGLN("Автокорм выключен");
    }
    if (cfg.afeed == 1) {
      DEBUGLN("Автокорм включен");
    }
    hub.sendUpdate("afeed");
    hub.sendGet("afeed");
    prev_afeed = cfg.afeed;
    EE_update();
  }


  if (cfg.afeed == 1) {

    if (cfg.feed_time1 == (ntp.hour() * 3600 + ntp.minute() * 60 + ntp.second())) {
      cfg.feed = 1;
    }
    if (cfg.feed_time2 == (ntp.hour() * 3600 + ntp.minute() * 60 + ntp.second())) {
      cfg.feed = 1;
    }
    if (cfg.feed_time3 == (ntp.hour() * 3600 + ntp.minute() * 60 + ntp.second())) {
      cfg.feed = 1;
    }
    if (cfg.feed_time4 == (ntp.hour() * 3600 + ntp.minute() * 60 + ntp.second())) {
      cfg.feed = 1;
    }
  }
}
