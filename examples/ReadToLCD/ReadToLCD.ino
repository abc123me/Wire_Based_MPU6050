#include "MPU.h"
#include "Wire.h"
#include "LiquidCrystal.h"

const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
MPU6050 thingy; //Declare the MPU6050 device

void setup(){
  lcd.begin(16, 2);
  thingy.begin();
  if(!thingy.test()) { //Contacts the MPU6050 and checks its id to see if its on the bus
    lcd.setCursor(0, 0); 
    lcd.write("MPU6050 error");
  } else {
    lcd.setCursor(0, 0);
    lcd.write("Ready!");
  }
  delay(1000);
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
