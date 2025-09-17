#include "initialisation.h"
#include "display.h"
#include "buzzer.h"
#include "lfsr.h"
#include "display_macros.h"
#include "quty_board.h" // <-- Include this for direct buzzer pin control
#include <util/delay.h>

// Correct note periods calculated from your student number (xy=72)
#define NOTE_E_HIGH_PERIOD 4630 // 216 Hz for STEP 0
#define NOTE_CS_PERIOD     5525 // 181 Hz for STEP 1
#define NOTE_A_PERIOD      3472 // 288 Hz for STEP 2
#define NOTE_E_LOW_PERIOD  9259 // 108 Hz for STEP 3

#define STEP_ON_DURATION    300 // ms
#define STEP_OFF_DURATION   150 // ms

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

    const uint8_t step_displays[] = {DISP_STEP_0, DISP_STEP_1, DISP_STEP_2, DISP_STEP_3};
    const uint16_t step_notes[] = {NOTE_E_HIGH_PERIOD, NOTE_CS_PERIOD, NOTE_A_PERIOD, NOTE_E_LOW_PERIOD};

    while (1)
    {
        // --- Play the sequence to the user ---
        uint32_t playback_lfsr = sequence_start_seed;

        for (uint8_t i = 0; i < turn_length; i++)
        {
            uint8_t current_step = lfsr_get_next_step(&playback_lfsr);

            // --- Step ON State ---
            // 1. Show the pattern on the display
            display_update(step_displays[current_step]);
            // 2. Play the corresponding note
            buzzer_play_tone(step_notes[current_step], STEP_ON_DURATION);
            
            // --- Step OFF State ---
            // 3. Turn display off
            display_update(DISP_OFF);
            // 4. Wait for the pause between steps
            _delay_ms(STEP_OFF_DURATION);
        }

        // --- Wait for player input (To be implemented) ---
        _delay_ms(1000); // Wait a second before the next turn
        turn_length++;
    }
}