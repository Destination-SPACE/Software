#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
}
int dataSet = 0;
void loop() {
  Wire.beginTransmission(0x19);
  Wire.write(byte(0x00));
  Wire.endTransmission();
  delay(70);
  Wire.beginTransmission(0x19);
  Wire.write(byte(0x12));
  Wire.endTransmission();
  delay(70);
  Wire.requestFrom(0x19, 6);
  if(6 <= Wire.available()) {
    dataSet = Wire.read();
    //dataSet = dataSet << 8;
    //dataSet |= Wire.read();
    Serial.println(dataSet);
  }
  delay(100);
}
