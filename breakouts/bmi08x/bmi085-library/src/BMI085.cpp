/*
* DeepSpace00
* deepspace00@pm.me
* 
* Copyright (c) 2022 Destination SPACE Inc.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the "Software"), to deal in the Software without restriction,
* including without limitation the rights to use, copy, modify, merge, publish, distribute,
* sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "BMI085.h"
#include "Arduino.h"
#include "Wire.h"

#define ACC_CHIP_ID  0x00
#define ACC_ERR_REG  0x02
#define ACC_STATUS  0x03
#define ACC_X_LSB   0x012
#define ACC_X_MSB   0x13
#define ACC_Y_LSB   0x14
#define ACC_Y_MSB   0x015
#define ACC_Z_LSB   0x16
#define ACC_Z_MSB   0x17
#define ACC_SENSORTIME_0  0x18
#define ACC_SENSORTIME_1  0x19
#define ACC_SENSORTIME_2  0x1A
#define ACC_INT_STAT_1  0x1D
#define ACC_TEMP_MSB 0x22
#define ACC_TEMP_LSB 0x23
#define ACC_CONF 0x40
#define ACC_RANGE   0x41
#define ACC_ACC_PWR_CONF 0x7D
#define ACC_ACC_PWR_CTRL 0x7D
#define ACC_SOFTRESET 0x7E

#define GYRO_CHIPID         0x00
#define GYRO_X_LSB          0x02
#define GYRO_X_MSB          0x03
#define GYRO_Y_LSB          0x04
#define GYRO_Y_MSB          0x05
#define GYRO_Z_LSB          0x06
#define GYRO_Z_MSB          0x07
#define GYRO_INT_STAT_1     0x0a
#define GYRO_RANGE          0x0F
#define GYRO_BW             0x10
#define GYRO_SOFTRESET      0x14
#define GYRO_INT_CTRL       0x15

#define BMI085_ACC_ADDR_1  0x19
#define BMI085_GYRO_ADDR_1 0x69
#define BMI085_ACC_ADDR_2  0x18
#define BMI085_GYRO_ADDR_2 0x68

/************************************/
#define ACC_0G_X      2048
#define ACC_1G_X      (2048+1024)
#define ACC_MINUS1G_X (2048-1024)
#define ACC_0G_Y      2048   
#define ACC_1G_Y      (2048+1024)
#define ACC_MINUS1G_Y (2048-1024)
#define ACC_0G_Z      2048       
#define ACC_1G_Z      (2048+1024)
#define ACC_MINUS1G_Z (2048-1024)

void BMI085::setAddress(uint8_t address) {
    settings.I2CAddress = address
}

bool BMI085::initialize()) {
    Wire.begin()
    Wire.beginTransmission(BMI085_ACC_ADDR_1);
    Wire.write(ACC_CHIP_ID);
    Wire.endTransmission();
    Wire.beginTransmission(BMI085_ACC_ADDR_1);
    Wire.write(ACC_ACC_PWR_CTRL);
    Wire.write(0x04);
    Wire.endTransmission();

}