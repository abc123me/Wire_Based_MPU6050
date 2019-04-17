#include "MPU6050.h"
#include "Wire.h"
#include "LiquidCrystal.h"

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
MPU6050 thingy; //Declare the MPU6050 device

void mpu6050init(){
  thingy.begin();
  if(!thingy.test()) { //Contacts the MPU6050 and checks its id to see if its on the bus
    lcd.setCursor(0, 0); lcd.write("MPU6050 error");
    lcd.setCursor(0, 1); lcd.write("Retrying in 3s");
    delay(3000);
    mpu6050init();
  }
}
void setup(){
  lcd.begin(16, 2);
  mpu6050init();
  lcd.setCursor(0, 0);
  lcd.write("Ready!");
}

void lcdWriteCoord(float* buf){
  String s = String(buf[0]);
  lcd.write("X");
  lcd.write(s.c_str());
  s = String(buf[1]);
  lcd.write(" Y");
  lcd.write(s.c_str());
  s = String(buf[2]);
  lcd.write(" Z");
  lcd.write(s.c_str());
}
void loop(){
  float buf[3];
  thingy.readGyroDPS(buf); //Reads the gyrometer in degrees per second
  lcd.setCursor(0, 0); lcd.write("Rotation (deg/s)");
  lcd.setCursor(0, 1); lcdWriteCoord(buf);
  delay(500);
  thingy.readAccelG(buf); //Reads the accelerometer in G'
  lcd.setCursor(0, 0); lcd.write("Acceleration (G)");
  lcd.setCursor(0, 1); lcdWriteCoord(buf);
  delay(500);
  lcd.setCursor(0, 0); lcd.write("Temperature: ");
  lcd.setCursor(0, 1);
  String s = String(thingy.readTempC());
  lcd.write(s.c_str()); 
  lcd.write("C (");
  s = String(thingy.readTempF());
  lcd.write(s.c_str());
  lcd.write("F)");
  delay(500);
}
