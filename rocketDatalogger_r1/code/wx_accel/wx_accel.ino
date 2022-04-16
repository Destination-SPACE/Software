#include "BMI088.h"
#include "SparkFunBME280.h"
#include <Wire.h>
#include <SPI.h>
#include<SD.h>

BME280 BME;
Bmi088Accel accel(Wire,0x19);
Bmi088Gyro gyro(Wire,0x69);
File myFile;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  accel.begin();
  gyro.begin();
  BME.setI2CAddress(0x76);
  if(BME.beginI2C() == false) Serial.println("BME failed");
  if (!SD.begin(3)) while (1);
  delay(1500);
}
void loop() {
  String dataString = "";
  myFile = SD.open("datalog.txt", FILE_WRITE);
  if(myFile){
    myFile.print(BME.readFloatHumidity(), 0);
    myFile.print(",");
    myFile.print(BME.readFloatPressure(), 0);
    myFile.print(",");
    myFile.print(BME.readTempC(), 2);
    myFile.print(",");
    myFile.print(accel.getAccelX_mss());
    myFile.print(",");
    myFile.print(accel.getAccelY_mss());
    myFile.print(",");
    myFile.print(accel.getAccelZ_mss());
    myFile.print(",");
    myFile.print(gyro.getGyroX_rads());
    myFile.print(",");
    myFile.print(gyro.getGyroY_rads());
    myFile.print(",");
    myFile.print(gyro.getGyroZ_rads());
    myFile.print(",");
  }
  accel.readSensor();
  gyro.readSensor();
  Serial.print(BME.readFloatHumidity(), 0);
  Serial.print("\t");
  Serial.print(BME.readFloatPressure(), 0);
  Serial.print("\t");
  Serial.print(BME.readTempC(), 2);
  Serial.print("\t");
  Serial.print(accel.getAccelX_mss());
  Serial.print("\t");
  Serial.print(accel.getAccelY_mss());
  Serial.print("\t");
  Serial.print(accel.getAccelZ_mss());
  Serial.print("\t");
  Serial.print(gyro.getGyroX_rads());
  Serial.print("\t");
  Serial.print(gyro.getGyroY_rads());
  Serial.print("\t");
  Serial.print(gyro.getGyroZ_rads());
  Serial.print("\n");
}
