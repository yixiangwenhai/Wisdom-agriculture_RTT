/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-12     86181       the first version
 */
#ifndef APPLICATIONS_MAIN_H_
#define APPLICATIONS_MAIN_H_

extern char light[6];
extern char eco2[6];
extern char tvoc[6];
extern char hum[6];
extern char temp[6];

extern int light1;
extern int eco21;
extern int tvoc1;
extern int hum1;
extern int temp1;

#define PG7 GET_PIN(C, 5)
#define PH8 GET_PIN(H, 8)
#define PH10 GET_PIN(H, 10)

#endif /* APPLICATIONS_MAIN_H_ */
