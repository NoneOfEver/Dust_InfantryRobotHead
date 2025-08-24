#include "bsp_usb.h"
#include "pc_comm.h"
#include "cmsis_os2.h"

void Class_PC_Comm::Init()
{

}

void Class_PC_Comm::Send_Message()
{
    uint8_t buffer[16];
    memcpy(buffer, &PC_Send_Data, sizeof(Struct_PC_Send_Data));
    USB_Transmit(buffer,16);
}

void Class_PC_Comm::RxCpltCallback()
{
    if (PC_Recv_Data.Start_Of_Frame == bsp_usb_rx_buffer[0]){
        memcpy(PC_Recv_Data.Yaw,&bsp_usb_rx_buffer[1],4);
        memcpy(PC_Recv_Data.Pitch,&bsp_usb_rx_buffer[5],4);
        PC_Recv_Data.Fire       = bsp_usb_rx_buffer[9];
        PC_Recv_Data.CRC16[0]   = bsp_usb_rx_buffer[10];
        PC_Recv_Data.CRC16[1]   = bsp_usb_rx_buffer[11];
    }
}
