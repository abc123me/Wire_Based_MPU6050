#include "MPU6050.h"

int16_t MPU6050::reqSingle(uint8_t reg) {
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(address, 2);
  int16_t n = 0;
  n = Wire.read() << 8 | Wire.read();
  return n;
}
void MPU6050::reqCoord(int16_t* buf, uint8_t reg) {
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(address, 6);
  buf[0] = Wire.read() << 8 | Wire.read();
  buf[1] = Wire.read() << 8 | Wire.read();
  buf[2] = Wire.read() << 8 | Wire.read();
}
void MPU6050::wakeup() {
  Wire.beginTransmission(address);
  Wire.write(0x6B); Wire.write(0);
  Wire.endTransmission();
}
void MPU6050::setRangeCfgReg(uint8_t reg, uint8_t range) {
  Wire.beginTransmission(address);
  Wire.write(reg);
  uint8_t n = (range & 0b11) << 3;
  Wire.write(n);
  Wire.endTransmission();
}
void MPU6050::setAccelerationRange(uint8_t range) {
  range &= 0b11;
  switch (range) {
    case MPU6050_ACCEL_RANGE_2G:  accelScale = 2;  break;
    case MPU6050_ACCEL_RANGE_4G:  accelScale = 4;  break;
    case MPU6050_ACCEL_RANGE_8G:  accelScale = 8;  break;
    case MPU6050_ACCEL_RANGE_16G: accelScale = 16; break;
  }
  setRangeCfgReg(_MPU6050_ACCEL_CONFIG_ADDR, range);
}
void MPU6050::setGyroscopeRange(uint8_t range) {
  range &= 0b11;
  switch (range) {
    case MPU6050_GYRO_RANGE_250DPS:  gyroScale = 250;  break;
    case MPU6050_GYRO_RANGE_500DPS:  gyroScale = 500;  break;
    case MPU6050_GYRO_RANGE_1000DPS: gyroScale = 1000; break;
    case MPU6050_GYRO_RANGE_2000DPS: gyroScale = 2000; break;
  }
  setRangeCfgReg(_MPU6050_ACCEL_CONFIG_ADDR, range);
}
void MPU6050::readGyroDPS(float* buf) {
  int16_t ibuf[3];
  reqCoord(ibuf, _MPU6050_GYRO_START);
  for (int i = 0; i < 3; i++)
    buf[i] = (ibuf[i] / 32768.0) * gyroScale;
}
void MPU6050::readAccelG(float* buf) {
  int16_t ibuf[3];
  reqCoord(ibuf, _MPU6050_ACCEL_START);
  for (int i = 0; i < 3; i++)
    buf[i] = (ibuf[i] / 32768.0) * accelScale;
}
void MPU6050::readAccelMS(float* buf) {
  int16_t ibuf[3];
  reqCoord(ibuf, _MPU6050_ACCEL_START);
  for (int i = 0; i < 3; i++)
    buf[i] = (ibuf[i] / 32768.0) * accelScale * ONE_G;
}
bool MPU6050::test() {
  Wire.beginTransmission(address);
  Wire.write(_MPU6050_WHO_AM_I_ADDR);
  Wire.endTransmission();
  Wire.requestFrom(address, 1);
  uint8_t out = Wire.read();
  return out == 0x72;
}
float MPU6050::getAccelerationMagnitude(){
    float buf[3]; readAccelG(buf);
    float out = 0;
    for(int i = 0; i < 3; i++)
      out += buf[i] * buf[i];
    return sqrt(out);
  }
