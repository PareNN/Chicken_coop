
// ------------------- МАКРО --------------------
#ifdef DEBUG_SERIAL
#define DEBUGLN(x) Serial.println(x)
#define DEBUG(x) Serial.print(x)
#else
#define DEBUGLN(x)
#define DEBUG(x)
#endif

struct Config {

#ifdef Start_Mode
  bool light = 0;
  bool feed = 0;
  bool heat = 0;
  bool wather = 0;
  bool door = 0;

  bool alight = 0;
  bool afeed = 0;
  bool aheat = 0;
  bool awather = 0;
  bool adoor = 0;

  int porc = 1;
  int eggs = 0;
  int tdoor = 1;
  int twather = 1;

  float temp_p = 12.00;
  float temp_g = 1.00;

  // Таймеры времени
  uint32_t light1_on = 0;
  uint32_t light1_off = 0;
  uint32_t light2_on = 0;
  uint32_t light2_off = 0;
  uint32_t feed_time1 = 0;
  uint32_t feed_time2 = 0;
  uint32_t feed_time3 = 0;
  uint32_t feed_time4 = 0;
  uint32_t door_time_on = 0;
  uint32_t door_time_off = 0;
  uint32_t wather_time1 = 0;
  uint32_t wather_time2 = 0;
  uint32_t wather_time3 = 0;
  uint32_t wather_time4 = 0;


  // Нсатройки сети и MQTT
  bool WiFimode = 0;  // 0 AP, 1 local
  bool mqtt = 0;      // mqtt

  //char mqttHost[32] = "m6.wqtt.ru";
  char mqttHost[32] = "";
  //uint16_t mqttPort = 15392;
  uint16_t mqttPort = 0;
  //char mqttLogin[16] = "u_G26BLX";
  char mqttLogin[16] = "";
  //char mqttPass[16] = "c2iVM5ei";
  char mqttPass[16] = "";

  //char ssid[32] = "Parepko_NN";  // логин wifi
  char ssid[32] = "";  // логин wifi
  //char pass[32] = "28101979n";   // пароль wifi
  char pass[32] = "";   // пароль wifi

#else
  bool light;
  bool feed;
  bool heat;
  bool wather;
  bool door;

  bool alight;
  bool afeed;
  bool aheat;
  bool awather;
  bool adoor;



  int porc;
  int eggs;
  int tdoor;
  int twather;

  float temp_p;
  float temp_g;

  // Таймеры времени
  uint32_t light1_on;
  uint32_t light1_off;
  uint32_t light2_on;
  uint32_t light2_off;
  uint32_t feed_time1;
  uint32_t feed_time2;
  uint32_t feed_time3;
  uint32_t feed_time4;
  uint32_t door_time_on;
  uint32_t door_time_off;
  uint32_t wather_time1;
  uint32_t wather_time2;
  uint32_t wather_time3;
  uint32_t wather_time4;


  // Нсатройки сети и MQTT
  bool WiFimode;  // 0 AP, 1 local
  bool mqtt;      // mqtt

  char mqttHost[32];
  uint16_t mqttPort;
  char mqttLogin[16];
  char mqttPass[16];

  char ssid[32];  // логин wifi
  char pass[32];  // пароль wifi
#endif
};
