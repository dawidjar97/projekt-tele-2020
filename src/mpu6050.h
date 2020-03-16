#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define FILTER_BANDWIDTH MPU6050_BAND_5_HZ
#define CYCLE_RATE MPU6050_CYCLE_5_HZ

typedef struct {
    float ax;
    float ay;
    float az;
    float gx;
    float gy;
    float gz;
    float roll;
    float pitch;
} MPU6050_Data;

class MPU6050
{
    public:
        MPU6050() {};
        bool begin() {
            bool b = mpu.begin();
            if(!b) return b;

            mpu.setFilterBandwidth(FILTER_BANDWIDTH);
            mpu.setCycleRate(CYCLE_RATE);

            return b;
        }

        bool getData(sensors_event_t *a, sensors_event_t *g) {
            sensors_event_t temp;
            return mpu.getEvent(a, g, &temp);
        }

        void readData() {
            //Save old data before override
            previous.ax = current.ax;
            previous.ay = current.ay;
            previous.az = current.az;
            previous.pitch = current.pitch;
            previous.roll = current.roll;

            sensors_event_t a, g;
            getData(&a, &g);

            current.gx = g.gyro.x;
            current.gy = g.gyro.y;
            current.gz = g.gyro.z;

            //Filtr 
            current.ax = 0.93 * a.acceleration.x + 0.07 * previous.ax;
            current.ay = 0.93 * a.acceleration.y + 0.07 * previous.ay;
            current.az = 0.93 * a.acceleration.z + 0.07 * previous.az;

            current.pitch = atan2((-current.ax), sqrt(current.ay * current.ay + current.az * current.az)) * RAD_TO_DEG;
            current.roll = atan2(current.ay, current.az) * RAD_TO_DEG;

            //Filtr 
            current.roll = 0.85 * current.roll + 0.15 * previous.roll;
            current.pitch = 0.85 * current.pitch + 0.15 * previous.pitch;
        }

        const MPU6050_Data & getCurrent() {
            return current;
        }

    private:
        Adafruit_MPU6050 mpu;
        MPU6050_Data previous;
        MPU6050_Data current;
};
