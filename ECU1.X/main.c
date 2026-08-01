/*
 * File:   main.c
 *
 * Created on July 2, 2026, 09:09 AM
 */

#include <xc.h>
#include "adc.h"
#include "can.h"
#include "ecu1_sensor.h"
#include "msg_id.h"
#include "uart.h"

#define _XTAL_FREQ 200000000

void main(void)
{
    /* Initialize digital keypad */
    init_digital_keypad();

    /* Initialize ADC module */
    init_adc();

    /* Initialize UART module */
    init_uart();

    /* Initialize CAN module */
    init_can();

    /* Array to store speed digits */
    unsigned char str[3];

    /* Gear position strings */
    unsigned char *arr[9] = {"N ","1 ","2 ","3 ","4 ","5 ","R ","C "};

    while(1)
    {
        /* Read current vehicle speed */
        uint16_t speed = get_speed();

        /* Read current gear position */
        unsigned char gear = get_gear_pos();

        /* Convert speed into ASCII characters */
        str[0] = ((speed / 10) + '0');
        str[1] = ((speed % 10) + '0');

        /* Transmit speed over CAN */
        can_transmit(SPEED_MSG_ID, str, 2);
        __delay_us(1000);

        /* Transmit gear position over CAN */
        can_transmit(GEAR_MSG_ID, arr[gear], 2);
        __delay_us(1000);
    }

    return;
}