#ifndef _MPU6050_H
#define _MPU6050_H

#include "stdint.h"
#include "stdbool.h"
#include "Wire.h"

#define _MPU6050_GYRO_START         0x43
#define _MPU6050_ACCEL_START        0x3B
#define _MPU6050_TEMP_START         0x41
#define _MPU6050_ACCEL_CONFIG_ADDR  0x1C
#define _MPU6050_GYRO_CONFIG_ADDR   0x1B
#define _MPU6050_WHO_AM_I_ADDR      0x75

#define ONE_G 9.80665
#define MPU6050_ACCEL_RANGE_2G      0b00
#define MPU6050_ACCEL_RANGE_4G      0b01
#define MPU6050_ACCEL_RANGE_8G      0b10
#define MPU6050_ACCEL_RANGE_16G     0b11

#define MPU6050_GYRO_RANGE_250DPS   0b00
#define MPU6050_GYRO_RANGE_500DPS   0b01
#define MPU6050_GYRO_RANGE_1000DPS  0b10
#define MPU6050_GYRO_RANGE_2000DPS  0b11

enum Axis { XAxis = 0, YAxiz = 1, ZAxis = 2, WAxis = 3 };

class MPU6050{
private:
  float accelScale = 0;
  float gyroScale = 0;
  int address = 0x68;
  
  int16_t reqSingle(uint8_t reg);
  void reqCoord(int16_t* buf, uint8_t reg);
  void wakeup();
  void setRangeCfgReg(uint8_t reg, uint8_t range);
public:
  MPU6050(){
    address = 0x68;
  };
  void begin(){
    Wire.begin();
    Wire.setClock(400000);
    wakeup();
    setGyroscopeRange(MPU6050_GYRO_RANGE_250DPS);
    setAccelerationRange(MPU6050_ACCEL_RANGE_4G);
  }
  bool test();
  void setAccelerationRange(uint8_t range);
  void setGyroscopeRange(uint8_t range);
  void readAccelRaw(int16_t* buf){ reqCoord(buf, _MPU6050_ACCEL_START); }
  void readGyroRaw(int16_t* buf){ reqCoord(buf, _MPU6050_GYRO_START); }
  void readAccelG(float* buf);
  void readAccelMS(float* buf);
  void readGyroDPS(float* buf);
  float readTempC(){
    int16_t t = reqSingle(_MPU6050_TEMP_START);
    float tf = (float) t;
    return tf / 340.0 + 36.53; //Refer to page 30 in datasheet
  }
  float readTempF(){ return readTempC() * 1.8 + 32; }
  float getAccelerationMagnitude();
};

#endif
