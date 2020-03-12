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
  //Handle WebSocket event
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
}

void loop()
{
  mpu.readData();
  MPU6050_Data data = mpu.getCurrent();
  ws.printfAll("{ \"aX\": %f, \"aY\": %f, \"aZ\": %f }", data.ax, data.ay, data.az);
  delay(200);
}