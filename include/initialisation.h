#ifndef INITIALISATION_H
#define INITIALISATION_H

// This is a function declaration (or "prototype").
// It tells the rest of the program that a function named
// "initialise_board" exists, takes no arguments (void),
// and returns nothing (void).
void initialise_board(void);

// in initialise_board() function inside initialisation.c

    // --- Configure 7-Segment Display Pins (Outputs) ---
    // Set all control pins for the display driver to be outputs.
    DISP_MOSI_PORT.DIR   |= DISP_MOSI_PIN;
    DISP_CLK_PORT.DIR    |= DISP_CLK_PIN;
    DISP_LATCH_PORT.DIR  |= DISP_LATCH_PIN;
    DISP_ENABLE_PORT.DIR |= DISP_ENABLE_PIN;

    // ADD THIS LINE: Globally enable the display driver output.
    DISP_ENABLE_PORT.OUT |= DISP_ENABLE_PIN;
    
#endif