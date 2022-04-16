#include <Wire.h> 

void setup() { 
  Wire.begin();
  Serial.begin(9600);
  // ACC_SOFTRESET
  Wire.beginTransmission(0x18);
  Wire.write(0x00);
  Wire.endTransmission();
  
  // ACC_PWR_CTRL ENABLE
  Wire.beginTransmission(0x19);
  Wire.write(0x7D);
  Wire.write(0x04);
  Wire.endTransmission();
  delay(50);
} 
void loop() {
  delay(0);
  // Set start byte as ACC_X_LSB
  Wire.beginTransmission(0x19);
  Wire.write(0x12);
  Wire.endTransmission();

  // Request 6 bytes from ACC
  Wire.beginTransmission(0x19);
  Wire.requestFrom(0x19,6); 
  byte ACC_X_LSB = Wire.read();
  byte ACC_X_MSB = Wire.read();
  byte ACC_Y_LSB = Wire.read();
  byte ACC_Y_MSB = Wire.read();
  byte ACC_Z_LSB = Wire.read();
  byte ACC_Z_MSB = Wire.read();
  Wire.endTransmission();
  Serial.print(ACC_X_LSB); Serial.print(",");
  Serial.print(ACC_X_MSB); Serial.print(",");
  Serial.print(ACC_Y_LSB); Serial.print(",");
  Serial.print(ACC_Y_MSB); Serial.print(",");
  Serial.print(ACC_Z_LSB); Serial.print(",");
  Serial.print(ACC_Z_MSB); Serial.print(",");
}
