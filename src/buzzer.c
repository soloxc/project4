#include "buzzer.h"
#include "quty_board.h"
#include <avr/io.h>

// Note periods calculated from your student number (xy=72)
#define NOTE_E_HIGH_PERIOD 4630 // For STEP 0
#define NOTE_CS_PERIOD     5525 // For STEP 1
#define NOTE_A_PERIOD      3472 // For STEP 2
#define NOTE_E_LOW_PERIOD  9259 // For STEP 3
const uint16_t step_notes[] = {NOTE_E_HIGH_PERIOD, NOTE_CS_PERIOD, NOTE_A_PERIOD, NOTE_E_LOW_PERIOD};

// --- State Variable ---
// Countdown timer for note duration. 1 tick = 10ms (from our 100Hz TCB interrupt)
static volatile uint16_t duration_ticks = 0;

void buzzer_play_note(uint8_t step) {
    // Set the frequency using the TCA0 hardware timer
    TCA0.SINGLE.CMP0 = step_notes[step] / 2; // Compare value for 50% duty cycle
    TCA0.SINGLE.PER = step_notes[step];      // Period of the wave
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc | TCA_SINGLE_ENABLE_bm; // Start timer
}

void buzzer_stop(void) {
    TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm; // Stop the timer
}

void buzzer_set_duration(uint16_t duration_ms) {
    // Convert ms to 10ms ticks for our heartbeat ISR
    duration_ticks = duration_ms / 10;
}

// This function gets called by the 100Hz ISR
void buzzer_update_duration(void) {
    if (duration_ticks > 0) {
        duration_ticks--;
        if (duration_ticks == 0) {
            buzzer_stop();
        }
    }
}