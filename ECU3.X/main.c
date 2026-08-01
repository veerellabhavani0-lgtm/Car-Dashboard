#include <xc.h>
#include <stdint.h>
#include "can.h"
#include "clcd.h"
#include "msg_id.h"
#include "message_handler.h"
//#include "timer0.h"

static void  init_leds(void)
{
    TRISB = 0x08;      // RB2 = TX, RB3 = RX
    PORTB = 0x00;
}

static void init_config(void)
{
    init_clcd();
    init_can();
    init_leds();

    PEIE = 1;
    GIE = 1;
    //init_timer0();
}

void main(void)
{
    unsigned long int delay = 0;
    init_config();
    //init_uart();
    while(1)
    {
        process_canbus_data();
        clcd_print("SP",LINE1(0));
        clcd_print("G",LINE1(3));
        clcd_print("RPM",LINE1(6));
        clcd_print("IND",LINE1(11));
        if(delay++ ==1000){
            delay = 0;
        indicator_blink();
        }
    }
    
    
    return;
}