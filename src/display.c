#include "display.h"
#include "display_macros.h"
#include "quty_board.h"
#include <avr/io.h>

// --- State Variables ---
// These variables store what SHOULD be on the display.
// The ISR will read from these.
static uint8_t pattern_digit_1 = DISP_OFF;
static uint8_t pattern_digit_2 = DISP_OFF;

// This tells the ISR which digit to update next
static uint8_t active_digit = 1;

const uint8_t step_displays[] = {DISP_STEP_0, DISP_STEP_1, DISP_STEP_2, DISP_STEP_3};

void display_show_step(uint8_t step) {
    // Determine which digit the step corresponds to
    if (step < 2) { // Step 0 or 1 is on Digit 1
        pattern_digit_1 = step_displays[step];
        pattern_digit_2 = DISP_OFF;
    } else { // Step 2 or 3 is on Digit 2
        pattern_digit_1 = DISP_OFF;
        pattern_digit_2 = step_displays[step];
    }
}

void display_off(void) {
    pattern_digit_1 = DISP_OFF;
    pattern_digit_2 = DISP_OFF;
}

void display_multiplex_update(void) {
    if (active_digit == 1) {
        display_update(pattern_digit_1);
        active_digit = 2;
    } else {
        display_update(pattern_digit_2);
        active_digit = 1;
    }
}

/**
 * @brief Sends one byte of data to the 74HC595 shift register using the SPI peripheral.
 * @param segments An 8-bit value where each bit corresponds to a display segment.
 */
void display_update(uint8_t segments)
{
    // Temporarily set the shared Latch/Button pin (PA1) as an output
    DISP_LATCH_PORT.DIR |= DISP_LATCH_PIN;

    // Step 1: Prepare the shift register by pulling the latch LOW.
    DISP_LATCH_PORT.OUT &= ~DISP_LATCH_PIN;

    // Step 2: Write the data to the SPI Data Register.
    // This action automatically triggers the hardware to send all 8 bits.
    SPI0.DATA = segments;

    // Step 3: Wait for the hardware to finish sending the byte.
    // We do this by waiting for the SPI Interrupt Flag (IF) to be set.
    while (!(SPI0.INTFLAGS & SPI_IF_bm));
    // (The flag is automatically cleared after we write to SPI0.DATA again later)

    // Step 4: Latch the new data to the display outputs by pulling the latch HIGH.
    DISP_LATCH_PORT.OUT |= DISP_LATCH_PIN;

    // IMPORTANT: Return the pin to be an input for the button.
    DISP_LATCH_PORT.DIR &= ~DISP_LATCH_PIN;
}