#include "display.h"
#include "quty_board.h"
#include "display_macros.h"
#include <avr/io.h>

/**
 * @brief Sends one byte of data to the 74HC595 shift register to control the segments.
 * @param segments An 8-bit value where each bit corresponds to a display segment.
 */
void display_update(uint8_t segments)
{
    // Step 1: Prepare the shift register to receive new data by pulling the latch LOW.
    DISP_LATCH_PORT.OUT &= ~DISP_LATCH_PIN;

    // Step 2: Shift out all 8 bits of the 'segments' byte, one by one.
    // The loop runs 8 times, for each bit in the byte.
    for (uint8_t i = 0; i < 8; i++)
    {
        // Set the clock pin LOW before changing the data pin to ensure clean data signals.
        DISP_CLK_PORT.OUT &= ~DISP_CLK_PIN;

        // Check the most significant bit of our data.
        // 0x80 is a mask (binary 10000000) that isolates the leftmost bit.
        if (segments & 0x80)
        {
            // If the bit is 1, set the MOSI (data) pin HIGH.
            DISP_MOSI_PORT.OUT |= DISP_MOSI_PIN;
        }
        else
        {
            // If the bit is 0, set the MOSI (data) pin LOW.
            DISP_MOSI_PORT.OUT &= ~DISP_MOSI_PIN;
        }

        // Pulse the clock pin HIGH. This rising edge shifts the bit into the register.
        DISP_CLK_PORT.OUT |= DISP_CLK_PIN;

        // Shift our data byte one position to the left. The next bit to send is now the leftmost one.
        segments <<= 1;
    }

    // Step 3: Latch the new data to the display outputs by pulling the latch HIGH.
    // This makes the pattern stored in the shift register appear on the LEDs.
    DISP_LATCH_PORT.OUT |= DISP_LATCH_PIN;
}


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