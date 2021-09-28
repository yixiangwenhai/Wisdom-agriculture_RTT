/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-02     RT-Thread    first version
 */

#include <rtthread.h>
#include <app_bh1750.c>
#include <app_sgp30.c>
#include <app_sht30.c>
#include "sensor.h"
#include <app_mqtt.c>
#include "drv_common.h"
#include <rtdevice.h>

extern void wlan_autoconnect_init(void);

int main(void)
{
    wlan_autoconnect_init();
    rt_wlan_config_autoreconnect(RT_TRUE);
    rt_pin_mode(PG7, PIN_MODE_OUTPUT);
    rt_pin_mode(PH8, PIN_MODE_OUTPUT);
    rt_pin_mode(PH10, PIN_MODE_OUTPUT);
    rt_pin_write(PG7, PIN_LOW);
    rt_pin_write(PH8, PIN_HIGH);
    rt_pin_write(PH10, PIN_HIGH);
    /* 栈空间地址对齐 */
    ALIGN( RT_ALIGN_SIZE )
    /* 定义一个数组，栈的空间大小就是1024*8字节 */
    static rt_uint8_t rt_bh1750_thread_stack[1024];
    static rt_uint8_t rt_sgp30_thread_stack[1024];

    static struct rt_thread bh1750_thread; //定义线程控制块
    static struct rt_thread sgp30_thread; //定义线程控制块

    rt_thread_init(&bh1750_thread, /* 线程控制块 */
                    "bh1750", /* 线程名字 */
                    app_bh1750_thread_entry, /* 线程入口函数 */
                    RT_NULL, /* 线程入口函数参数 */
                    &rt_bh1750_thread_stack[0], /* 线程栈起始地址 */
                    sizeof(rt_bh1750_thread_stack), /* 线程栈大小 */
                    1, /* 线程的优先级 */
                    20); /* 线程时间片 */
     rt_thread_startup(&bh1750_thread);

     rt_thread_init(&sgp30_thread, /* 线程控制块 */
                     "sgp30", /* 线程名字 */
                     app_sgp30_thread_entry, /* 线程入口函数 */
                     RT_NULL, /* 线程入口函数参数 */
                     &rt_sgp30_thread_stack[0], /* 线程栈起始地址 */
                     sizeof(rt_sgp30_thread_stack), /* 线程栈大小 */
                     2, /* 线程的优先级 */
                     20); /* 线程时间片 */
     rt_thread_startup(&sgp30_thread);

     rt_thread_t tid;    //线程句柄

     tid = rt_thread_create("mqtt_emqx",
                             mqtt_emqx_entry,
                             RT_NULL,
                             512,
                             3,
                             20);
     if(tid != RT_NULL)
        {
            //线程创建成功，启动线程
            rt_thread_startup(tid);
         }

     rt_thread_t tid1;

     tid1 = rt_thread_create("sht30_emqx",
                             sht30_emqx_entry,
                             RT_NULL,
                             1024,
                             4,
                             20);
     if(tid1 != RT_NULL)
        {

            rt_thread_startup(tid1);
         }

}

#include "stm32h7xx.h"
static int vtor_config(void)
{
    /* Vector Table Relocation in Internal QSPI_FLASH */
    SCB->VTOR = QSPI_BASE;
    return 0;
}
INIT_BOARD_EXPORT(vtor_config);


