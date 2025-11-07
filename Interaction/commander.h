//
// Created by noe on 25-8-15.
//

#ifndef COMMANDER_H
#define COMMANDER_H

#include "FreeRTOS.h"
// app
#include "booster.h"
// module
#include "mcu_comm.h"
#include "pc_comm.h"
#include "VT03.h"
#include "IMU.hpp"

class Class_Commander
{
public:
    // IMU
    Imu imu_;
    // 与下板通讯服务
    Class_MCU_Comm MCU_Comm;
    // 与接收机通讯服务
    Class_VT03 VT03;
    // 与上位机通讯
    Class_PC_Comm PC_Comm;
    // 发射机构
    Class_Booster Booster;

    /**
     * @brief 控制台初始化
     */
    void Init();

    /**
     * @brief 控制台上层调度任务
     */
    void Task();

private:
    static void TaskEntry(void *param);
};


#endif //COMMANDER_H
