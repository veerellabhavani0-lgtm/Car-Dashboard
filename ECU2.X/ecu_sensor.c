#include "ecu_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"

/* Function to read engine RPM */
uint16_t get_rpm(void)
{
    uint16_t rpm;

    /* Read ADC value from RPM sensor */
    rpm = read_adc(RPM_ADC_CHANNEL);

    /* Convert ADC value to RPM */
    rpm = (uint16_t)(rpm / 0.1705);

    /* Return calculated RPM */
    return rpm;
}

/* Function to process indicator switch input */
IndicatorStatus process_indicator(void)
{
    /* Read keypad using state change detection */
    unsigned char key = read_digital_keypad(STATE_CHANGE);

    /* Store current indicator status */
    static IndicatorStatus flag = 3;

    /* SWITCH1 -> Left Indicator */
    if (key == SWITCH1)
    {
        flag = 0;
    }
    /* SWITCH2 -> Right Indicator */
    else if (key == SWITCH2)
    {
        flag = 1;
    }
    /* SWITCH3 -> Hazard Indicator */
    else if (key == SWITCH3)
    {
        flag = 2;
    }
    /* SWITCH4 -> Indicator OFF */
    else if (key == SWITCH4)
    {
        flag = 3;
    }

    /* Return current indicator status */
    return flag;
}