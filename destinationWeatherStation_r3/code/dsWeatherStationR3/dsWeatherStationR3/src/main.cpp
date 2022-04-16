// code libraries
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define lightSensor A2 // define the photoresistor as pin A2

Adafruit_SSD1306 display(128, 64, &Wire, -1); // set the dimensions of the OLED display
Adafruit_BME280 bme; // define the BME280
File myFile; // define the SD file

int i; // define i as an integer

// Setup Function
void setup() {
  pinMode(0, OUTPUT); // define the LED as an output device
  // blink LED 3 times
  for(i=0;i<3;i++){
    digitalWrite(0, HIGH);
    delay(50);
    digitalWrite(0, LOW);
    delay(50);
  }
  delay(100);
  // set serial bitrate to 57600bps
  Serial.begin(57600);
  unsigned status;
  status = bme.begin(); // start bme
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // begin OLED, set address
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  Wire.begin(); // start the i2c bus
  if(!status) while(1); // if BME is not found, infinite while loop
  // blink LED
  digitalWrite(0, HIGH); 
  delay(50);
  digitalWrite(0, LOW);
  delay(100);
  if (!SD.begin(3)) while (1); // if SD is not found, infinite while loop
  // blink LED
  digitalWrite(0, HIGH);
  delay(50);
  digitalWrite(0, LOW);
  // open the SD file
  myFile = SD.open("datalog.csv", FILE_WRITE);
  if(myFile){
    myFile.print("--------"); myFile.print(","); myFile.print("--------"); myFile.print(","); myFile.print("--------"); myFile.print(","); myFile.println("--------"); myFile.close(); // write headers to CSV file
  }
}

// Loop Function
void loop() {
  digitalWrite(0, HIGH); // turn on LED
  myFile = SD.open("datalog.csv", FILE_WRITE); //write to SD
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
  // display data on OLED
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