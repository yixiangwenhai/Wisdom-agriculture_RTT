/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-09     86181       the first version
 */
#include "sensor.h"
#include "stdlib.h"
#include <main.h>

int eco21;
int tvoc1;


 static void app_sgp30_thread_entry(void)
{

     rt_device_t dev1 = RT_NULL;
     struct rt_sensor_data data1;
     rt_size_t res1;
     rt_device_t dev2 = RT_NULL;
     struct rt_sensor_data data2;
     rt_size_t res2;
    /* 查找系统中的传感器设备 */
    dev1 = rt_device_find("eco2_sg3");
    if (dev1 == RT_NULL)
    {
        rt_kprintf("Can't find device:eco2_sg3\n");
        return;
    }
    /* 查找系统中的传感器设备 */
    dev2 = rt_device_find("tvoc_sg3");
    if (dev2 == RT_NULL)
    {
        rt_kprintf("Can't find device:tvoc_sg3\n");
        return;
    }

    /* 以轮询模式打开传感器设备*/
    if (rt_device_open(dev1, RT_DEVICE_FLAG_RDONLY) != RT_EOK)
    {
        rt_kprintf("open device failed!");
        return;
    }
    /* 以轮询模式打开传感器设备*/
    if (rt_device_open(dev2, RT_DEVICE_FLAG_RDONLY) != RT_EOK)
    {
        rt_kprintf("open device failed!");
        return;
    }

    while(1)
    {
        /* 从传感器读取一个数据 */
    res1 = rt_device_read(dev1, 0, &data1, 1);
    res2 = rt_device_read(dev2, 0, &data2, 1);
    if (res1 != 1&& res2 != 1)
    {
        rt_kprintf("read data failed!size is %d", res1);
        rt_kprintf("read data failed!size is %d", res2);
    }
    else
    {
        itoa((&data1)->data.eco2,eco2,10);
        itoa((&data2)->data.tvoc,tvoc,10);
        eco21 = (&data1)->data.eco2;
        tvoc1 = (&data2)->data.tvoc;
       //rt_kprintf("eco2:%5d \n", (&data1)->data.eco2);
       //rt_kprintf("tvoc:%5d  \n", (&data2)->data.tvoc);
       //rt_kprintf("eco2:%d",eco21);
       //rt_kprintf("tvoc:%d",tvoc1);
    }
    rt_thread_mdelay(1000);
    }
    /* 关闭传感器设备 */
    rt_device_close(dev1);
    rt_device_close(dev2);
}
