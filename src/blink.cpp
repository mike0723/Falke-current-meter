#include "blink.h"

void setup_led (void)
{
    pinMode (PIN_LED, OUTPUT);
}

void blink (int num)
{
    for (int i = 0; i < num; i++)
    {
	digitalWrite (PIN_LED, LOW);
	delay (10);
	digitalWrite (PIN_LED, HIGH);
	delay (90);
    }
}

