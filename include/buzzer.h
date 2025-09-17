// Replace the contents of buzzer.h

#ifndef BUZZER_H
#define BUZZER_H
#include <stdint.h>

void buzzer_play_note(uint8_t step);
void buzzer_stop(void);
void buzzer_set_duration(uint16_t duration_ms); // <-- ADD THIS LINE
void buzzer_update_duration(void);

#endif