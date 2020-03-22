#include <Arduino.h>
#include <Wire.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <FS.h>

#include "config.h"
#include "configurator.h"
#include "mpu6050.h"

#define INTERNAL_LED 2
#define RESET_BUTTON_PIN 18
#define SERIAL_BAUD 115200
#define WEBSOCKET_PATH "/ws"
#define HTTP_SERVER_PORT 80

#define DEFAULT_SSID "ESP32-Przechylomierz"
#define DEFAULT_PASSWORD "12345678"

MPU6050 mpu;
AsyncWebServer server(HTTP_SERVER_PORT);
AsyncWebSocket ws(WEBSOCKET_PATH);

bool espReboot = false;

void setup()
{
  SPIFFS.begin();

  #if DEBUG
    Serial.begin(SERIAL_BAUD);
  #endif

  if (!mpu.begin())
  {
    #if DEBUG
      Serial.println("Sensor init failed");
    #endif

    while (1)
      yield();
  }

  pinMode(RESET_BUTTON_PIN, INPUT_PULLDOWN);
  bool buttonState = digitalRead(RESET_BUTTON_PIN);

  #if DEBUG
    Serial.print("Stan przycisku: "); Serial.println(buttonState);
  #endif

  if (buttonState) //Usuniecie konfiguracji
  {
    deleteFile(SPIFFS, CONFIG_PATH);
    
    #if DEBUG
      Serial.println("Konfiguracja usunieta, restart systemu.");
    #endif
    pinMode(INTERNAL_LED, OUTPUT);
    digitalWrite(INTERNAL_LED, HIGH);
    delay(500);
    digitalWrite(INTERNAL_LED, LOW);
    ESP.restart();
  }
  
  if(isConfigurationCompleted(SPIFFS)) {
    #if DEBUG
      Serial.println("Well yes");
    #endif

    String ssid, password;

    if(!loadConfiguration(SPIFFS, ssid, password)) {
      #if DEBUG
        Serial.println("Something went wrong loading config file. Erasing config file");
        delay(500);
      #endif

      deleteFile(SPIFFS, CONFIG_PATH);
      ESP.restart();
    }

    WiFi.softAP(ssid.c_str(), password.c_str());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(SPIFFS, "/index.html");
    });

    server.on("/delete-config", HTTP_GET, [](AsyncWebServerRequest *request) {
      deleteFile(SPIFFS, CONFIG_PATH);
      request->send(200, String(), "RIP AND TEAR UNTIL ITS ERASED");
      espReboot = true;
    });

  } else { //BUT
    #if DEBUG
      Serial.println("Actually no");
    #endif

    WiFi.softAP(DEFAULT_SSID, DEFAULT_PASSWORD);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(SPIFFS, "/initial_config_hello.html");
    });

    server.on("/initial_config.html", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(SPIFFS, "/initial_config.html");
    });

    server.on("/initial_config_ready.html", HTTP_POST, [](AsyncWebServerRequest *request) {
      if(request->hasParam("wifi-name", true) && request->hasParam("wifi-password", true) && request->hasParam("wifi-password-repeat", true)) {
        AsyncWebParameter* wifiName = request->getParam("wifi-name", true);
        AsyncWebParameter* wifiPassword = request->getParam("wifi-password", true);
        AsyncWebParameter* wifiPasswordR = request->getParam("wifi-password-repeat", true);

        #if DEBUG
          Serial.print("Wifi-Name: "); Serial.println(wifiName->value().c_str());
          Serial.print("Wifi-Password: "); Serial.println(wifiPassword->value().c_str());
          Serial.print("Wifi-PasswordR: "); Serial.println(wifiPasswordR->value().c_str());
        #endif

        request->send(SPIFFS, "/initial_config_ready.html", String(), false, [&wifiName](const String& var) {
          if(var == "NAZWA_SIECI") 
            return wifiName->value();
          return String();
        });

        if(!saveConfiguration(SPIFFS, wifiName->value(), wifiPassword->value())) {
          #if DEBUG
            Serial.println("Something went horribly wrong.");
            pinMode(INTERNAL_LED, OUTPUT);
            digitalWrite(INTERNAL_LED, HIGH);
          #endif
        }

        espReboot = true;
      }
    });
  }

  IPAddress IP = WiFi.softAPIP();
  #if DEBUG
    Serial.print("AP IP address: "); Serial.println(IP);
  #endif

  server.addHandler(&ws);
  server.serveStatic("/static/", SPIFFS, "/static/");
  server.begin();
}

void loop()
{
  mpu.readData();
  MPU6050_Data mpuData = mpu.getCurrent();

  /* Konwersja typu na stałoprzecinkowy */
  int p = mpuData.pitch * 100;
  int r = mpuData.roll * 100;

  uint8_t * pitch = (uint8_t *)&(p);
  uint8_t * roll = (uint8_t *)&(r);

  uint8_t data[8] = {
    pitch[0], pitch[1], pitch[2], pitch[3],
    roll[0], roll[1], roll[2], roll[3]
  };

  ws.binaryAll(data, 8);

  /* Minimalny delay przy którym kolejka webSocketa jeszcze się nie wypełnia */
  delay(60);

  if(espReboot) {
    delay(5000);
    server.end();
    WiFi.softAPdisconnect();
    ESP.restart();
  }
}

