#include <Arduino.h>
#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin();
  delay(100);
}

void loop() {
  Wire.beginTransmission(0x19);
  Wire.write(0x00);
  Wire.endTransmission(false);
  Wire.requestFrom(0x12, 6, true);

  byte A = Wire.read();
  byte B = Wire.read();
  byte C = Wire.read();
  byte D = Wire.read();
  byte E = Wire.read();
  byte F = Wire.read();

  Serial.println(A);
  Serial.println(B);
  Serial.println(C);
  Serial.println(D);
  Serial.println(E);
  Serial.println(F);
}