#include "buzzer.h"
#include "quty_board.h"
#include <avr/io.h>
#include <util/delay.h>

/**
 * @brief Creates a variable delay in microseconds using a loop.
 * @param us The number of microseconds to delay.
 */
static void variable_delay_us(uint16_t us)
{
    for (uint16_t i = 0; i < us; i++)
    {
        _delay_us(1); // Delay for 1 microsecond in each iteration
    }
}

/**
 * @brief Plays a tone on the buzzer for a specified duration.
 * @param period_us The period of the square wave in microseconds (us). Lower value = higher pitch.
 * @param duration_ms The duration to play the tone in milliseconds (ms).
 */
void buzzer_play_tone(uint16_t period_us, uint16_t duration_ms)
{
    // The total duration we want the sound to last, in microseconds.
    uint32_t total_duration_us = (uint32_t)duration_ms * 1000;
    
    // Calculate how many cycles of the square wave we need to play to fill the duration.
    uint32_t cycles = total_duration_us / period_us;
    
    // The time for one half of the wave (the "on" time or "off" time).
    uint16_t half_period_us = period_us / 2;

    // Loop for the required number of cycles.
    for (uint32_t i = 0; i < cycles; i++)
    {
        // Turn buzzer pin HIGH (on).
        BUZZER_PORT.OUT |= BUZZER_PIN;
        variable_delay_us(half_period_us);

        // Turn buzzer pin LOW (off).
        BUZZER_PORT.OUT &= ~BUZZER_PIN;
        variable_delay_us(half_period_us);
    }
}