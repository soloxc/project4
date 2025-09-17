#ifndef DISPLAY_H
#define DISPLAY_H
#include <stdint.h>

// High-level function to set the display for a Simon step
void display_show_step(uint8_t step);

// Turns the display completely off
void display_off(void);

// This function is now called ONLY by the timer ISR
void display_multiplex_update(void);

// This function is no longer called from main.c
void display_update(uint8_t segments);

#endif