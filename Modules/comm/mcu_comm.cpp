#include "mcu_comm.h"
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

void Class_MCU_Comm::CAN_Send_AutoAim()
{
     static uint8_t CAN_Tx_Frame[8];
     CAN_Tx_Frame[0] = MCU_AutoAim_Data.Start_Of_Yaw_Frame;
     CAN_Tx_Frame[1] = MCU_AutoAim_Data.Yaw[0];
     CAN_Tx_Frame[2] = MCU_AutoAim_Data.Yaw[1];
     CAN_Tx_Frame[3] = MCU_AutoAim_Data.Yaw[2];
     CAN_Tx_Frame[4] = MCU_AutoAim_Data.Yaw[3];
     CAN_Send_Data(CAN_Manage_Object->CAN_Handler, CAN_Tx_ID, CAN_Tx_Frame, 8);

     CAN_Tx_Frame[0] = MCU_AutoAim_Data.Start_Of_Pitch_Frame;
     CAN_Tx_Frame[1] = MCU_AutoAim_Data.Pitch[0];
     CAN_Tx_Frame[2] = MCU_AutoAim_Data.Pitch[1];
     CAN_Tx_Frame[3] = MCU_AutoAim_Data.Pitch[2];
     CAN_Tx_Frame[4] = MCU_AutoAim_Data.Pitch[3];
     CAN_Send_Data(CAN_Manage_Object->CAN_Handler, CAN_Tx_ID, CAN_Tx_Frame, 8);
}

void Class_MCU_Comm::Data_Process()
{

}

void Class_MCU_Comm::CAN_RxCpltCallback(uint8_t* Rx_Data)
{
     // 判断在线

     // 处理数据
     union { float f; uint8_t b[4]; } conv;

     // 判断是哪一帧
     if (Rx_Data[4] == 0xBA)   // ---- 第二帧 (Pitch)
     {
          memcpy(MCU_Recv_Data.Pitch, Rx_Data, 4 * sizeof(uint8_t));
     }
     else if ((Rx_Data[0] == 0xAB)&&((Rx_Data[1] == 0x00)||(Rx_Data[1] == 0x01)))                     // ---- 第一帧 (Yaw)
     {
          MCU_Recv_Data.Start_Of_Frame = Rx_Data[0];
          MCU_Recv_Data.Armor = Rx_Data[1];

          memcpy(MCU_Recv_Data.Yaw, &Rx_Data[2], 4 * sizeof(uint8_t));
     }
}
