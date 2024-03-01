void Mqtt() {

  hub.sendUpdate("light");
  hub.sendGet("light");

  hub.sendUpdate("feed");
  hub.sendGet("feed");

  hub.sendUpdate("heat");
  hub.sendGet("heat");

  hub.sendUpdate("wather");
  hub.sendGet("wather");

  hub.sendUpdate("door");
  hub.sendGet("door");

  hub.sendUpdate("eggs");
  hub.sendGet("eggs");

  hub.sendUpdate("alight");
  hub.sendGet("alight");

  hub.sendUpdate("afeed");
  hub.sendGet("afeed");

  hub.sendUpdate("awather");
  hub.sendGet("awather");

  hub.sendUpdate("adoor");
  hub.sendGet("adoor");
  
}
