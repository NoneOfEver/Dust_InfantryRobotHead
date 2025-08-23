#include "comm.h"
#include "VT03.h"

void Class_MCU_Comm::Init(
     FDCAN_HandleTypeDef* hcan,
     uint8_t __CAN_Rx_ID,
     uint8_t __CAN_Tx_ID)
{
     if (hcan->Instance == FDCAN1)
     {
          CAN_Manage_Object = &CAN1_Manage_Object;
     }
     else if (hcan->Instance == FDCAN2)
     {
          CAN_Manage_Object = &CAN2_Manage_Object;
     }

     CAN_Rx_ID = __CAN_Rx_ID;
     CAN_Tx_ID = __CAN_Tx_ID;
}

void Class_MCU_Comm::CAN_Send_Command()
{
     static uint8_t CAN_Tx_Frame[8];
     CAN_Tx_Frame[0] = MCU_Comm_Data.Start_Of_Frame;
     CAN_Tx_Frame[1] = MCU_Comm_Data.Yaw_Angle;
     CAN_Tx_Frame[2] = MCU_Comm_Data.Pitch_Angle;
     CAN_Tx_Frame[3] = MCU_Comm_Data.Chassis_Speed_X;
     CAN_Tx_Frame[4] = MCU_Comm_Data.Chassis_Speed_Y;
     CAN_Tx_Frame[5] = MCU_Comm_Data.Chassis_Rotation;
     CAN_Tx_Frame[6] = MCU_Comm_Data.Chassis_Spin;
     CAN_Tx_Frame[7] = MCU_Comm_Data.Booster;

     CAN_Send_Data(CAN_Manage_Object->CAN_Handler, CAN_Tx_ID, CAN_Tx_Frame, 8);
}


void Class_MCU_Comm::Data_Process()
{

}

void Class_MCU_Comm::CAN_RxCpltCallback(uint8_t* Rx_Data)
{
     // 判断在线

     // 处理数据
     Data_Process();
}
