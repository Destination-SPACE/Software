#ifndef BMI085_h
#define BMI085_h

#include "Arduino.h"
#include "Wire.h"

// ADDRESSES
#define BMI085_ACC_ADDR_LOW 0x18
#define BMI085_ACC_ADDR_HIGH 0x19
#define BMI085_GYRO_ADDR_LOW 0x68
#define BMI085_GYRO_ADDR_HIGH 0x69

// ACC_BANDWITH
#define ACC_OSR_4 0x08
#define ACC_OSR_2 0x09
#define ACC_OSR_NORMAL 0x0A

// ACC_ODR
#define ACC_ODR_12_5HZ 0x05
#define ACC_ODR_25HZ 0x06
#define ACC_ODR_50HZ 0x07
#define ACC_ODR_100HZ 0x08
#define ACC_ODR_200HZ 0x09
#define ACC_ODR_400HZ 0x0A
#define ACC_ODR_800HZ 0x0B
#define ACC_ODR_1600HZ 0x0C

// ACC_RANGE
#define ACC_RNG_3G 0x00
#define ACC_RNG_4G 0x01
#define ACC_RNG_8G 0x02
#define ACC_RNG_16G 0x03

// GYRO_ODR
#define GYRO_ODR_2000HZ_532HZ 0x00
#define GYRO_ODR_2000HZ_230HZ 0x01
#define GYRO_ODR_1000HZ_116HZ 0x02
#define GYRO_ODR_400HZ_47HZ 0x03
#define GYRO_ODR_200HZ_23HZ 0x04
#define GYRO_ODR_100HZ_12HZ 0x05
#define GYRO_ODR_200HZ_64HZ 0x06
#define GYRO_ODR_100HZ_32HZ 0x07

// GYRO_RANGE
#define GYRO_RNG_2000DPS 0x00
#define GYRO_RNG_1000DPS 0x01
#define GYRO_RNG_500DPS 0x02
#define GYRO_RNG_250DPS 0x03
#define GYRO_RNG_125DPS 0x04

class BMI085_ACC {
    private:
        unit8_t writeToACC(unit8_t reg, uint8_t data);
        uint8_t requestFromACC(uint8_t reg, uint8_t count);
        float acc_mss_conversion
    public:
        uint8_t acc_address;
        float x, y, z;
        BMI085_ACC(uint8_t anAddress) {
            acc_anAddress = anAddress;
        }
        bool begin();
        void accConfig(uint8_t ACC_OSR, uint8_t ACC_ODR, uint8_t ACC_RANGE);
        void doACC();
};

class BMI085_GYRO {
    private:
        uint8_t writeToGyro(uint8_t reg, uint8_t data);
        uint8_t requestFromGyro(uint8_t reg, uint8_t count);

        float gyro_rad_conversion;

        //Calibration
        uint32_t sampleCount;
        float pre_x;
        float pre_y;
        float pre_z;     
    public:
        uint8_t gyro_address;

        float x, y, z;
        float x_off, y_off, z_off;

        bool gyroCal;

        BMI088_GYRO(uint8_t anAddress){
            gyro_address = anAddress;
        }

        bool begin();

        void gyroConfig(uint8_t GYRO_ODR, uint8_t GYRO_RANGE);
        
        void doGyro();

        bool calibrateGyro(uint32_t calculate_samples);

        void resetCalibration();
};

#endif