#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <U8x8lib.h>
#include "FS.h"
#include "SPIFFS.h"
#include "configurator.h"

Adafruit_MPU6050 mpu;
U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);

//Config start
String ssid = "ESP32";
String passwd = "test";
const char* path = "/cfg.xd";
#define FORMAT_SPIFFS_IF_FAILED true

void setup() {
    Serial.begin(9600);

    if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED))
        Serial.println("SPIFFS Mount Failed");
    else
        configurationLoad(SPIFFS,path,ssid,passwd);
    //config stop
    //Do usunięcia configu przycisk wywołujący: deleteFile(SPIFFS, path);

  if (!mpu.begin()) {
    Serial.println("Sensor init failed");
    while (1)
      yield();
  }
  Serial.println("Found a MPU-6050 sensor");

  u8x8.begin();
  u8x8.setFont(u8x8_font_pxplusibmcgathin_u);

  Serial.println(mpu.getFilterBandwidth());
  Serial.println(mpu.getGyroRange());
  Serial.println(mpu.getCycleRate());
}

char buff[7];

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  dtostrf(a.acceleration.x, 4, 1, buff);
  u8x8.drawString(0, 0, "X:");
  u8x8.drawString(2, 0, buff);

  dtostrf(a.acceleration.y, 4, 1, buff);
  u8x8.drawString(0, 2, "Y:");
  u8x8.drawString(2, 2, buff);

  dtostrf(a.acceleration.z, 4, 1, buff);
  u8x8.drawString(0, 4, "Z:");
  u8x8.drawString(2, 4, buff);
  
  dtostrf(g.gyro.x, 4, 1, buff);
  u8x8.drawString(8, 0, "X:");
  u8x8.drawString(10, 0, buff);
  
  dtostrf(g.gyro.y, 4, 1, buff);
  u8x8.drawString(8, 2, "Y:");
  u8x8.drawString(10, 2, buff);

  dtostrf(g.gyro.z, 4, 1, buff);
  u8x8.drawString(8, 4, "Z:");
  u8x8.drawString(10, 4, buff);

  double roll = atan2(a.acceleration.y , a.acceleration.z) * 57.3;
  double pitch = atan2((- a.acceleration.x) , sqrt(a.acceleration.y * a.acceleration.y + a.acceleration.z * a.acceleration.z)) * 57.3;

  // Serial.print("ROLL: ");
  // Serial.println(roll);
  // Serial.print("PICZ: ");
  // Serial.println(pitch);

  dtostrf(roll, 4, 1, buff);
  u8x8.drawString(0, 6, "P:");
  u8x8.drawString(2, 6, "     ");
  u8x8.drawString(2, 6, buff);
  dtostrf(pitch, 4, 1, buff);
  u8x8.drawString(8, 6, "R:");
  u8x8.drawString(10, 6, "     "); 
  u8x8.drawString(10, 6, buff);
}