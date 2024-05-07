#include "MPU6050_2.h"

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

void MPU6050_Read_MPU(I2C_HandleTypeDef *I2Cx, MPU6050_t *DataStruct) {
    uint8_t Rec_Data[6];

    HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, GYRO_XOUT_H_R_GYRO_XOUT, 1, Rec_Data, 6, i2c_timeout);

    DataStruct->Gyro_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    DataStruct->Gyro_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    DataStruct->Gyro_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

    HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, ACCEL_XOUT_H_R_ACCEL_XOUT, 1, Rec_Data, 6, i2c_timeout);

    DataStruct->Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    DataStruct->Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    DataStruct->Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);
}

void MPU6050_Convert_Acc_Values(MPU6050_t *Raw_Values) {
	Raw_Values-> Accel_X = Raw_Values-> Accel_X_RAW*((2*G)/32768);
	Raw_Values-> Accel_Y = Raw_Values-> Accel_Y_RAW*((2*G)/32768);
	Raw_Values-> Accel_Z = Raw_Values-> Accel_Z_RAW*((2*G)/32768);
};

void MPU6050_Convert_Gyro_Values(MPU6050_t *Raw_Values) {
	Raw_Values-> Gyro_X = Raw_Values-> Gyro_X_RAW/131.0;
	Raw_Values-> Gyro_Y = Raw_Values-> Gyro_Y_RAW/131.0;
	Raw_Values-> Gyro_Z = Raw_Values-> Gyro_Z_RAW/131.0;
};

void MPU6050_Get_Acc_Angles(MPU6050_t *Raw_Values) {
	float pitch_tmp =  RAD_TO_DEG * asin(Raw_Values->Accel_X / G);
	Raw_Values->Accel_Pitch = Raw_Values->Accel_Pitch * (1 - ACCEL_LPF_ALPHA) + pitch_tmp * ACCEL_LPF_ALPHA;

    if (Raw_Values->Accel_Z != 0) {
    	float roll_tmp = RAD_TO_DEG * atan(Raw_Values->Accel_Y / Raw_Values->Accel_Z);
    	Raw_Values->Accel_Roll = Raw_Values->Accel_Roll * (1 - ACCEL_LPF_ALPHA) + roll_tmp * ACCEL_LPF_ALPHA;
    } else {
    	Raw_Values->Accel_Roll = 0.0;
    }
}



void MPU6050_Get_Gyro_Angles(MPU6050_t *Raw_Values, double Sample_Time) {
	float pitch_tmp = Raw_Values->Gyro_Pitch + Raw_Values->Gyro_Y*Sample_Time;
	Raw_Values->Gyro_Pitch = Raw_Values->Gyro_Pitch * (1 - GYRO_LPF_ALPHA) + pitch_tmp * GYRO_LPF_ALPHA;

	float roll_tmp = Raw_Values->Gyro_Roll + Raw_Values->Gyro_X*Sample_Time;
	Raw_Values->Gyro_Roll = Raw_Values->Gyro_Roll * (1 - GYRO_LPF_ALPHA) + roll_tmp * GYRO_LPF_ALPHA;
};

void MPU6050_Comp_Filter(MPU6050_t *Results) {
	float pitch_tmp = Results->Gyro_Pitch * COMPLEMENTARY_ALPHA + (1-COMPLEMENTARY_ALPHA) * Results->Accel_Pitch;
	Results->Accel_Pitch = pitch_tmp;
	Results->Gyro_Pitch = pitch_tmp;

	float roll_tmp = Results->Gyro_Roll * COMPLEMENTARY_ALPHA + (1-COMPLEMENTARY_ALPHA) * Results->Accel_Roll;
	Results->Accel_Roll = roll_tmp;
	Results->Gyro_Roll = roll_tmp;
}
