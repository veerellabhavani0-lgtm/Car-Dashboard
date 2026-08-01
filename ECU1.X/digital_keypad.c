#include <xc.h>
#include "digital_keypad.h"

/* Function to initialize digital keypad pins */
void init_digital_keypad(void)
{
	/* Configure keypad pins as input */
	TRISC = TRISC | INPUT_PINS;
}

/* Function to read keypad based on detection type */
unsigned char read_digital_keypad(unsigned char detection_type)
{
	/* Variable to detect key press only once */
	static unsigned char once = 1;

	/* State change detection */
	if (detection_type == STATE_CHANGE)
	{
		/* Return key only once when pressed */
		if (((KEY_PORT & INPUT_PINS) != ALL_RELEASED) && once)
		{
			once = 0;

			return (KEY_PORT & INPUT_PINS);
		}
		/* Reset flag when all keys are released */
		else if ((KEY_PORT & INPUT_PINS) == ALL_RELEASED)
		{
			once = 1;
		}
	}
	/* Level detection */
	else if (detection_type == LEVEL)
	{
		/* Return current key status continuously */
		return (KEY_PORT & INPUT_PINS);
	}

	/* No key pressed */
	return 0xFF;
}