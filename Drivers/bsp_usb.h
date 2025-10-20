#ifndef BSP_USB_H
#define BSP_USB_H
#ifdef __cplusplus
extern "C"{
#endif
#include "usb_device.h"
#include "usbd_cdc.h"
#include "usbd_conf.h"
#include "usbd_desc.h"
#include "usbd_cdc_if.h"

extern uint8_t *bsp_usb_rx_buffer; // 接收到的数据会被放在这里,buffer size为2048
extern uint8_t *send_buffer;

/* @note 虚拟串口的波特率/校验位/数据位等动态可变,取决于上位机的设定 */
/* 使用时不需要关心这些设置(作为从机) */
void USB_Init(USBCallback tx_cbk,USBCallback rx_cbk);

void USB_Transmit(uint8_t *buffer, uint16_t len); // 通过usb发送数据
void USB_Refresh(); // 重新枚举USB设备

#ifdef __cplusplus
}
#endif
#endif



