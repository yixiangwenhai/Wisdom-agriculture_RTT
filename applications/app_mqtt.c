/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-10     86181       the first version
 */
#include "paho_mqtt.h"
#include <main.h>
#include "drv_common.h"
#include <rtdevice.h>

char light[6];
char eco2[6];
char tvoc[6];
char hum[6];
char temp[6];

/* 设置代理信息 */
#define MQTT_URI                "tcp://121.5.7.228:1883"
#define MQTT_USERNAME           "123"
#define MQTT_PASSWORD           "456"
#define MQTT_SUBTOPIC           "a"
#define MQTT_PUBTOPIC_light     "light"
#define MQTT_PUBTOPIC_eco2      "eco2"
#define MQTT_PUBTOPIC_tvoc      "tvoc"
#define MQTT_PUBTOPIC_hum       "hum"
#define MQTT_PUBTOPIC_temp       "temp"
#define MQTT_WILLMSG            "Goodbye!"

static MQTTClient client;
static int is_started = 0;

static void mqtt_sub_callback(MQTTClient *c, MessageData *msg_data)
{
    *((char *)msg_data->message->payload + msg_data->message->payloadlen) = '\0';
    rt_kprintf("mqtt sub callback: %.*s %.*s\n",
               msg_data->topicName->lenstring.len,
               msg_data->topicName->lenstring.data,
               msg_data->message->payloadlen,
               (char *)msg_data->message->payload);
    if(strcmp("LED_HIGH",(char *)msg_data->message->payload) ==0)
    {
        rt_pin_write(PG7, PIN_HIGH);
        rt_kprintf("LED_HIGH\n");
    }
    else if(strcmp("LED_LOW",(char *)msg_data->message->payload)==0)
    {
        rt_pin_write(PG7, PIN_LOW);
        rt_kprintf("LED_LOW\n");
    }
    if(strcmp("FEN_LOW",(char *)msg_data->message->payload) ==0)
    {
        rt_pin_write(PH8, PIN_HIGH);
        rt_kprintf("FEN_LOW\n");
    }
    else if(strcmp("FEN_HIGH",(char *)msg_data->message->payload)==0)
    {
        rt_pin_write(PH8, PIN_LOW);
        rt_kprintf("FEN_HIGH\n");
    }
    if(strcmp("HUM_LOW",(char *)msg_data->message->payload) ==0)
    {
        rt_pin_write(PH10, PIN_HIGH);
        rt_kprintf("HUM_LOW\n");
    }
    else if(strcmp("HUM_HIGH",(char *)msg_data->message->payload)==0)
    {
        rt_pin_write(PH10, PIN_LOW);
        rt_kprintf("HUM_HIGH\n");
    }
}

static void mqtt_emqx_entry(void *parameter)
{
    MQTTPacket_connectData condata = MQTTPacket_connectData_initializer;
    static char cid[20] = { 0 };

    /* config MQTT context param*/
    client.isconnected = 0;
    client.uri = MQTT_URI;

    /* generate the random client ID */
    rt_snprintf(cid, sizeof(cid), "rtthread%d", rt_tick_get());
    /* config connect param */
    memcpy(&client.condata, &condata, sizeof(condata));
    client.condata.clientID.cstring = cid;
    client.condata.keepAliveInterval = 30;
    client.condata.cleansession = 1;
    client.condata.username.cstring = MQTT_USERNAME;
    client.condata.password.cstring = MQTT_PASSWORD;

    /* config MQTT will param. */
    client.condata.willFlag = 1;
    client.condata.will.qos = 1;
    client.condata.will.retained = 0;
    client.condata.will.topicName.cstring = MQTT_PUBTOPIC_light;
    client.condata.will.message.cstring = MQTT_WILLMSG;

    /* malloc buffer. */
    client.buf_size = client.readbuf_size = 1024;
    client.buf = rt_calloc(1, client.buf_size);
    client.readbuf = rt_calloc(1, client.readbuf_size);
    if (!(client.buf && client.readbuf))
    {
        rt_kprintf("no memory for MQTT client buffer!");
       return;
    }

    /* set subscribe table and event callback */
    client.messageHandlers[0].topicFilter = rt_strdup(MQTT_SUBTOPIC);
    client.messageHandlers[0].callback = mqtt_sub_callback;
    client.messageHandlers[0].qos = QOS1;

    paho_mqtt_start(&client);
    is_started = 1;

    while(1)
    {
        if (is_started == 0)
        {
            rt_kprintf("mqtt client is not connected.");
           return;
        }
        else
        {
           paho_mqtt_publish(&client, QOS1, MQTT_PUBTOPIC_light, light);
           rt_thread_mdelay(100);
           paho_mqtt_publish(&client, QOS1, MQTT_PUBTOPIC_eco2, eco2);
           rt_thread_mdelay(100);
           paho_mqtt_publish(&client, QOS1, MQTT_PUBTOPIC_tvoc, tvoc);
           rt_thread_mdelay(100);
           paho_mqtt_publish(&client, QOS1, MQTT_PUBTOPIC_hum, hum);
           rt_thread_mdelay(100);
           paho_mqtt_publish(&client, QOS1, MQTT_PUBTOPIC_temp, temp);
           rt_thread_mdelay(100);
        }
    }
}
