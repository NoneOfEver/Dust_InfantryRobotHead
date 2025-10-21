#ifndef COMM_H
#define COMM_H
#include "drv_can.h"
#include <cstdint>

struct Struct_MCU_Comm_Data
{
    uint8_t Start_Of_Frame;     // 帧头
    uint8_t Yaw_Angle;          // 偏移角度
    uint8_t Pitch_Angle;        // 俯仰角度
    uint8_t Chassis_Speed_X;    // 平移方向：前、后、左、右
    uint8_t Chassis_Speed_Y;    // 底盘移动总速度
    uint8_t Chassis_Rotation;   // 自转：不转、顺时针转、逆时针转
    uint8_t Chassis_Spin;       // 小陀螺：不转、顺时针转、逆时针转
    uint8_t Supercap;           // 超级电容：充电、放电
};

struct Struct_MCU_Recv_Data
{
    uint8_t Start_Of_Frame;
    uint8_t Armor;
    uint8_t Yaw[4];
    uint8_t Pitch[4];
};

struct Struct_MCU_AutoAim_Data
{
    uint8_t Start_Of_Yaw_Frame;
    uint8_t Start_Of_Pitch_Frame;
    uint8_t Yaw[4];
    uint8_t Pitch[4];
};

struct McuImuData
{
    uint8_t start_of_yaw_frame;
    uint8_t start_of_pitch_frame;
    uint8_t yaw[4];
    uint8_t pitch[4];
};

class Class_MCU_Comm
{
public:

    Struct_MCU_Comm_Data MCU_Comm_Data = {
    0xAB,
        127,
        127,
        127,
        127,
        127,
        1,
        1,
    };

    Struct_MCU_AutoAim_Data MCU_AutoAim_Data = {
        0xAC,
        0xAD,
        {0x00,0x00,0x00,0x00},
        {0x00,0x00,0x00,0x00},
    };

    McuImuData mcu_imu_data_ = {
        0xAE,
        0xAF,
        {0,0,0,0},
        {0,0,0,0},
    };

    Struct_MCU_Recv_Data MCU_Recv_Data = {
    0xAB,
        0x00,
        {0x00,0x00,0x00,0x00},
        {0x00,0x00,0x00,0x00},
    };

    void Init(FDCAN_HandleTypeDef *hcan,
              uint8_t __CAN_Rx_ID,
              uint8_t __CAN_Tx_ID
              );

    void CAN_RxCpltCallback(uint8_t *Rx_Data);

    void CAN_Send_Command();
    void CAN_Send_AutoAim();
    void CanSendImu();

protected:
    // 绑定的CAN
    Struct_CAN_Manage_Object *CAN_Manage_Object;
    // 收数据绑定的CAN ID, 与上位机驱动参数Master_ID保持一致
    uint16_t CAN_Rx_ID;
    // 发数据绑定的CAN ID, 是上位机驱动参数CAN_ID加上控制模式的偏移量
    uint16_t CAN_Tx_ID;
    // 发送缓冲区
    uint8_t Tx_Data[8];
    // 接收缓冲区
    uint8_t Rx_Data[8];
    // 内部函数
    void Data_Process();
};

#endif //COMM_H
