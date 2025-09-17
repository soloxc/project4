#include "lfsr.h"

// The LFSR mask as specified in the project description.
#define MASK 0xE2025CAB

// The initial seed, based on your student number n10196072.
#define SEED 0x10196072

uint32_t lfsr_init(void)
{
    return SEED;
}

uint8_t lfsr_get_next_step(uint32_t *state_lfsr)
{
    // Algorithm from Section B of the project description:
    
    // 1. BIT ← lsbit(STATE_LFSR)
    // Get the least significant bit (LSB). The '& 1' operation isolates it.
    uint8_t bit = *state_lfsr & 1;

    // 2. STATE_LFSR ← STATE_LFSR >> 1
    // Right-shift the state by one position.
    *state_lfsr >>= 1;

    // 3. if (BIT = 1) STATE_LFSR ← STATE_LFSR xor MASK
    if (bit == 1)
    {
        *state_lfsr ^= MASK; // '^' is the XOR operator in C
    }

    // 4. STEP ← STATE_LFSR and 0b11
    // The '0b11' is a binary literal for 3. This isolates the last two bits.
    uint8_t step = *state_lfsr & 0b11;

    return step;
}