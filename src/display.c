#include "display.h"
#include "quty_board.h" //
#include "display_macros.h" //
#include <avr/io.h>

/**
 * @brief Sends one byte of data to the 74HC595 shift register to control the segments.
 * @param segments An 8-bit value where each bit corresponds to a display segment.
 */
void display_update(uint8_t segments)
{
    // Temporarily set the shared Latch/Button pin (PA1) as an output
    DISP_LATCH_PORT.DIR |= DISP_LATCH_PIN;

    // Step 1: Prepare the shift register by pulling the latch LOW.
    DISP_LATCH_PORT.OUT &= ~DISP_LATCH_PIN;

    // Step 2: Shift out all 8 bits.
    for (uint8_t i = 0; i < 8; i++)
    {
        DISP_CLK_PORT.OUT &= ~DISP_CLK_PIN;
        if (segments & 0x80)
        {
            DISP_MOSI_PORT.OUT |= DISP_MOSI_PIN;
        }
        else
        {
            DISP_MOSI_PORT.OUT &= ~DISP_MOSI_PIN;
        }
        DISP_CLK_PORT.OUT |= DISP_CLK_PIN;
        segments <<= 1;
    }

    // Step 3: Latch the new data to the display outputs by pulling the latch HIGH.
    DISP_LATCH_PORT.OUT |= DISP_LATCH_PIN;

    // IMPORTANT: Return the pin to be an input for the button.
    DISP_LATCH_PORT.DIR &= ~DISP_LATCH_PIN;
}

// NOTE: The rest of the file (segment_patterns array and display_show_number)
// remains exactly the same and is omitted here for brevity.
// Do NOT delete it from your file.

// This is a lookup table for the segment patterns of digits 0-9.
// NOTE: This is not currently used by the Simon game logic but is here for completeness.
const uint8_t segment_patterns[] = {
    DISP_SEG_A & DISP_SEG_B & DISP_SEG_C & DISP_SEG_D & DISP_SEG_E & DISP_SEG_F, // 0
    DISP_SEG_B & DISP_SEG_C,                                                   // 1
    DISP_SEG_A & DISP_SEG_B & DISP_SEG_G & DISP_SEG_E & DISP_SEG_D,             // 2
    DISP_SEG_A & DISP_SEG_B & DISP_SEG_G & DISP_SEG_C & DISP_SEG_D,             // 3
    DISP_SEG_F & DISP_SEG_G & DISP_SEG_B & DISP_SEG_C,                         // 4
    DISP_SEG_A & DISP_SEG_F & DISP_SEG_G & DISP_SEG_C & DISP_SEG_D,             // 5
    DISP_SEG_A & DISP_SEG_F & DISP_SEG_E & DISP_SEG_D & DISP_SEG_C & DISP_SEG_G, // 6
    DISP_SEG_A & DISP_SEG_B & DISP_SEG_C,                                     // 7
    DISP_SEG_A & DISP_SEG_B & DISP_SEG_C & DISP_SEG_D & DISP_SEG_E & DISP_SEG_F & DISP_SEG_G, // 8
    DISP_SEG_A & DISP_SEG_B & DISP_SEG_C & DISP_SEG_D & DISP_SEG_F & DISP_SEG_G  // 9
};

/**
 * @brief Displays a single digit number on the 7-segment display.
 * @param number The number to display (0-9).
 */
void display_show_number(uint8_t number)
{
    // Check if the number is within the bounds of our lookup table
    if (number < sizeof(segment_patterns))
    {
        display_update(segment_patterns[number]);
    }
}