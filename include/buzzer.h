#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h> // For uint16_t

/**
 * @brief Plays a tone on the buzzer for a specified duration.
 * @param period_us The period of the square wave in microseconds (us). Lower value = higher pitch.
 * @param duration_ms The duration to play the tone in milliseconds (ms).
 */
void buzzer_play_tone(uint16_t period_us, uint16_t duration_ms);

#endif