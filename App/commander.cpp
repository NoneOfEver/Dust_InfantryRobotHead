#include "booster.h"
#include "comm.h"

#include "bsp_usb.h"
#include "cmsis_os2.h"
#include "drv_can.h"
#include "bsp_usart.h"
#include "VT03.h"

#include "commander.h"

void Class_Commander::Init()
{
    // 图传接收机初始化
    VT03.Init(&huart1);
    // 与下板通讯服务初始化
    MCU_Comm.Init(&hfdcan2,0x00,0x01);
    // 发射机构初始化
    Booster.Init();

    static const osThreadAttr_t CommanderTaskAttr = {
        .name = "CommanderTask",
        .stack_size = 512,
        .priority = (osPriority_t) osPriorityNormal
    };
    // 启动任务，将 this 传入
    osThreadNew(Class_Commander::TaskEntry, this, &CommanderTaskAttr);
}
// 任务入口（静态函数）—— osThreadNew 需要这个原型
void Class_Commander::TaskEntry(void *argument)
{
    Class_Commander *self = static_cast<Class_Commander *>(argument);  // 还原 this 指针
    self->Task();  // 调用成员函数
}

void Class_Commander::Task()
{
    for (;;)
    {
        // parse_parameter(USB_RxBuf);

        // 左侧自定义按键逻辑
        if (VT03.Data.Left_Key == VT03_Key_Status_TRIG_PRESSED_FREE){
            if (Booster.Get_Switch_Statue() == 1){
                Booster.Set_Switch_Statue(0);
            }else if(Booster.Get_Switch_Statue() == 0){
                Booster.Set_Switch_Statue(1);
            }
        }
        //遥控器扳机键逻辑
        if (VT03.Data.Right_Key == VT03_Key_Status_PRESSED){
            Booster.Set_Reverse_Statue(1);
        }else if (VT03.Data.Right_Key == VT03_Key_Status_FREE){
            Booster.Set_Reverse_Statue(0);
        }
        if (VT03.Data.Trigger == VT03_Key_Status_PRESSED){
            Booster.Set_Shoot_Statue(1);
        }else if (VT03.Data.Trigger == VT03_Key_Status_FREE){
            Booster.Set_Shoot_Statue(0);
        }

        MCU_Comm.CAN_Send_Command();

        osDelay(10);
    }
}

