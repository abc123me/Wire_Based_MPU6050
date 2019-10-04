#include "MPU.h"
#include "Wire.h"

MPU6050 thingy; //Declare the MPU6050 device

void setup(){
  Serial.begin(9600);
  thingy.begin(); //Initialize it, you can pass in a speed in hertz
  //thingy.begin(1000); //Like so
  if(!thingy.test()) //Contacts the MPU6050 and checks its id to see if its on the bus
    Serial.println("No MPU6050 on I2C bus, please check your connection!");
  Serial.println("Ready!");
}

void printCoord(float* buf){ //Prints 3 bytes starting at buf
  Serial.print(buf[0]);
  Serial.print(", ");
  Serial.print(buf[1]);
  Serial.print(", ");
  Serial.print(buf[2]);
}

void loop(){
  float buf[3]; //12 byte buffer for storing results
  thingy.readGyroDPS(buf); //Reads the gyrometer in degrees per second
  Serial.print("\e[0;0H\e[2J\e[H");
  Serial.print("Gyration: ");
  printCoord(buf); 
  Serial.println();
  thingy.readAccelG(buf); //Reads the accelerometer in G
  //thiny.readAccelMPS(buf); //Same thing in meters per second per second
  Serial.print("Acceleration: ");
  printCoord(buf);
  Serial.println();
  Serial.print("Temperature: " + String(thingy.readTempC()) + "C (" + String(thingy.readTempF()) + "F)");
  Serial.println();
  delay(250);
}
