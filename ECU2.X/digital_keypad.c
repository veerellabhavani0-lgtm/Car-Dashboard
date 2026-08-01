#include <xc.h>
#include "digital_keypad.h"

/* Initialize digital keypad */
void init_digital_keypad(void)
{
    /* Configure keypad pins as input */
    TRISC = TRISC | INPUT_PINS;
}

/* Read keypad input */
unsigned char read_digital_keypad(unsigned char detection_type)
{
    /* Flag for state change detection */
    static unsigned char once = 1;

    /* Check for state change mode */
    if (detection_type == STATE_CHANGE)
    {
        /* Key is pressed for the first time */
        if (((KEY_PORT & INPUT_PINS) != ALL_RELEASED) && once)
        {
            once = 0;

            /* Return pressed key */
            return (KEY_PORT & INPUT_PINS);
        }
        /* Reset flag after key release */
        else if ((KEY_PORT & INPUT_PINS) == ALL_RELEASED)
        {
            once = 1;
        }
    }
    /* Check for level detection mode */
    else if (detection_type == LEVEL)
    {
        /* Return current key status */
        return (KEY_PORT & INPUT_PINS);
    }

    /* No key pressed */
    return 0xFF;
}