# Wire based MPU6050 library (works with STM32)
A Wire based MPU6050 library intended for ARM Cortex STM32 devices, but since it uses the `Wire.h` library it works with ***EVERYTHING*** and yes, you can use it to take over the world!
## Usage
```c
#include "MPU6050.h"
#include "Wire.h"

MPU6050 thingy;

void setup(){
  Serial.begin(9600);
  thingy.begin();
  if(!thingy.test()) Serial.println("Something probably is broke however i'm not sure?");
  Serial.println("Ready!");
}

void printCoord(float* buf){
  Serial.print(buf[0]);
  Serial.print(", ");
  Serial.print(buf[1]);
  Serial.print(", ");
  Serial.print(buf[2]);
}

void loop(){
  float buf[3];
  thingy.readGyroDPS(buf);
  Serial.print("\e[0;0H\e[2J\e[H");
  Serial.print("Gyration: ");
  printCoord(buf);
  Serial.println();
  thingy.readAccelG(buf);
  Serial.print("Acceleration: ");
  printCoord(buf);
  Serial.println();
  Serial.print("Temperature: " + String(thingy.readTempC()) + "C (" + String(thingy.readTempF()) + "F)");
  Serial.println();
  delay(250);
}

```
