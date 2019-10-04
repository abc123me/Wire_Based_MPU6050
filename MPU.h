#ifndef _MPU6050_H
#define _MPU6050_H

#pragma message "Universal MPUXXXX library (c) Jeremiah Lowe 2019-2020"

#include "Wire.h"

#define ONE_G                   9.80665

#define MPU_DEFAULT_ADDRESS     0x68
#define AK8963_DEFAULT_ADDRESS  0x0C

#define MPU_ACCEL_RANGE_2G      0b00
#define MPU_ACCEL_RANGE_4G      0b01
#define MPU_ACCEL_RANGE_8G      0b10
#define MPU_ACCEL_RANGE_16G     0b11
#define MPU_GYRO_RANGE_250DPS   0b00
#define MPU_GYRO_RANGE_500DPS   0b01
#define MPU_GYRO_RANGE_1000DPS  0b10
#define MPU_GYRO_RANGE_2000DPS  0b11

#define _MPU_GYRO_START         0x43
#define _MPU_ACCEL_START        0x3B
#define _MPU_TEMP_START         0x41
#define _MPU_ACCEL_CONFIG_ADDR  0x1C
#define _MPU_GYRO_CONFIG_ADDR   0x1B
#define _MPU_INTERRUPT_EN_ADDR  0x38
#define _MPU_BYPASS_EN_ADDR     0x37
#define _MPU_POWER_REG          0x6B

#define _AK8963_MAGNET_START    0x03
#define _AK8963_STATUS1         0x02
#define _AK8963_STATUS2         0x09
#define _AK8963_CTRL1           0x0A
#define _AK8963_CTRL2           0x0B

#define _MPU_WHO_AM_I_ADDR      0x75
#define _MPU9250_IDENTIFIER     0x71
#define _MPU6050_IDENTIFIER     0x72

#define MPU_MAGNETOMETER        1
#define MPU_GYROMETER           2
#define MPU_ACCELEROMETER       4
#define MPU_THERMOMETER         8

enum Axis { XAxis = 0, YAxiz = 1, ZAxis = 2, WAxis = 3 };
enum AK8963Mode { Shutdown = 0, Single = 0b0001, Cont100Hz = 0b0110, Cont8Hz = 0b0010, SelfTest = 0b1000, ExtTrig = 0b0100, FuseROM = 0b1111 };

class MPU6050 {
private:
  float accelScale = 0;
  float gyroScale = 0;
  
  void wakeup();
  void setRangeCfgReg(uint8_t reg, uint8_t range);
protected:
  uint8_t address;
public:
  MPU6050() : address(MPU_DEFAULT_ADDRESS) {};
  MPU6050(uint8_t addr) : address(addr) {};
  void begin(uint32_t speed);
  void begin(){ begin(10000); }
  int16_t whoAmI();
  void setInterruptsEnabled(bool en);
  void setAccelerationRange(uint8_t range);
  void setGyroscopeRange(uint8_t range);
  void readAccelRaw(int16_t* buf);
  void readGyroRaw(int16_t* buf);
  void readAccelG(float* buf);
  void readAccelMS(float* buf);
  void readGyroDPS(float* buf);
  float readTempC();
  float readTempF(){ return readTempC() * 1.8 + 32; }
  float getAccelerationMagnitude();
  void setBypass(bool bypass);
  bool bypassOn();
  
  bool test();
  uint8_t getFeatureMask();
};
class MPU9250 : public MPU6050 {
protected:
  uint8_t mag_address = 0x0C;
public:
  MPU9250() : mag_address(AK8963_DEFAULT_ADDRESS) { address = MPU_DEFAULT_ADDRESS; };
  MPU9250(uint8_t addr, uint8_t mag_addr) : mag_address(mag_addr) { address = addr; };
  bool test();
  void begin(uint32_t speed);
  uint8_t getFeatureMask();
  uint8_t readMagnetometer(int16_t* buf);
  void setMagnetometerMode(AK8963Mode mode);
  AK8963Mode getMagnetometerMode();
  bool isMagnetometerReady();
};

#endif
