#include <avr/io.h>
#include <util/delay.h>

// Adjust delay to achieve a 5 Hz blink rate (100ms for ON, 100ms for OFF)
#define BLINK_DELAY_MS 100

int main(void)
{
    DDRD = 1 << DDD6 | 1 << DDD7;                    // Set D6, D7 as output for LEDs
    PORTD = 1 << PORTD2 | 1 << PORTD3 | 1 << PORTD4; // Set pull-up on D2, D3 & D4 for buttons
    while (1)
    {
        // Read the button states
        int button1 = PIND & (1 << PIND3);
        int button2 = PIND & (1 << PIND4);
        int button3 = PIND & (1 << PIND2);

        // Count how many buttons are pressed
        int buttonsPressed = (!button1) + (!button2) + (!button3);

        // Check the button press conditions
        if (buttonsPressed == 1)
        { // Only proceed if exactly one button is pressed
            if (!button1)
            {
                // Toggle LED connected to PD6 for Button1
                PORTD ^= (1 << PORTD6);
                _delay_ms(BLINK_DELAY_MS);
            }
            else if (!button2)
            {
                // Toggle LED connected to PD7 for Button2
                PORTD ^= (1 << PORTD7);
                _delay_ms(BLINK_DELAY_MS);
            }
            else if (!button3)
            {
                // Toggle both LEDs for Button3
                PORTD ^= (1 << PORTD6) | (1 << PORTD7);
                _delay_ms(BLINK_DELAY_MS);
            }
        }
        else
        {
            // Turn off both LEDs if more than one button is pressed or no button is pressed
            PORTD &= ~((1 << PORTD6) | (1 << PORTD7));
        }

        // If no button is pressed, this block is redundant, included for clarity.
        // When buttonsPressed is not 1, it ensures LEDs are off, avoiding a static on state from the last loop iteration.
        if (buttonsPressed != 1)
        {
            PORTD &= ~((1 << PORTD6) | (1 << PORTD7));
        }
    }

    return 0;
}
