/*
  Wifi кормушка для кур

  // Кнопки:
  // but_feed управления кормушкой
  // but_wather управления водой

  // Переменные:
  // light - лампа
  // door - дверь
  // wather - вода
  // feed - корм
  // alight - автомат. включения света
  // atemp - автомат. включение обогревателя
  // afeed - автомат. подача корма
  // adoor - автомат. дверь
  // awather - автомат. подача воды
  // eggs - яйца
  // porc - порция для корма

  //    Переменные для температуры
  // temp температура
  // temp_p уставка температуры
  // temp_g гистерезис температуры


  Переменные времени
  // light1_on включение света
  // light1_off выключение света
  // light2_on включение света
  // light2_off выключение света
  // feed_time1 время кормления
  // feed_time2 время кормления
  // feed_time3 время кормления
  // feed_time4 время кормления
  // door_time_on открытие двери
  // door_time_off закрытие двери
  // wather_time1 Подача воды
  // wather_time2 Подача воды
  // wather_time3 Подача воды
  // wather_time4 Подача воды
*/

#define LIGHT_PIN 4    //Пин подключение реле освещения
#define DOOR_O_PIN 16  //Пин подключение реле открытия двери
#define DOOR_C_PIN 17  //Пин подключение реле закрытия двери
#define FEED_PIN 21    //Пин подключение реле кормушки
#define WATHER_PIN 22  //Пин подключение реле клапана воды
#define HEAT_PIN 23    //Пин подключение реле обогрева
#define TEMP_PIN 14    //Пин подключение датчика температуры
#define DEBUG_SERIAL   //Закомментируй чтобы выключить отладку (скорость 115200)
// #define Start_Mode     //Закоментируй после первой прошивки


#include <Arduino.h>
#include <GyverNTP.h>
GyverNTP ntp(3);
//#define ATOMIC_FS_UPDATE  // OTA обновление сжатым .gz файлом вместо .bin (для esp)
#include <GyverHub.h>
GyverHub hub("Devices", "ESP32", "");  // префикс, имя, иконка

#include <Stamp.h>
Stamp gdate;

#include <EEPROM.h>
#include "Data.h"  // данные
#include <GyverTimer.h>
#include <OneWire.h>
#include <DallasTemperature.h>


Config cfg;

// Настройка температуры
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(TEMP_PIN);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensor(&oneWire);
// arrays to hold device address
DeviceAddress insideThermometer;


// ------------ WiFi AP ------------
const char* apssid = "Chiken_coop";
const char* appass = "";


// GHbutton but_feed, but_wather, but_door, but_light, but_reset;
GTimer Timer_door, Timer_feed, Timer_wather, Timer_connect(MS, 300000), Timer_heat(MS, 60000), Timer_mqtt(MS, 60000);;
bool prev_light, prev_feed, prev_door, prev_heat, prev_wather, prev_adoor, prev_afeed, prev_alight, prev_aheat, prev_awather;
float temp;



