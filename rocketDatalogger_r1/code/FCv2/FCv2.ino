#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_BME280.h>

#define BMI085_accel 0x18
#define BMI085_gyro 0x69

Adafruit_BME280 bme;
int i;
File myFile;

void setup() {
  pinMode(1, OUTPUT);
  for(i=0;i<3;i++){
    digitalWrite(1, HIGH);
    delay(50);
    digitalWrite(1, LOW);
    delay(50);
  }
  delay(100);
  Wire.begin();
  Serial.begin(9600);
  unsigned status;
  status = bme.begin();
  if(!status) while(1);
  digitalWrite(1, HIGH);
  delay(50);
  digitalWrite(1, LOW);
  delay(100);
  
  if (!SD.begin(3)) while (1);
  digitalWrite(1, HIGH);
  delay(50);
  digitalWrite(1, LOW);
  
  myFile = SD.open("datalog.csv", FILE_WRITE);
  if(myFile){
    myFile.print("--------"); myFile.print(","); myFile.print("--------"); myFile.print(","); myFile.print("--------"); myFile.print(","); myFile.print("--------"); myFile.print(","); myFile.print("--------"); myFile.print(","); myFile.print("--------"); myFile.print(","); myFile.print("--------"); myFile.print(","); myFile.print("--------"); myFile.print(","); myFile.println("--------"); myFile.close();
  }
  
  // ACC_SOFTRESET
  Wire.beginTransmission(BMI085_accel);
  Wire.write(0x00);
  Wire.endTransmission();
  
  // ACC_PWR_CTRL ENABLE
  Wire.beginTransmission(BMI085_accel);
  Wire.write(0x7D);
  Wire.write(0x04);
  Wire.endTransmission();
  delay(50);
} 

void loop() {
  digitalWrite(1, HIGH);
  // Set start byte as ACC_X_LSB
  Wire.beginTransmission(BMI085_accel);
  Wire.write(0x12);
  Wire.endTransmission();

  // Request 6 bytes from ACC
  Wire.beginTransmission(BMI085_accel);
  Wire.requestFrom(BMI085_accel,6); 
  byte ACC_X_LSB = Wire.read();
  byte ACC_X_MSB = Wire.read();
  byte ACC_Y_LSB = Wire.read();
  byte ACC_Y_MSB = Wire.read();
  byte ACC_Z_LSB = Wire.read();
  byte ACC_Z_MSB = Wire.read();
  Wire.endTransmission();

  // Set start byte as RATE_X_LSB
  Wire.beginTransmission(BMI085_gyro);
  Wire.write(0x02);
  Wire.endTransmission();

  // Request 6 bytes from GYRO
  Wire.beginTransmission(BMI085_gyro);
  Wire.requestFrom(BMI085_gyro,6);
  byte GYRO_X_LSB = Wire.read();
  byte GYRO_X_MSB = Wire.read();
  byte GYRO_Y_LSB = Wire.read();
  byte GYRO_Y_MSB = Wire.read();
  byte GYRO_Z_LSB = Wire.read();
  byte GYRO_Z_MSB = Wire.read();
  Wire.endTransmission();

  float accelX = (int16_t)(ACC_X_MSB << 8 | ACC_X_LSB) * 0.00120971; 
  float accelY = (int16_t)(ACC_Y_MSB << 8 | ACC_Y_LSB) * 0.00120971; 
  float accelZ = (int16_t)(ACC_Z_MSB << 8 | ACC_Z_LSB) * 0.00120971;

  float gyroX = (int16_t)(GYRO_X_MSB << 8 | GYRO_X_LSB) * 0.03051757812;
  float gyroY = (int16_t)(GYRO_Y_MSB << 8 | GYRO_Y_LSB) * 0.03051757812;
  float gyroZ = (int16_t)(GYRO_Z_MSB << 8 | GYRO_Z_LSB) * 0.03051757812;

  myFile = SD.open("datalog.csv", FILE_WRITE);
  if(myFile){
    myFile.print(bme.readTemperature());
    myFile.print(",");
    myFile.print(bme.readPressure() / 100.0F);
    myFile.print(",");
    myFile.print(bme.readHumidity());
    myFile.print(",");
    myFile.print(accelX);
    myFile.print(",");
    myFile.print(accelY);
    myFile.print(",");
    myFile.print(accelZ);
    myFile.print(",");
    myFile.print(gyroX);
    myFile.print(",");
    myFile.print(gyroY);
    myFile.print(",");
    myFile.println(gyroZ);
    myFile.close();    
  }
  digitalWrite(1, LOW);
  Serial.print(bme.readTemperature()); Serial.print(",");
  Serial.print(bme.readPressure()); Serial.print(",");
  Serial.print(bme.readHumidity()); Serial.print(",");
  Serial.print(accelX); Serial.print(",");
  Serial.print(accelY); Serial.print(",");
  Serial.print(accelZ); Serial.print(",");
  Serial.print(gyroX); Serial.print(",");
  Serial.print(gyroY); Serial.print(",");
  Serial.println(gyroZ);
}
