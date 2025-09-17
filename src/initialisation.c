#include "initialisation.h"
#include "quty_board.h" //
#include <avr/io.h>     //

/**
 * @brief Configures all the necessary pins and peripherals for the QUTy board.
 */
void initialise_board(void)
{
    // --- Configure Pushbuttons (Inputs) ---
    BUTTON_UP_PORT.DIR    &= ~BUTTON_UP_PIN;
    BUTTON_DOWN_PORT.DIR  &= ~BUTTON_DOWN_PIN;
    BUTTON_LEFT_PORT.DIR  &= ~BUTTON_LEFT_PIN;
    BUTTON_RIGHT_PORT.DIR &= ~BUTTON_RIGHT_PIN;

    // Enable the internal pull-up resistors for each button.
    PORTA.PIN1CTRL = PORT_PULLUPEN_bm; // Button Up / Latch Pin
    PORTA.PIN2CTRL = PORT_PULLUPEN_bm; // Button Down
    PORTA.PIN3CTRL = PORT_PULLUPEN_bm; // Button Left
    PORTA.PIN4CTRL = PORT_PULLUPEN_bm; // Button Right

    // --- Configure Buzzer (Output) ---
    BUZZER_PORT.DIR |= BUZZER_PIN;

    // --- Configure 7-Segment Display Pins (Outputs) ---
    DISP_MOSI_PORT.DIR   |= DISP_MOSI_PIN;
    DISP_CLK_PORT.DIR    |= DISP_CLK_PIN;
    DISP_ENABLE_PORT.DIR |= DISP_ENABLE_PIN;

    // REMOVED: DISP_LATCH_PORT.DIR |= DISP_LATCH_PIN;
    // This line is removed because PA1 must be an input by default for the button.

    // Globally enable the display driver output.
    DISP_ENABLE_PORT.OUT |= DISP_ENABLE_PIN;
    
    // --- Configure Potentiometer (Analog Input) ---
    POT_ADC_PORT.DIR &= ~POT_ADC_PIN;
    PORTA.PIN7CTRL = PORT_ISC_INPUT_DISABLE_gc;
}