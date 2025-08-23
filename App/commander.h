//
// Created by noe on 25-8-15.
//

#ifndef COMMANDER_H
#define COMMANDER_H

#include "FreeRTOS.h"
// app
#include "booster.h"
// module
#include "comm.h"
#include "VT03.h"

class Class_Commander
{
public:
    // 与下板通讯服务
    Class_MCU_Comm MCU_Comm;
    // 与接收机通讯服务
    Class_VT03 VT03;
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
    // FreeRTOS 入口，静态函数
    static void TaskEntry(void *param);
};

#endif //COMMANDER_H
