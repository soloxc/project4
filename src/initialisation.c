#include "initialisation.h"
#include "quty_board.h" // We need our pin definitions!
#include <avr/io.h>     // We need the register definitions

/**
 * @brief Configures all the necessary pins and peripherals for the QUTy board.
 */
void initialise_board(void)
{
    // --- Configure Pushbuttons (Inputs) ---
    // Set button pins to be inputs by clearing the bits in the DIR register.
    BUTTON_UP_PORT.DIR    &= ~BUTTON_UP_PIN;
    BUTTON_DOWN_PORT.DIR  &= ~BUTTON_DOWN_PIN;
    BUTTON_LEFT_PORT.DIR  &= ~BUTTON_LEFT_PIN;
    BUTTON_RIGHT_PORT.DIR &= ~BUTTON_RIGHT_PIN;

    // Enable the internal pull-up resistors for each button.
    PORTA.PIN1CTRL = PORT_PULLUPEN_bm; // Button Up
    PORTA.PIN2CTRL = PORT_PULLUPEN_bm; // Button Down
    PORTA.PIN3CTRL = PORT_PULLUPEN_bm; // Button Left
    PORTA.PIN4CTRL = PORT_PULLUPEN_bm; // Button Right

    // --- Configure Buzzer (Output) ---
    // Set the buzzer pin to be an output.
    BUZZER_PORT.DIR |= BUZZER_PIN;

    // --- Configure 7-Segment Display Pins (Outputs) ---
    // Set all control pins for the display driver to be outputs.
    DISP_MOSI_PORT.DIR   |= DISP_MOSI_PIN;
    DISP_CLK_PORT.DIR    |= DISP_CLK_PIN;
    DISP_LATCH_PORT.DIR  |= DISP_LATCH_PIN;
    DISP_ENABLE_PORT.DIR |= DISP_ENABLE_PIN;
    
    // --- Configure Potentiometer (Analog Input) ---
    // For analog input, the pin must be configured as a digital input.
    POT_ADC_PORT.DIR &= ~POT_ADC_PIN;
    // To save power, it's also good practice to disable the digital input buffer
    // on pins used exclusively for analog readings.
    PORTA.PIN7CTRL = PORT_ISC_INPUT_DISABLE_gc;
}