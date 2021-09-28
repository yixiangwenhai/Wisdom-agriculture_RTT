/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-16     86181       the first version
 */

#include <sht3x.h>
#include <main.h>

int hum1;
int temp1;

/* Èë¿Úº¯Êý */
static void sht30_emqx_entry(void *parameter)
{
    sht3x_device_t  sht3x_device;

    sht3x_device = sht3x_init("i2c3", 0x44);

    rt_thread_mdelay(150);

    while (1)
    {
        if(RT_EOK == sht3x_read_singleshot(sht3x_device))
        {
            itoa(sht3x_device->humidity*10,hum,10);
            itoa(sht3x_device->temperature,temp,10);

            hum1 = (sht3x_device->humidity)*100;
            temp1 = (sht3x_device->temperature)*10;
           // rt_kprintf("hum1 = %d\n",hum1);
           // rt_kprintf("temp1 = %d\n",temp1);
            //rt_thread_mdelay(1000);
        }
        else
        {
            rt_kprintf("read sht3x fail.\r\n");
            break;
        }
        rt_thread_mdelay(100);
    }
}
