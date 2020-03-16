#include <Arduino.h>
#include <Wire.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "FS.h"
#include "configurator.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "mpu6050.h"

MPU6050 mpu;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

#define FORMAT_SPIFFS_IF_FAILED true
String ssid = "ESP32";
String passwd = "test";
const char* path = "/cfg.xd";

void onEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  //Handle WebSocket event Client -> Server
}

void setup() 
{
    Serial.begin(9600);

    if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED))
        Serial.println("SPIFFS Mount Failed");
    else
        configurationLoad(SPIFFS,path,ssid,passwd);
    //Do usunięcia configu przycisk wywołujący: deleteFile(SPIFFS, path);

  if (!mpu.begin())
  {
    Serial.println("Sensor init failed");
    while (1)
      yield();
  }
  
  //SPIFFS.begin();
  WiFi.softAP(ssid, pass);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  ws.onEvent(onEvent);
  server.addHandler(&ws);

  server.serveStatic("/", SPIFFS, "/");
  server.begin();

}

void loop()
{
  mpu.readData();
  MPU6050_Data data = mpu.getCurrent();

  int pitch = data.pitch * 100;
  int roll = data.roll * 100;

  uint8_t arr[8] = { 
    (pitch >> 0) & 0xFF, (pitch >> 8) & 0xFF, (pitch >> 16) & 0xFF, (pitch >> 24) & 0xFF,
    (roll >> 0) & 0xFF, (roll >> 8) & 0xFF, (roll >> 16) & 0xFF, (roll >> 24) & 0xFF
    };

  ws.binaryAll(arr, 8);

  delay(60);
}