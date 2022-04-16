#include "BMI085.h"
#include "Arduino.h"
#include "Wire.h"

uint8_t BMI088_ACC::writeToAcc(uint8_t reg, uint8_t data){
    Wire.beginTransmission(acc_address);
    Wire.write(reg);
    Wire.write(data);
    return Wire.endTransmission();
}



BMI085::BMI085(){};

void BME085::write(int addr, int reg, int data) {
    Wire.beginTransmission(addr>>1);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission(true);
};

void BMI055::read_accel() {

    Wire.beginTransmission(BMI085_ACC_ADDR>>1);
    Wire.write(ACC_X_LSB);
    Wire.requestFrom(BMI055_ACC_ADDR>>1, 6, true);
    
    accel.y = (int16_t)(Wire.read()|Wire.read()<<8) * 0.00239501953;
    accel.x = (int16_t)(Wire.read()|Wire.read()<<8) * 0.00239501953;
    accel.z = (int16_t)(Wire.read()|Wire.read()<<8) * 0.00239501953;

    Wire.endTransmission(true);
};