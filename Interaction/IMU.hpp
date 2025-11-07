#ifndef IMU_HPP_
#define IMU_HPP_

#include "INS_Task.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"

class Imu
{
public:
    void Init(){
        
        static const osThreadAttr_t ImuTaskAttr = {
            .name = "ImuTask",
            .stack_size = 512,
            .priority = (osPriority_t) osPriorityNormal
        };
        osThreadNew(TaskEntry, this, &ImuTaskAttr);
    }
    
    void Task(){
        INS_Task();
    }
private:
    static void TaskEntry(void *param){
        Imu *self = static_cast<Imu *>(param);
        self->Task();
    }
};

#endif