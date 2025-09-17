#include "initialisation.h"
#include "display.h"
#include "buzzer.h"
#include "lfsr.h" // Include our new PRNG module
#include "display_macros.h" // For the new DISP_STEP_ macros
#include <util/delay.h>

// New notes based on the project description
#define NOTE_E_HIGH 1517 // 659 Hz (E5) for STEP 0
#define NOTE_CS     1804 // 554 Hz (C#5) for STEP 1
#define NOTE_A      2273 // 440 Hz (A4) for STEP 2
#define NOTE_E_LOW  3034 // 329 Hz (E4) for STEP 3

void state_machine(void);

int main(void)
{
    initialise_board();
    state_machine();
    while(1);
}

void state_machine(void)
{
    // --- Game State Variables ---
    // This seed marks the beginning of the current game's sequence.
    // It's only updated on a full reset or when the player loses.
    uint32_t sequence_start_seed = lfsr_init();

    // The current length of the sequence for this turn.
    uint8_t turn_length = 1;

    // A lookup table for our display patterns
    const uint8_t step_displays[] = {DISP_STEP_0, DISP_STEP_1, DISP_STEP_2, DISP_STEP_3};
    // A lookup table for our notes
    const uint16_t step_notes[] = {NOTE_E_HIGH, NOTE_CS, NOTE_A, NOTE_E_LOW};

    while (1)
    {
        // --- Play the sequence to the user ---
        
        // We must start from the beginning of the sequence for each playback.
        // So, we create a temporary copy of the starting seed for this turn.
        uint32_t playback_lfsr = sequence_start_seed;

        // Loop for the number of steps in the current turn.
        for (uint8_t i = 0; i < turn_length; i++)
        {
            // Generate the next step without permanently changing the seed.
            uint8_t current_step = lfsr_get_next_step(&playback_lfsr);

            // 1. Show the pattern on the display
            display_update(step_displays[current_step]);

            // 2. Play the corresponding note
            buzzer_play_tone(step_notes[current_step], 300); // Play for 300ms

            // 3. Wait briefly with a blank display
            display_update(DISP_OFF);
            _delay_ms(150);
        }

        // --- Wait for player input (To be implemented in the next step) ---
        // For now, we'll just wait and then increase the turn length automatically.

        _delay_ms(1000); // Wait before starting the next, longer sequence.
        turn_length++; // Make the sequence one step longer for the next turn.
    }
}