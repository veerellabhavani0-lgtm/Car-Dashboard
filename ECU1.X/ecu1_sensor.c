/*
 * File:   ecu1_sensor.c
 * Author: DELL
 *
 * Created on July 2, 2026, 8:34 AM
 */

#include "ecu1_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"

/* Function to read vehicle speed from ADC */
uint16_t get_speed(void)
{
    uint16_t val;

    /* Read ADC value from speed sensor channel */
    val = read_adc(SPEED_ADC_CHANNEL);

    /* Convert ADC value (0-1023) to speed (0-99) */
    val = val / 10.26;

    /* Return calculated speed */
    return val;
}

/* Function to detect current gear position */
unsigned char get_gear_pos(void)
{
    /* Store gear position even after function returns */
    static char gear = 0;

    /* Read keypad using state change detection */
    unsigned char key = read_digital_keypad(STATE_CHANGE);

    /* SWITCH1 -> Shift gear up */
    if (key == SWITCH1)
    {
        /* Exit collision state if active */
        if (gear == 7)
        {
            gear = 0;
        }
        /* Increase gear up to Gear 6 */
        else if (gear < 6)
        {
            gear++;
        }
    }
    /* SWITCH2 -> Shift gear down */
    else if (key == SWITCH2)
    {
        /* Exit collision state if active */
        if (gear == 7)
        {
            gear = 0;
        }
        /* Decrease gear down to Gear 0 */
        else if (gear > 0)
        {
            gear--;
        }
    }
    /* SWITCH3 -> Enter collision state */
    else if (key == SWITCH3)
    {
        gear = 7;
    }

    /* Return current gear position */
    return gear;
}