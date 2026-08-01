#include <xc.h>
#include "ecu_sensor.h"
#include "adc.h"
#include "can.h"
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

    /* Array to store RPM in ASCII format */
    unsigned char str[5];

    /* Variable to store indicator status */
    unsigned char indicator;

    while (1)
    {
        /* Read current engine RPM */
        uint16_t rpm = get_rpm();

        /* Read current indicator status */
        indicator = process_indicator();

        /* Convert RPM into ASCII characters */
        str[0] = ((rpm / 1000) % 10) + '0';
        str[1] = ((rpm / 100) % 10) + '0';
        str[2] = ((rpm / 10) % 10) + '0';
        str[3] = (rpm % 10) + '0';
        str[4] = '\0';

        /* Transmit RPM over CAN */
        can_transmit(RPM_MSG_ID, str, 4);
        __delay_us(1000);

        /* Transmit indicator status over CAN */
        can_transmit(INDICATOR_MSG_ID, &indicator, 1);
        __delay_us(1000);
    }

    return;
}