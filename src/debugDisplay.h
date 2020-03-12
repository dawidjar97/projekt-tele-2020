// #include <Arduino.h>
// #include <Adafruit_MPU6050.h>
// #include <Adafruit_Sensor.h>
// #include <U8x8lib.h>

// typedef struct{
//   float roll;
//   float pitch;
//   float x;
//   float y;
//   float z;
// } AccelerometerData;

// void drawXYZLabels(AccelerometerData &previousData, char* buff, U8X8_SH1106_128X64_NONAME_HW_I2C &u8x8,uint8_t offsetX, uint8_t offsetY);
// void drawAccelerometerData(AccelerometerData &previousData, char* buff, U8X8_SH1106_128X64_NONAME_HW_I2C &u8x8, sensors_event_t &a, uint8_t offsetX, uint8_t offsetY);
// void drawGyroData(char* buff, U8X8_SH1106_128X64_NONAME_HW_I2C &u8x8, sensors_event_t &g, uint8_t offsetX, uint8_t offsetY);
// void drawPitchRoll(AccelerometerData &previousData, char* buff, U8X8_SH1106_128X64_NONAME_HW_I2C &u8x8, sensors_event_t &a, uint8_t offsetX, uint8_t offsetY);