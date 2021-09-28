#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <math.h>
#include <stdint.h>
#include <main.h>

#ifndef SIMULATOR


int i = 0;


extern "C"
{
#include <rtdevice.h>
#include "drv_common.h"
}


#define PG7 GET_PIN(C, 5)
#define PH8 GET_PIN(H, 8)
#define PH10 GET_PIN(H, 10)
#endif


Model::Model() : modelListener(0)
{

}

void Model::tick()
{
    uint32_t sum1=0,sum2=0,sum3=0,sum4=0,sum5=0;
        sum1 = light1;
        sum2 = eco21;
        sum3 = tvoc1;
        sum4 = hum1;
        sum5 = temp1;




       /* for(i=0;i<6;i++)
        {
           // sum1 =sum1+light[i]*pow(10,i);
           // sum2 = 1212;
           sum2 = eco2[i]*pow(10,i);
            sum3 = tvoc[i]*pow(10,i);
            sum4 = hum[i]*pow(10,i);
            sum5 = temp[i]*pow(10,i);*/

        //rt_thread_mdelay(5000);
       // rt_kprintf("sum1 = %d\n",sum1);
        modelListener->shuju(sum1,sum2,sum3,sum4,sum5);
}

void Model::led()
{
    #ifndef SIMULATOR
        static int status = PIN_LOW;

        if(status == PIN_LOW)
        {
            status = PIN_HIGH;
        }
        else{status = PIN_LOW;}

        rt_pin_write(PG7,status);

        rt_kprintf("click");
    #endif
}

void Model::jsq()
{
    #ifndef SIMULATOR
        static int status1 = PIN_HIGH;

        if(status1 == PIN_HIGH)
        {
            status1 = PIN_LOW;
        }
        else{status1 = PIN_HIGH;}

        rt_pin_write(PH8,status1);

        rt_kprintf("jiashiqi");
    #endif
}

void Model::fs()
{
    #ifndef SIMULATOR
        static int status2 = PIN_HIGH;

        if(status2 == PIN_HIGH)
        {
            status2 = PIN_LOW;
        }
        else{status2 = PIN_HIGH;}

        rt_pin_write(PH10,status2);

        rt_kprintf("fenshan");
    #endif
}
