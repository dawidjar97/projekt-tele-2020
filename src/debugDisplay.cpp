// #include "debugDisplay.h"
// #include <U8x8lib.h>

// void drawGyroData(char* buff, U8X8_SH1106_128X64_NONAME_HW_I2C &u8x8, sensors_event_t &g, uint8_t offsetX = 0, uint8_t offsetY = 0) 
// {
//   //X
//   dtostrf(g.gyro.x, 4, 1, buff);
//   u8x8.drawString(2 + offsetX, offsetY, buff);

//   //Y
//   dtostrf(g.gyro.y, 4, 1, buff);
//   u8x8.drawString(2 + offsetX, 2 + offsetY, buff);

//   //Z
//   dtostrf(g.gyro.z, 4, 1, buff);
//   u8x8.drawString(2 + offsetX, 4 + offsetY, buff);
// }

// void drawAccelerometerData(AccelerometerData &previousData, char* buff, U8X8_SH1106_128X64_NONAME_HW_I2C &u8x8, sensors_event_t &a, uint8_t offsetX = 0, uint8_t offsetY = 0)
// {
//   float x = 0.93 * a.acceleration.x + 0.07 * previousData.x;
//   float y = 0.93 * a.acceleration.y + 0.07 * previousData.y;
//   float z = 0.93 * a.acceleration.z + 0.07 * previousData.z;

//   //X
//   dtostrf(x, 4, 1, buff);
//   buff[5] = ' ';
//   u8x8.drawString(2 + offsetX, offsetY, buff);
//   //Y
//   dtostrf(y, 4, 1, buff);
//   buff[5] = ' ';
//   u8x8.drawString(2 + offsetX, 2 + offsetY, buff);
//   //Z
//   dtostrf(z, 4, 1, buff);
//   buff[5] = ' ';
//   u8x8.drawString(2 + offsetX, 4 + offsetY, buff);

//   previousData.x = x;
//   previousData.y = y;
//   previousData.z = z;
// }

// void drawXYZLabels(AccelerometerData &previousData, char* buff, U8X8_SH1106_128X64_NONAME_HW_I2C &u8x8,uint8_t offsetX = 0, uint8_t offsetY = 0)
// {
//   u8x8.drawString(offsetX, offsetY, "X:");
//   u8x8.drawString(offsetX, 2 + offsetY, "Y:");
//   u8x8.drawString(offsetX, 4 + offsetY, "Z:");
// }

// void drawPitchRoll(AccelerometerData &previousData, char* buff, U8X8_SH1106_128X64_NONAME_HW_I2C &u8x8, sensors_event_t &a, uint8_t offsetX = 0, uint8_t offsetY = 0)
// {

//   roll = 0.93 * roll + 0.07 * previousData.roll;
//   pitch = 0.93 * pitch + 0.07 * previousData.pitch;

//   dtostrf(roll, 5, 2, buff);
//   buff[5] = ' ';
//   u8x8.drawString(offsetX, offsetY, "P:");
//   u8x8.drawString(2 + offsetX, offsetY, buff);

//   dtostrf(pitch, 5, 2, buff);
//   buff[5] = ' ';
//   u8x8.drawString(8 + offsetX, offsetY, "R:");
//   u8x8.drawString(10 + offsetX, offsetY, buff);

//   previousData.roll = roll;
//   previousData.pitch = pitch;
// }