#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"

/* LED and indicator status variables */
volatile unsigned char led_state = LED_OFF, status = e_ind_off;
unsigned char ind = 3;

/* Indicator display strings */
const unsigned char *ind_arr[4] =
{
    (const unsigned char *)"<-- ",
    (const unsigned char *)"--> ",
    (const unsigned char *)"<-> ",
    (const unsigned char *)"OFF "
};

/* Function to handle speed data received over CAN */
void handle_speed_data(uint8_t *data, uint8_t len)
{
    /* Append string terminator */
    data[len] = '\0';

    /* Display speed on CLCD */
    clcd_print(data, LINE2(0));
}

/* Function to handle gear data received over CAN */
void handle_gear_data(uint8_t *data, uint8_t len)
{
    /* Append string terminator */
    data[len] = '\0';

    /* Display gear on CLCD */
    clcd_print(data, LINE2(3));
}

/* Function to handle RPM data received over CAN */
void handle_rpm_data(uint8_t *data, uint8_t len)
{
    /* Append string terminator */
    data[len] = '\0';

    /* Display RPM on CLCD */
    clcd_print(data, LINE2(6));
}

/*
void handle_engine_temp_data(uint8_t *data, uint8_t len)
{
    // Implement the temperature function
}
*/

/* Function to handle indicator data received over CAN */
void handle_indicator_data(uint8_t *data, uint8_t len)
{
    /* len is unused */
    (void)len;

    /* Store received indicator status */
    ind = data[0];

    /* Display indicator status on CLCD */
    if (ind < 4)
    {
        clcd_print(ind_arr[ind], LINE2(11));
    }
}

/* Function to blink indicator LEDs */
void indicator_blink()
{
    /* Toggle flag for blinking */
    static char flag = 0;

    /* Indicator OFF */
    if (ind == 3)
    {
        RIGHT_IND_OFF();
        LEFT_IND_OFF();
    }
    /* Left Indicator */
    else if (ind == 0)
    {
        if (flag == 0)
        {
            flag = 1;
            LEFT_IND_ON();
            RIGHT_IND_OFF();
        }
        else
        {
            flag = 0;
            LEFT_IND_OFF();
            RIGHT_IND_OFF();
        }
    }
    /* Right Indicator */
    else if (ind == 1)
    {
        if (flag == 0)
        {
            flag = 1;
            RIGHT_IND_ON();
            LEFT_IND_OFF();
        }
        else
        {
            flag = 0;
            RIGHT_IND_OFF();
            LEFT_IND_OFF();
        }
    }
    /* Hazard Indicator */
    else if (ind == 2)
    {
        if (flag == 0)
        {
            flag = 1;
            LEFT_IND_ON();
            RIGHT_IND_ON();
        }
        else
        {
            flag = 0;
            LEFT_IND_OFF();
            RIGHT_IND_OFF();
        }
    }
}

/* Function to receive and process CAN messages */
void process_canbus_data()
{
    uint16_t msg_id;
    uint8_t data[9];
    uint8_t len;

    /* Receive CAN message */
    can_receive(&msg_id, data, &len);

    /* Process received message */
    if (len != 0)
    {
        if (msg_id == SPEED_MSG_ID)
            handle_speed_data(data, len);

        if (msg_id == GEAR_MSG_ID)
            handle_gear_data(data, len);

        if (msg_id == RPM_MSG_ID)
            handle_rpm_data(data, len);

        if (msg_id == INDICATOR_MSG_ID)
            handle_indicator_data(data, len);
    }

    /* Clear message length */
    len = 0;
}