void build(GH::Builder& b) {
  hub.setVersion("PareNN/Chicken_coop@2.2");
  b.Menu(F("Основное; Свет; Корм; Температура; Вода; Дверь; Настройки; MQTT"));
  
  if (b.show(b.menu() == 0)) {
    // GH::Update upd(&hub);
    b.Title_("tit_main", "Курятник WIFI");
    b.beginRow();
    b.Label("Температура").noLabel().size(3);
    b.Label_("temp",(String(temp))).noLabel().color(GH::Colors::Green).size(1);
    b.endRow();

    b.beginRow();
    b.Label("Яйца").noLabel().size(3);
    b.Label_("eggs",(String(cfg.eggs))).noLabel().color(GH::Colors::Green).size(1);
    b.endRow();

    b.beginRow();
    b.Label("Свет").noLabel().size(3);
    b.Switch_("light", &cfg.light).noLabel().size(1);
    b.endRow();

    b.beginRow();
    b.Label("Дверь").noLabel().size(3);
    b.Switch_("door", &cfg.door).noLabel().size(1);
    b.endRow();


    b.Label_("cur_time", ntp.timeString()).noLabel().color(GH::Colors::Red);
  }


  if (b.show(b.menu() == 1)) {
    // GH::Update upd(&hub);
    b.Title_("tit_light", "Освещение");
    b.beginRow();
    b.Label("Свет").noLabel().size(3);
    b.Switch_("light", &cfg.light).noLabel().size(1);
    b.endRow();

    b.beginRow();
    b.Label("АвтоСвет").noLabel().size(3);
    b.Switch_("alight", &cfg.alight).noLabel().size(1);
    b.endRow();

    b.Label("По времени").noLabel();
    b.beginRow();
    b.Label("Вкл").noLabel().size(2);
    b.Time_("light1_on", &cfg.light1_on).noLabel().size(4);
    b.endRow();
    b.beginRow();
    b.Label("Выкл").noLabel().size(2);
    b.Time_("light1_off", &cfg.light1_off).noLabel().size(4).color(GH::Colors::Red);
    b.endRow();

    b.beginRow();
    b.Label("Вкл").noLabel().size(2);
    b.Time_("light2_on", &cfg.light2_on).noLabel().size(4);
    b.endRow();
    b.beginRow();
    b.Label("Выкл").noLabel().size(2);
    b.Time_("light2_off", &cfg.light2_off).noLabel().size(4).color(GH::Colors::Red);
    b.endRow();
  }

  if (b.show(b.menu() == 2)) {
    // GH::Update upd(&hub);
    b.Title_("tit_feed", "Корм");
    b.beginRow();
    b.Label("Корм").noLabel().size(3);
    // if (b.Button().noLabel().size(1).click()) but_feed();
    b.Switch_("feed", &cfg.feed).noLabel().size(1);
    b.endRow();

    b.beginRow();
    b.Label("Время сек.").noLabel().size(3);
    b.Input(&cfg.porc).noLabel().size(1);
    EE_update();
    b.endRow();

    b.beginRow();
    b.Label("АвтоКорм").noLabel().size(3);
    b.Switch_("afeed", &cfg.afeed).noLabel().size(1);
    b.endRow();

    b.Label("По времени").noLabel();
    b.Time_("feed_time1", &cfg.feed_time1).label("Завтрак").color(GH::Colors::Green);
    b.Time_("feed_time2", &cfg.feed_time2).label("Полдник").color(GH::Colors::Green);
    b.Time_("feed_time3", &cfg.feed_time3).label("Обед").color(GH::Colors::Green);
    b.Time_("feed_time4", &cfg.feed_time4).label("Ужин").color(GH::Colors::Green);
  }

  if (b.show(b.menu() == 3)) {
    // GH::Update upd(&hub);
    b.Title_("tit_temp", "Температура");
    b.Label(String(temp)).noLabel().size(3);
    b.beginRow();
    b.Label("Подогрев").noLabel().size(3);
    b.Switch_("heat", &cfg.heat).noLabel().size(1);
    b.endRow();
    b.beginRow();
    b.Label("Автообогрев").noLabel().size(3);
    b.Switch_("aheat", &cfg.aheat).noLabel().size(1);
    b.endRow();

    b.beginRow();
    b.Label("Температура").noLabel().size(3);
    b.Input(&cfg.temp_p).noLabel().size(1);
    EE_update();
    b.endRow();

    b.beginRow();
    b.Label("Гистерезис").noLabel().size(3);
    b.Input(&cfg.temp_g).noLabel().size(1);
    EE_update();
    b.endRow();
  }

  if (b.show(b.menu() == 4)) {
    // GH::Update upd(&hub);
    b.Title_("tit_wather", "Вода");
    b.beginRow();
    b.Label("Вода").noLabel().size(3);
    //if (b.Button().noLabel().size(1).click()) but_wather();
    b.Switch_("wather", &cfg.wather).noLabel().size(1);
    b.endRow();

    b.beginRow();
    b.Label("Время сек.").noLabel().size(3);
    b.Input(&cfg.twather).noLabel().size(1);
    EE_update();
    b.endRow();

    b.beginRow();
    b.Label("АвтоВода").noLabel().size(3);
    b.Switch_("awather", &cfg.awather).noLabel().size(1);
    b.endRow();

    b.Label("По времени").noLabel();
    b.Time_("wather_time1", &cfg.wather_time1).label("Завтрак").color(GH::Colors::Green);
    b.Time_("wather_time2", &cfg.wather_time2).label("Полдник").color(GH::Colors::Green);
    b.Time_("wather_time3", &cfg.wather_time3).label("Обед").color(GH::Colors::Green);
    b.Time_("wather_time4", &cfg.wather_time4).label("Ужин").color(GH::Colors::Green);
  }

  if (b.show(b.menu() == 5)) {
    // GH::Update upd(&hub);
    b.Title_("tit_door", "Дверь");

    b.beginRow();
    b.Label("Дверь").noLabel().size(3);
    b.Switch_("door", &cfg.door).noLabel().size(1);
    b.endRow();

    b.beginRow();
    b.Label("Время").noLabel().size(3);
    b.Input(&cfg.tdoor).noLabel().size(1);
    EE_update();
    b.endRow();

    b.beginRow();
    b.Label("АвтоДверь").noLabel().size(3);
    b.Switch_("adoor", &cfg.adoor).noLabel().size(1);
    b.endRow();

    b.Label("По времени").noLabel();
    b.Time_("door_time_on", &cfg.door_time_on).label("Открытие").color(GH::Colors::Green);
    b.Time_("door_time_off", &cfg.door_time_off).label("Закрытие").color(GH::Colors::Red);
  }

  if (b.show(b.menu() == 6)) {
    // GH::Update upd(&hub);
    b.Title_("tit_seting", "Настройки");

    b.beginRow();
    b.Label("Подключение").noLabel().size(3);
    b.Switch_("WiFimode", &cfg.WiFimode).noLabel().size(1);
    b.endRow();

    b.Label("Логин").noLabel();
    b.Input(cfg.ssid).noLabel();
    EE_update();
    b.Label("Пароль").noLabel();
    b.Pass(cfg.pass).noLabel();
    EE_update();

    b.beginRow();
    b.Label("Сброс яиц").noLabel().size(3);
    if (b.Button().noLabel().size(1).click()) cfg.eggs = 0;
    EE_update();
    b.endRow();
  }

  if (b.show(b.menu() == 7)) {
    // GH::Update upd(&hub);
    b.Title_("tit_mqtt", "MQTT");
    b.beginRow();
    b.Label("Подключение").noLabel().size(3);
    b.Switch_("mqtt", &cfg.mqtt).noLabel().size(1);
    b.endRow();

    b.Label("Сервер").noLabel();
    b.Input(cfg.mqttHost).noLabel();
    EE_update();

    b.Label("Порт").noLabel();
    b.Input(&cfg.mqttPort).noLabel();
    EE_update();

    b.Label("Логин").noLabel();
    b.Input(cfg.mqttLogin).noLabel();
    EE_update();
    b.Label("Пароль").noLabel();
    b.Pass(cfg.mqttPass).noLabel();
    EE_update();
  }
  // upd.send();
}
void setup() {

  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(DOOR_O_PIN, OUTPUT);
  pinMode(DOOR_C_PIN, OUTPUT);
  pinMode(FEED_PIN, OUTPUT);
  pinMode(WATHER_PIN, OUTPUT);

#ifdef DEBUG_SERIAL
  Serial.begin(115200);
  DEBUGLN();
#endif

  sensor.begin();

#ifdef Start_Mode
  EEPROM.begin(1000);  // старт епром
  EE_update();
#else
  EE_startup();  // читаем епром
#endif

  prev_light = cfg.light;
  prev_feed = cfg.feed;
  prev_wather = cfg.wather;
  prev_heat = cfg.heat;
  prev_door = cfg.door;

  prev_adoor = cfg.adoor;
  prev_afeed = cfg.afeed;
  prev_alight = cfg.alight;
  prev_aheat = cfg.aheat;
  prev_awather = cfg.awather;

  digitalWrite(LIGHT_PIN, cfg.light);
  digitalWrite(HEAT_PIN, cfg.heat);


  // EE_update();
  // подключение к WiFi...
  delay(3000);
  startWiFi();

  hub.onBuild(build);  // подключаем билдер
  hub.begin();         // запускаем систему

  ntp.updateNow();
  delay(1000);
  if (ntp.synced()) DEBUGLN(ntp.timeString());
}




void loop() {
  hub.tick();  // обязательно тикаем тут
  ntp.tick();
  Light();
  Feed();
  Door();
  Eggs();
  Temperature();
  Wather();
  tryReconnect();
  if (Timer_mqtt.isReady()) Mqtt();

  // =========== ОБНОВЛЕНИЯ ПО ТАЙМЕРУ ===========
  // в библиотеке предусмотрен удобный класс асинхронного таймера
  static GH::Timer tmr(1000);  // период 1 секунда
  if (tmr) {
    hub.sendUpdate("cur_time");
    GH::Update upd(&hub);
    // upd.update("cur_time");
    upd.send();
  }
}
