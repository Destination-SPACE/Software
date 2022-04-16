#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BME280.h>
Adafruit_SSD1306 display(128, 64, &Wire, -1);
Adafruit_BME280 bme;
#define lightSensor A2
int i;
File myFile;
void setup() {
  pinMode(0, OUTPUT);
  for(i=0;i<3;i++){
    digitalWrite(0, HIGH);
    delay(50);
    digitalWrite(0, LOW);
    delay(50);
  }
  delay(100);
  Serial.begin(57600);
  unsigned status;
  status = bme.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  Wire.begin();
  if(!status) while(1);
  digitalWrite(0, HIGH);
  delay(50);
  digitalWrite(0, LOW);
  delay(100);
  if (!SD.begin(3)) while (1);
  digitalWrite(0, HIGH);
  delay(50);
  digitalWrite(0, LOW);
  myFile = SD.open("datalog.csv", FILE_WRITE);
  if(myFile){
    myFile.print("--------"); myFile.print(","); myFile.print("--------"); myFile.print(","); myFile.print("--------"); myFile.print(","); myFile.println("--------"); myFile.close();
  }
}
void loop() {
  digitalWrite(0, HIGH);
  String dataString = "";
  myFile = SD.open("datalog.csv", FILE_WRITE);
  if(myFile){
    myFile.print(bme.readTemperature());
    myFile.print(",");
    myFile.print(bme.readPressure() / 100.0F);
    myFile.print(",");
    myFile.print(bme.readHumidity());
    myFile.print(",");
    myFile.println(analogRead(lightSensor));
    myFile.close();    
  }  
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("DS Weather Station");
  display.setCursor(0, 20);
  display.print("Temperature: ");
  display.print(bme.readTemperature());
  display.print(" C");
  display.setCursor(0, 30);
  display.print("Pressure: ");
  display.print(bme.readPressure() /100.0F);
  display.print(" hPa");
  display.setCursor(0, 40);
  display.print("Humidity: ");
  display.print(bme.readHumidity(), 2);
  display.print(" %");
  display.setCursor(0,50);
  display.print("Light Level: ");
  display.print(analogRead(lightSensor));
  display.display();
  digitalWrite(0, LOW);
  delay(500);
}
