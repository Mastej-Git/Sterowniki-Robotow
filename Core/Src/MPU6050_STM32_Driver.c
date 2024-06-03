#include "MPU6050_STM32_Driver.h"

const uint16_t i2c_timeout = 100;

uint8_t MPU6050_Init(I2C_HandleTypeDef *I2Cx) {
    uint8_t check;
    uint8_t Data;

    HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, WHO_AM_I, 1, &check, 1, i2c_timeout);

    if (check == 104) {

        Data = 0;
        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, PWR_MGMT_1, 1, &Data, 1, i2c_timeout);

        Data = 0x07;
        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, SMPLRT_DIV, 1, &Data, 1, i2c_timeout);

        Data = 0x00;
        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, ACCEL_CONFIG, 1, &Data, 1, i2c_timeout);

        Data = 0x00;
        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, GYRO_CONFIG, 1, &Data, 1, i2c_timeout);
        return 0;
    }
    return 1;
}

void MPU6050_Read_MPU(I2C_HandleTypeDef *I2Cx, MPU6050_t *data_struct) {
    uint8_t Rec_Data[6];

    HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, GYRO_XOUT_H_R_GYRO_XOUT, 1, Rec_Data, 6, i2c_timeout);

    data_struct->gyro_x_raw = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    data_struct->gyro_y_raw = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    data_struct->gyro_z_raw = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

    HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, ACCEL_XOUT_H_R_ACCEL_XOUT, 1, Rec_Data, 6, i2c_timeout);

    data_struct->accel_x_raw = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    data_struct->accel_y_raw = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    data_struct->accel_z_raw = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);
}

void MPU6050_Convert_Acc_Values(MPU6050_t *raw_values) {
	raw_values->accel_X = raw_values->accel_x_raw*((2*G)/32768);
	raw_values->accel_Y = raw_values->accel_y_raw*((2*G)/32768);
	raw_values->accel_Z = raw_values->accel_z_raw*((2*G)/32768);
};

void MPU6050_Convert_Gyro_Values(MPU6050_t *raw_values) {
	raw_values->gyro_X = raw_values->gyro_x_raw/131.0;
	raw_values->gyro_Y = raw_values->gyro_y_raw/131.0;
	raw_values->gyro_Z = raw_values->gyro_z_raw/131.0;
};

void MPU6050_Get_Acc_Angles(MPU6050_t *raw_values) {
	if ((raw_values->accel_X < G) && (raw_values->accel_X > -G)) {
		raw_values->accel_pitch = - RAD_TO_DEG * asin(raw_values->accel_X / G);
	}
	raw_values->accel_roll = - RAD_TO_DEG * atan2(raw_values->accel_Y, raw_values->accel_Z);
}


void MPU6050_Get_Gyro_Angles(MPU6050_t *raw_values, double sample_time) {
	raw_values->gyro_pitch = raw_values->gyro_pitch + raw_values->gyro_Y * sample_time;
	raw_values->gyro_roll = raw_values->gyro_roll - raw_values->gyro_X * sample_time;
}

void MPU6050_Comp_Filter(MPU6050_t *results) {
	float pitch_tmp = results->gyro_pitch * (1-ALPHA) + results->accel_pitch * ALPHA;
	results->accel_pitch = pitch_tmp;
	results->gyro_pitch = pitch_tmp;

	float roll_tmp = results->gyro_roll * (1-ALPHA) + results->accel_roll * ALPHA;
	results->accel_roll = roll_tmp;
	results->gyro_roll = roll_tmp;
}
