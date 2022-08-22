#include "I2Cdev.h"
#include "MPU6050.h"
#include "HMC5883L.h"
#include "Wire.h"
#include "Adafruit_Sensor.h"
     
const int MPU_ADDR = 0x68;

// Magnetometer class default I2C address is 0x1E
// specific I2C addresses may be passed as a parameter here
// this device only supports one I2C address (0x1E)
HMC5883L mag1;
HMC5883L mag2;
int16_t m1x, m1y, m1z;
int16_t m2x, m2y, m2z;

// Accel/Gyro class default I2C address is 0x68 (can be 0x69 if AD0 is high)
// specific I2C addresses may be passed as a parameter here
MPU6050 accelgyro1;
MPU6050 accelgyro2;
int16_t a1x, a1y, a1z;
int16_t a2x, a2y, a2z;
int16_t g1x, g1y, g1z;
int16_t g2x, g2y, g2z;

void TCA9548A(uint8_t i){
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << i);          // send byte to select i
  Wire.endTransmission();
}

void displaySensorDetails1(int i)
{
  TCA9548A (i);
  accelgyro1.getMotion6(&a1x, &a1y, &a1z, &g1x, &g1y, &g1z);
  mag1.getHeading(&m1x, &m1y, &m1z);
  Serial.print(i); Serial.print(",");
  Serial.print(a1x/4096.0); Serial.print(",");
  Serial.print(a1y/4096.0); Serial.print(",");
  Serial.print(a1z/4096.0); Serial.print(",");
  //Serial.print(g1x/131); Serial.print(",");
  //Serial.print(g1y/131); Serial.print(",");
  //Serial.print(g1z/131); Serial.print(",");
  Serial.print(m1x); Serial.print(",");
  Serial.print(m1y); Serial.print(",");
  Serial.print(m1z); Serial.print(";");  
}

void displaySensorDetails2(int i)
{
  TCA9548A (i);
  accelgyro2.getMotion6(&a2x, &a2y, &a2z, &g2x, &g2y, &g2z);
  mag2.getHeading(&m2x, &m2y, &m2z);
  Serial.print(i); Serial.print(",");
  Serial.print(a2x/4096.0); Serial.print(",");
  Serial.print(a2y/4096.0); Serial.print(",");
  Serial.print(a2z/4096.0); Serial.print(",");
  //Serial.print(g2x/131); Serial.print(",");
  //Serial.print(g2y/131); Serial.print(",");
  //Serial.print(g2z/131); Serial.print(",");
  Serial.print(m2x); Serial.print(",");
  Serial.print(m2y); Serial.print(",");
  Serial.println(m2z); 
}


void setup()
{
  Serial.begin(38400);
  Wire.begin();
 
  TCA9548A(3);
    accelgyro1.initialize();
    Serial.println(accelgyro1.testConnection() ? "MPU6050 1 connection successful" : "MPU6050 1 connection failed");   
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x1C);                  //Talk to the ACCEL_CONFIG register (1C hex)
    //Wire.write(0b00000000);          //Setting the accel to +/- 2g
    //Wire.write(0b00001000);          //Setting the accel to +/- 4g
    Wire.write(0b00010000);            //Setting the accel to +/- 8g
    //Wire.write(0b00011000);          //Setting the accel to +/- 16g
    Wire.endTransmission(true); 
    accelgyro1.setI2CBypassEnabled(true); // set bypass mode
    mag1.initialize();
    Serial.println(mag1.testConnection() ? "HMC5883L 1 connection successful" : "HMC5883L 1 connection failed");
    
  TCA9548A(6);   
    accelgyro2.initialize();
    Serial.println(accelgyro2.testConnection() ? "MPU6050 2 connection successful" : "MPU6050 2 connection failed"); 
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x1C);                  //Talk to the ACCEL_CONFIG register (1C hex)
    //Wire.write(0b00000000);          //Setting the accel to +/- 2g
    //Wire.write(0b00001000);          //Setting the accel to +/- 4g
    Wire.write(0b00010000);            //Setting the accel to +/- 8g
    //Wire.write(0b00011000);          //Setting the accel to +/- 16g
    Wire.endTransmission(true); 
    accelgyro2.setI2CBypassEnabled(true); // set bypass mode
    mag2.initialize();
    Serial.println(mag2.testConnection() ? "HMC5883L 2 connection successful" : "HMC5883L 2 connection failed");
}

void loop()
{
  static unsigned long ms = 0;
  
  if (millis() - ms > 12)//delay time
  {
    Serial.print(ms);Serial.print(",");      
    displaySensorDetails1(3);
    displaySensorDetails2(6);
       
    ms = millis();
  }
}
