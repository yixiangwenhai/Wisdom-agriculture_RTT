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

int light1;

 static void app_bh1750_thread_entry(void)
{
    rt_device_t dev = RT_NULL;
    struct rt_sensor_data data;
    rt_size_t res;

    /* ����ϵͳ�еĴ������豸 */
    dev = rt_device_find("li_bh1750");
    if (dev == RT_NULL)
    {
        rt_kprintf("Can't find device:li_bh1750\n");
        return;
    }

    /* ����ѯģʽ�򿪴������豸*/
    if (rt_device_open(dev, RT_DEVICE_FLAG_RDONLY) != RT_EOK)
    {
        rt_kprintf("open device failed!");
        return;
    }

        while(1)
        {
      /* �Ӵ�������ȡһ������ */
        res = rt_device_read(dev, 0, &data, 1);
        if (res != 1)
        {
            rt_kprintf("read data failed!size is %d", res);
        }
        else
        {
            //paho_mqtt_publish(&client, QOS1, MQTT_PUBTOPIC,itoa((&data)->data.light,i,10) );
            //rt_thread_mdelay(1000);
            itoa((&data)->data.light,light,10);
            //rt_kprintf("light:%4d lux  \n", (&data)->data.light / 10);
            //rt_thread_mdelay(1000);

            //rt_kprintf("light:%4d.%d lux  \n", (&data)->data.light / 10, (&data)->data.light % 10);
            light1 =  ((&data)->data.light);
            rt_kprintf("light1=%d\n",light1);
        }

        rt_thread_mdelay(1000);
        }

    /* �رմ������豸 */
    rt_device_close(dev);
}
