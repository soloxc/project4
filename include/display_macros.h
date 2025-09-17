#ifndef DISPLAY_MACROS_H
#define DISPLAY_MACROS_H

// Raw segment definitions (inverted logic for common anode or shift register)
#define DISP_SEG_A 0b01111110
#define DISP_SEG_B 0b01111101
#define DISP_SEG_C 0b01111011
#define DISP_SEG_D 0b01110111
#define DISP_SEG_E 0b01101111
#define DISP_SEG_F 0b01011111
#define DISP_SEG_G 0b00111111

// This bit selects the Left Hand Side digit (DIGIT 1)
#define DISP_LHS (1 << 7)

// --- Corrected Simon Step Definitions ---
// For each step, we combine the segment pattern with the digit select bit.

// Step 0 -> S1: Digit 1, Segments EF
#define DISP_STEP_0 ((DISP_SEG_E & DISP_SEG_F) | DISP_LHS)

// Step 1 -> S2: Digit 1, Segments BC
#define DISP_STEP_1 ((DISP_SEG_B & DISP_SEG_C) | DISP_LHS)

// Step 2 -> S3: Digit 2, Segments EF
#define DISP_STEP_2 (DISP_SEG_E & DISP_SEG_F) // No LHS bit, so it's the right digit

// Step 3 -> S4: Digit 2, Segments BC
#define DISP_STEP_3 (DISP_SEG_B & DISP_SEG_C) // No LHS bit, so it's the right digit


#define DISP_OFF 0b01111111 // All segments off, doesn't matter which digit

#endif  