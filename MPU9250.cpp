#include "MPU.h"
#include "wire_util.h"

bool MPU9250::test() {
  return whoAmI() == _MPU9250_IDENTIFIER;
}
uint8_t MPU9250::getFeatureMask(){
  return MPU_GYROMETER | MPU_ACCELEROMETER | MPU_THERMOMETER | MPU_MAGNETOMETER;
};
uint8_t MPU9250::readMagnetometer(int16_t* buf){
  uint8_t raw[7];
  uint8_t exit = 0;
  Wire.beginTransmission(mag_address);
  Wire.write(_AK8963_MAGNET_START);
  Wire.endTransmission();
  Wire.requestFrom(mag_address, 7);
  for(uint8_t i = 0; i < 7; i++)
    raw[i] = Wire.read();
  if(!(raw[6] & 0x08)){
    buf[0] = raw[1] << 8 | raw[0];
    buf[1] = raw[3] << 8 | raw[2];
    buf[2] = raw[5] << 8 | raw[4];
    exit = 1;
  }
  return exit;
}
bool MPU9250::isMagnetometerReady(){
  return reqByte(mag_address, _AK8963_STATUS1) & 1;
}
void MPU9250::begin(uint32_t speed){
  ((MPU6050*) this)->begin(speed);
  writeReg(mag_address, _AK8963_CTRL2, 1);
  setMagnetometerMode(AK8963Mode::Cont100Hz);
}
void MPU9250::setMagnetometerMode(AK8963Mode mode) {
  uint8_t ctrlH = reqByte(mag_address, _AK8963_CTRL1) & 0xF0;
  uint8_t ctrlL = mode & 0x0F;
  ctrlH &= 0b00010000;
  writeReg(mag_address, _AK8963_CTRL1, ctrlH | ctrlL);
}
AK8963Mode MPU9250::getMagnetometerMode() {
  uint8_t mode = reqByte(mag_address, _AK8963_CTRL1) & 0x0F;
  if(mode == AK8963Mode::Cont100Hz)
    return AK8963Mode::Cont100Hz;
  if(mode == AK8963Mode::Cont8Hz)
    return AK8963Mode::Cont8Hz;
  if(mode == AK8963Mode::Single)
    return AK8963Mode::Single;
  if(mode == AK8963Mode::ExtTrig)
    return AK8963Mode::ExtTrig;
  if(mode == AK8963Mode::FuseROM)
    return AK8963Mode::FuseROM;
  if(mode == AK8963Mode::SelfTest)
    return AK8963Mode::SelfTest;
  return AK8963Mode::Shutdown;
}
