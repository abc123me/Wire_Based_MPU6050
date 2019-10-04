#include "MPU.h"
#include "wire_util.h"

bool MPU6050::test(){
  return whoAmI() == _MPU6050_IDENTIFIER;
}
uint8_t MPU6050::getFeatureMask(){
  return MPU_GYROMETER | MPU_ACCELEROMETER | MPU_THERMOMETER;
}
void MPU6050::begin(uint32_t speed){
  Wire.begin();
  Wire.setClock(speed);
  wakeup();
  setGyroscopeRange(MPU_GYRO_RANGE_250DPS);
  setAccelerationRange(MPU_ACCEL_RANGE_4G);
  setInterruptsEnabled(false);
}

void MPU6050::setInterruptsEnabled(bool en){
  writeByte(address, en ? 1 : 0);
}
void MPU6050::wakeup() {
  writeReg(address, _MPU_POWER_REG, 0);
}
void MPU6050::setRangeCfgReg(uint8_t reg, uint8_t range) {
  writeReg(address, reg, (range & 0b11) << 3);
}
void MPU6050::setAccelerationRange(uint8_t range) {
  range &= 0b11;
  switch (range) {
    case MPU_ACCEL_RANGE_2G:  accelScale = 2;  break;
    case MPU_ACCEL_RANGE_4G:  accelScale = 4;  break;
    case MPU_ACCEL_RANGE_8G:  accelScale = 8;  break;
    case MPU_ACCEL_RANGE_16G: accelScale = 16; break;
  }
  setRangeCfgReg(_MPU_ACCEL_CONFIG_ADDR, range);
}
void MPU6050::setGyroscopeRange(uint8_t range) {
  range &= 0b11;
  switch (range) {
    case MPU_GYRO_RANGE_250DPS:  gyroScale = 250;  break;
    case MPU_GYRO_RANGE_500DPS:  gyroScale = 500;  break;
    case MPU_GYRO_RANGE_1000DPS: gyroScale = 1000; break;
    case MPU_GYRO_RANGE_2000DPS: gyroScale = 2000; break;
  }
  setRangeCfgReg(_MPU_ACCEL_CONFIG_ADDR, range);
}
void MPU6050::readGyroDPS(float* buf) {
  int16_t ibuf[3];
  reqCoord(address, ibuf, _MPU_GYRO_START);
  for (uint8_t i = 0; i < 3; i++)
    buf[i] = (ibuf[i] / 32768.0) * gyroScale;
}
void MPU6050::readAccelG(float* buf) {
  int16_t ibuf[3];
  reqCoord(address, ibuf, _MPU_ACCEL_START);
  for (uint8_t i = 0; i < 3; i++)
    buf[i] = (ibuf[i] / 32768.0) * accelScale;
}
void MPU6050::readAccelMS(float* buf) {
  int16_t ibuf[3];
  reqCoord(address, ibuf, _MPU_ACCEL_START);
  for (uint8_t i = 0; i < 3; i++)
    buf[i] = (ibuf[i] / 32768.0) * accelScale * ONE_G;
}
int16_t MPU6050::whoAmI(){
  return reqByte(address, _MPU_WHO_AM_I_ADDR);
}
float MPU6050::getAccelerationMagnitude(){
  float buf[3];
  readAccelG(buf);
  float out = 0;
  for(uint8_t i = 0; i < 3; i++)
    out += buf[i] * buf[i];
  return sqrt(out);
}
void MPU6050::readAccelRaw(int16_t* buf){ reqCoord(address, buf, _MPU_ACCEL_START); }
void MPU6050::readGyroRaw(int16_t* buf){ reqCoord(address, buf, _MPU_GYRO_START); }
float MPU6050::readTempC(){
  int16_t t = reqSingle(address, _MPU_TEMP_START);
  float tf = (float) t;
  return tf / 340.0 + 36.53; //Refer to page 30 in datasheet
}
void MPU6050::setBypass(bool bypass){
  uint8_t dat = reqByte(address, _MPU_BYPASS_EN_ADDR);
  if(bypass) dat |= 2;
  else dat ^= 2;
  writeReg(address, _MPU_BYPASS_EN_ADDR, dat);
}
bool MPU6050::bypassOn(){
  uint8_t dat = reqByte(address, _MPU_BYPASS_EN_ADDR) & 2;
  if(dat) return 1;
  return 0;
}
