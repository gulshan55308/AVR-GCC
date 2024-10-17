#include <avr/io.h>  // Register-level access to Arduino ports
#include <util/delay.h>  // For delays if needed
#include <stdint.h>  // For using uint8_t type

#define INPUT_P PD2  // Define pin 2 (Port D, Pin 2)
#define INPUT_Q PD3  // Define pin 3 (Port D, Pin 3)
#define INPUT_R PD4  // Define pin 4 (Port D, Pin 4)
#define INPUT_S PD5  // Define pin 5 (Port D, Pin 5)
#define OUTPUT_PIN PB5  // Define pin 13 (Port B, Pin 5)

void setup(void) {
    // Set inputs (PD2, PD3, PD4, PD5) as inputs
    DDRD &= ~(1 << INPUT_P);  // Set PD2 (pin 2) as input
    DDRD &= ~(1 << INPUT_Q);  // Set PD3 (pin 3) as input
    DDRD &= ~(1 << INPUT_R);  // Set PD4 (pin 4) as input
    DDRD &= ~(1 << INPUT_S);  // Set PD5 (pin 5) as input
    
    // Set output (PB5, which is pin 13) as output
    DDRB |= (1 << OUTPUT_PIN);  // Set PB5 (pin 13) as output
}

void loop(void) {
    // Read input pins (P, Q, R, S)
    uint8_t P = (PIND & (1 << INPUT_P)) ? 1 : 0;  // Read PD2 (input P)
    uint8_t Q = (PIND & (1 << INPUT_Q)) ? 1 : 0;  // Read PD3 (input Q)
    uint8_t S = (PIND & (1 << INPUT_S)) ? 1 : 0;  // Read PD5 (input S)

    // Apply the logic for output
    uint8_t output = (!P && S) || (!Q && !S);

    // Write the result to pin 13 (PB5)
    if (output) {
        PORTB |= (1 << OUTPUT_PIN);  // Set PB5 high (turn on LED)
    } else {
        PORTB &= ~(1 << OUTPUT_PIN);  // Set PB5 low (turn off LED)
    }
}

// Main function for AVR-GCC environment
int main(void) {
    setup();  // Call the setup function once
    while (1) {
        loop();  // Repeat the loop function indefinitely
    }
}

