#include "initialisation.h"
#include "display.h"
#include "buzzer.h"
#include "lfsr.h"
#include <util/delay.h>
#include <avr/interrupt.h>

// --- Game Constants ---
#define STEP_ON_DURATION    300 // ms
#define STEP_OFF_DURATION   150 // ms

// --- Software Timers ---
// These are simple countdown timers, managed by our ISR. 1 tick = 10ms.
volatile uint16_t timer_ticks = 0;

// This is the "Heartbeat" ISR. It runs every 10ms (100Hz).
ISR(TCB0_INT_vect)
{
    display_multiplex_update(); // Keep the display refreshed
    buzzer_update_duration();   // Countdown the buzzer duration
    
    if (timer_ticks > 0) {
        timer_ticks--;
    }

    // Clear the interrupt flag
    TCB0.INTFLAGS = TCB_CAPT_bm;
}

void delay_ms_non_blocking(uint16_t ms) {
    // Convert ms into 10ms ticks
    timer_ticks = ms / 10;
    // Wait for the ISR to count down the timer
    while (timer_ticks > 0);
}

void state_machine(void);

int main(void)
{
    initialise_board();
    state_machine();
    while(1);
}

void state_machine(void)
{
    uint32_t sequence_start_seed = lfsr_init();
    uint8_t turn_length = 1;

    while (1)
    {
        // --- Play the sequence to the user ---
        uint32_t playback_lfsr = sequence_start_seed;

        for (uint8_t i = 0; i < turn_length; i++)
        {
            uint8_t current_step = lfsr_get_next_step(&playback_lfsr);

            // --- Step ON State ---
            display_show_step(current_step);
            buzzer_play_note(current_step);
            buzzer_set_duration(STEP_ON_DURATION); // Tell ISR to turn buzzer off after 300ms
            delay_ms_non_blocking(STEP_ON_DURATION);

            // --- Step OFF State ---
            display_off();
            // Buzzer is already off via ISR
            delay_ms_non_blocking(STEP_OFF_DURATION);
        }

        // --- Wait for player input (To be implemented) ---
        delay_ms_non_blocking(1000);
        turn_length++;
    }
}