#ifndef IMU_H_
#define IMU_H_

#include "BMI088driver.h"
#include "spi.h"
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "imu_temp_ctrl.h"


class Imu {
private:
    // FreeRTOS 入口，静态函数
    static void TaskEntry(void *argument)
    {
        Imu *self = static_cast<Imu *>(argument);  // 还原 this 指针
        self->Task();  // 调用成员函数
    }
public:
    void Task()
    {
        IMU_task();
    }
    void Init()
    {
        INS_Init();
        static const osThreadAttr_t ImuTaskAttr = {
            .name = "ImuTask",
            .stack_size = 4096,
            .priority = (osPriority_t) osPriorityNormal
        };
        // 启动任务，将 this 传入
        osThreadNew(TaskEntry, this, &ImuTaskAttr);
    }
};

#endif /* IMU_H_ */