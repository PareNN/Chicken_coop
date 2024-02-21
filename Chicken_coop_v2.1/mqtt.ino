void Mqtt() {

  hub.sendUpdate("light");
  hub.sendGetStr("light", String(cfg.light));

  hub.sendUpdate("feed");
  hub.sendGetStr("feed", String(cfg.feed));

  hub.sendUpdate("heat");
  hub.sendGetStr("heat", String(cfg.heat));

  hub.sendUpdate("wather");
  hub.sendGetStr("wather", String(cfg.wather));

  hub.sendUpdate("door");
  hub.sendGetStr("door", String(cfg.door));

  hub.sendUpdate("eggs");
  hub.sendGetStr("eggs", String(cfg.eggs));

  hub.sendUpdate("alight");
  hub.sendGetStr("alight", String(cfg.alight));

  hub.sendUpdate("afeed");
  hub.sendGetStr("afeed", String(cfg.afeed));

  hub.sendUpdate("awather");
  hub.sendGetStr("awather", String(cfg.awather));

  hub.sendUpdate("adoor");
  hub.sendGetStr("adoor", String(cfg.adoor));
  
}