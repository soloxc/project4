#ifndef LFSR_H
#define LFSR_H

#include <stdint.h>

/**
 * @brief Initialises the LFSR with the starting seed.
 * * @return The initial 32-bit seed value.
 */
uint32_t lfsr_init(void);

/**
 * @brief Calculates the next step in a sequence from a given LFSR state.
 *
 * This function takes a pointer to an LFSR state, calculates the next state
 * according to the specified algorithm, updates the state in place, and
 * returns the resulting step (0, 1, 2, or 3).
 *
 * @param state_lfsr A pointer to the 32-bit LFSR state to be updated.
 * @return The next step value (0, 1, 2, or 3).
 */
uint8_t lfsr_get_next_step(uint32_t *state_lfsr);

#endif