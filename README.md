# Wire_Based_MPU6050
A Wire based MPU6050 library intended for ARM Cortex STM32 devices
## Usage
```c
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
  accel.readGyroDPS(buf);
  Serial.print("\e[0;0H\e[2J\e[H");
  Serial.print("Gyration: ");
  printCoord(buf);
  Serial.println();
  accel.readAccelG(buf);
  Serial.print("Acceleration: ");
  printCoord(buf);
  Serial.println();
  Serial.print("Temperature: " + String(accel.readTempC()) + "C (" + String(accel.readTempF()) + "F)");
  Serial.println();
  delay(250);
}
```
