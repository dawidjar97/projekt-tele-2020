#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <Wire.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include "mpu6050.h"


MPU6050 mpu;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

const char* ssid = "ESP32";
const char* pass = "";

void onEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  //Handle WebSocket event Client -> Server
}

void setup()
{
  Serial.begin(9600);

  if (!mpu.begin())
  {
    Serial.println("Sensor init failed");
    while (1)
      yield();
  }
  
  SPIFFS.begin();
  WiFi.softAP(ssid, pass);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  ws.onEvent(onEvent);
  server.addHandler(&ws);

  server.serveStatic("/", SPIFFS, "/");
  server.begin();

  

  Serial.print("float: "); Serial.println((int)sizeof(float));
  Serial.print("word: "); Serial.println((int)sizeof(word));
}

void loop()
{
  mpu.readData();
  MPU6050_Data data = mpu.getCurrent();
  // ws.printfAll("{ \"pitch\": %f, \"roll\": %f }", data.pitch, data.roll);


  Serial.print("1: ");

  int pitch = data.pitch * 100;
  uint8_t arr[4] = { (pitch >> 0) & 0xFF, (pitch >> 8) & 0xFF, (pitch >> 16) & 0xFF, (pitch >> 24) & 0xFF};
  Serial.println( pitch );  
  ws.binaryAll(arr, 4);

  delay(60);
}