# Wire based MPU6050 library (works with STM32)
A Wire based MPU6050 library intended for ARM Cortex STM32 devices, but since it uses the `Wire.h` library it works with ***EVERYTHING*** and yes, you can use it to take over the world!
## Usage
 1. Download as ZIP
 2. Unzip and install into your arduino libraries folder
 3. Select Examples/MPU6050/ and experiment with them
## Boards tested
 - Arduino Uno (ATmega328P) @ 16MHz w/ 10KHz I2C
 - STM32F103 (32K) @ 72MHz w/ 400KHz I2C
## Documentation
### MPU6050.h
```c
void begin(uint32_t speed);               //Initializes the device with a custom clock speed
void begin(){ begin(10000); }             //Initializes the device with a clock speed of 10KHz
bool test();                              //Checks if the library can communicate to the device
void setInterruptsEnabled(bool en);       //Enables/disables interrupts
void setAccelerationRange(uint8_t range); //Sets the range of the accelerometer
void setGyroscopeRange(uint8_t range);    //Sets the range of the gyrometer
void readAccelRaw(int16_t* buf);          //Reads the raw value of the accelerometer into buf
void readGyroRaw(int16_t* buf);           //Reads the raw value of the gyrometer into buf
void readAccelG(float* buf);              //Reads the value of the accelerometer (in Gs) into buf
void readAccelMS(float* buf);             //Reads the value of the accelerometer (in meters per second) into buf
void readGyroDPS(float* buf);             //Reads the value of the gyrometer (in degrees per second) into buf
float readTempC();                        //Reads the temperature in degrees celcius
float readTempF();                        //Reads the temperature in degrees farenheit
float getAccelerationMagnitude();         //Gets the magnitude of the acceleration vector
```
### Valid sensor ranges / compile constants
```c
#define ONE_G                      //One G (on Earth)
#define MPU6050_ACCEL_RANGE_2G     //Accelerometer range of 2G
#define MPU6050_ACCEL_RANGE_4G     //Accelerometer range of 4G
#define MPU6050_ACCEL_RANGE_8G     //Accelerometer range of 8G
#define MPU6050_ACCEL_RANGE_16G    //Accelerometer range of 16G

#define MPU6050_GYRO_RANGE_250DPS  //Gyrometer range of 250 degrees per second
#define MPU6050_GYRO_RANGE_500DPS  //Gyrometer range of 500 degrees per second
#define MPU6050_GYRO_RANGE_1000DPS //Gyrometer range of 1000 degrees per second
#define MPU6050_GYRO_RANGE_2000DPS //Gyrometer range of 2000 degrees per second
```
