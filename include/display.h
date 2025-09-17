#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h> // Provides standard integer types like uint8_t

/**
 * @brief Sends a raw 8-bit pattern to the display's shift register.
 * @param segments An 8-bit value where each bit corresponds to a display segment.
 */
void display_update(uint8_t segments);

/**
 * @brief Displays a number (0-9) by looking up its pattern. (No longer used in main)
 * @param number The number to display.
 */
void display_show_number(uint8_t number);

#endif