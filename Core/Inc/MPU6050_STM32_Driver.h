#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "MPU6050-REGISTER-MAP.h"

#define G  9.81
#define RAD_TO_DEG 57.29

#define AFS_SEL_0 16384
#define AFS_SEL_1 8192
#define AFS_SEL_2 4096
#define AFS_SEL_3 2048

#define ALPHA 0.05f


typedef struct {

	int16_t gyro_x_raw;
    int16_t gyro_y_raw;
    int16_t gyro_z_raw;

    float gyro_X;
    float gyro_Y;
    float gyro_Z;

    float gyro_pitch;
    float gyro_roll;


	int16_t accel_x_raw;
    int16_t accel_y_raw;
    int16_t accel_z_raw;

    float accel_X;
    float accel_Y;
    float accel_Z;

    float accel_pitch;
    float accel_roll;

} MPU6050_t;

uint8_t MPU6050_Init(I2C_HandleTypeDef *I2Cx);
void MPU6050_Read_MPU(I2C_HandleTypeDef *I2Cx, MPU6050_t *data_struct);
void MPU6050_Convert_Acc_Values(MPU6050_t *raw_values);
void MPU6050_Convert_Gyro_Values(MPU6050_t *raw_values);
void MPU6050_Get_Acc_Angles(MPU6050_t *raw_values);
void MPU6050_Get_Gyro_Angles(MPU6050_t *raw_values, double sample_time);
void MPU6050_Comp_Filter(MPU6050_t *uf_data);


