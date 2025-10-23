//
// Created by noe on 25-8-15.
//

#include "bsp_usb.h"
#include "bsp_usart.h"
#include "commander.h"
#include <cstdint>
#include <sys/types.h>

#include "Init.h"

// global variable
uint8_t* USB_RxBuf;
uint8_t usb_tx_cmplt_flag = 0;

Class_Commander Commander;

/**
 * @brief CAN1回调函数
 *
 * @param CAN_RxMessage CAN1收到的消息
 */
void Device_CAN1_Callback(Struct_CAN_Rx_Buffer *CAN_RxMessage)
{
    switch (CAN_RxMessage->Header.Identifier)
    {
        case (0x201):
        {
            Commander.Booster.Motor_Booster_3.CAN_RxCpltCallback(CAN_RxMessage->Data);
            break;
        }
        case (0x202):
        {
            Commander.Booster.Motor_Booster_1.CAN_RxCpltCallback(CAN_RxMessage->Data);
            break;
        }
        case (0x203):
        {
            Commander.Booster.Motor_Booster_2.CAN_RxCpltCallback(CAN_RxMessage->Data);
            break;
        }
    }
}

/**
 * @brief CAN2回调函数
 *
 * @param CAN_RxMessage CAN2收到的消息
 */
void Device_CAN2_Callback(Struct_CAN_Rx_Buffer *CAN_RxMessage)
{
    switch (CAN_RxMessage->Header.Identifier)
    {
    case (0x00):
        {
            Commander.MCU_Comm.CAN_RxCpltCallback(CAN_RxMessage->Data);
            break;
        }
    }
}

void VT03_UART1_Callback(uint8_t *Buffer, uint16_t Length)
{
    Commander.VT03.UART_RxCpltCallback(Buffer,Length);
    Commander.MCU_Comm.MCU_Comm_Data.Start_Of_Frame       = 0xAB;
    Commander.MCU_Comm.MCU_Comm_Data.Yaw_Angle            = (uint8_t)(Commander.VT03.Data.Right_X*255);
    Commander.MCU_Comm.MCU_Comm_Data.Pitch_Angle          = (uint8_t)(Commander.VT03.Data.Right_Y*255);
    Commander.MCU_Comm.MCU_Comm_Data.Chassis_Speed_X      = (uint8_t)(Commander.VT03.Data.Left_X*255);
    Commander.MCU_Comm.MCU_Comm_Data.Chassis_Speed_Y      = (uint8_t)(Commander.VT03.Data.Left_Y*255);
    Commander.MCU_Comm.MCU_Comm_Data.Chassis_Rotation     = (uint8_t)(Commander.VT03.Data.Wheel*255);
    Commander.MCU_Comm.MCU_Comm_Data.Chassis_Spin         = (uint8_t)(Commander.VT03.Data.Mode_Switch);
    Commander.MCU_Comm.MCU_Comm_Data.Supercap             = (uint8_t)(Commander.VT03.Data.Pause);
}

/**
 * @bief USB接收完成回调函数
 *
 * @param len 接收到的数据长度
 */
void usb_rx_callback(uint16_t len)
{
    Commander.PC_Comm.RxCpltCallback();
}

/**
 * @bief USB发送完成回调函数
 *
 * @param len 发送的数据长度
 */
void usb_tx_callback(uint16_t len)
{

}

void Init()
{
    osDelay(10000);
    // USB初始化
    USB_Init(usb_tx_callback,usb_rx_callback);
    // UART1 初始化，新图传通讯
    UART_Init(&huart1,VT03_UART1_Callback,512);
    // CAN1 初始化，控制发射
    CAN_Init(&hfdcan1,Device_CAN1_Callback);
    // CAN2 初始化，与下板通讯
    CAN_Init(&hfdcan2,Device_CAN2_Callback);

    Commander.Init();
}
