#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>  // Add this header to use bool

#define INPUT_P 2  // Pin 2
#define INPUT_Q 3  // Pin 3
#define INPUT_R 4  // Pin 4
#define INPUT_S 5  // Pin 5
#define OUTPUT_PIN 13  // Pin 13

void setup(void) {
    // Set the pin modes
    DDRD &= ~((1 << INPUT_P) | (1 << INPUT_Q) | (1 << INPUT_R) | (1 << INPUT_S)); // Set P, Q, R, S as inputs
    DDRB |= (1 << (OUTPUT_PIN - 8)); // Set outputPin as output (Pin 13 is PB5)
}

int main(void) {
    setup();

    while (1) {
        // Read input values
        bool P = PIND & (1 << INPUT_P); // Read INPUT_P
        bool Q = PIND & (1 << INPUT_Q); // Read INPUT_Q
        bool R = PIND & (1 << INPUT_R); // Read INPUT_R
        bool S = PIND & (1 << INPUT_S); // Read INPUT_S

        // Output logic based on the expression
        bool output = (!P && !S) || (!Q && !S);

        // Write to the output pin
        if (output) {
            PORTB |= (1 << (OUTPUT_PIN - 8)); // Set outputPin high
        } else {
            PORTB &= ~(1 << (OUTPUT_PIN - 8)); // Set outputPin low
        }

        _delay_ms(100); // Add a delay to prevent rapid toggling
    }

    return 0;
}

