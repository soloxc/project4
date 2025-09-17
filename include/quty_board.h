#ifndef QUTY_BOARD_H
#define QUTY_BOARD_H

#include <avr/io.h> // Required for VPORT and PIN definitions

/*
 * ==========================================================================
 * QUTy Development Board (ATtiny1626) Pin Definitions
 * ==========================================================================
 * This file maps the hardware components of the QUTy board to their
 * corresponding pins on the ATtiny1626 microcontroller, based on the
 * official schematic (QUTY-S01-V01).
 *
 * This file acts as a Hardware Abstraction Layer (HAL) to make the main
 * application code more readable and easier to maintain.
 */


// -- Pushbuttons (Digital Inputs) --
// The four directional pushbuttons are connected to PORTA.
// They should be configured as inputs with pull-up resistors enabled.
#define BUTTON_UP_PORT      VPORTA
#define BUTTON_UP_PIN       PIN1_bm  // Mapped to PA1

#define BUTTON_DOWN_PORT    VPORTA
#define BUTTON_DOWN_PIN     PIN2_bm  // Mapped to PA2

#define BUTTON_LEFT_PORT    VPORTA
#define BUTTON_LEFT_PIN     PIN3_bm  // Mapped to PA3

#define BUTTON_RIGHT_PORT   VPORTA
#define BUTTON_RIGHT_PIN    PIN4_bm  // Mapped to PA4


// -- 7-Segment LED Display Control --
// The display is driven by a 74HC595 shift register.
// These are the MCU pins used to send data to the driver.
#define DISP_MOSI_PORT      VPORTC
#define DISP_MOSI_PIN       PIN2_bm  // SPI MOSI, mapped to PC2

#define DISP_CLK_PORT       VPORTC
#define DISP_CLK_PIN        PIN1_bm  // SPI CLK, mapped to PC1

// NOTE: DISP_LATCH is shared with the UP button on the same pin (PA1).
// This pin is used to latch the data from the shift register to its output.
#define DISP_LATCH_PORT     VPORTA
#define DISP_LATCH_PIN      PIN1_bm  // Mapped to PA1

// The Display Enable pin controls the output of the display buffer.
#define DISP_ENABLE_PORT    VPORTB
#define DISP_ENABLE_PIN     PIN1_bm  // Mapped to PB1


// -- Potentiometer (Analog Input) --
// The potentiometer provides a variable voltage for analog readings.
// The pin should be configured as a digital input to use the ADC.
#define POT_ADC_PORT        VPORTA
#define POT_ADC_PIN         PIN7_bm  // Mapped to PA7 (AIN7)


// -- Piezo Buzzer (Audio Output) --
// Connected to a Timer/Counter (TCA) capable pin for generating tones.
#define BUZZER_PORT         VPORTB
#define BUZZER_PIN          PIN0_bm  // Mapped to PB0 (TCA0 WO0)


// -- UART Communication --
// Pins for communication with the onboard CP2102N USB-to-UART bridge.
#define UART_TXD_PORT       VPORTB
#define UART_TXD_PIN        PIN2_bm  // Mapped to PB2 (MCU TXD -> Bridge RXD)

#define UART_RXD_PORT       VPORTB
#define UART_RXD_PIN        PIN3_bm  // Mapped to PB3 (MCU RXD <- Bridge TXD)


// -- General Purpose SPI (PMOD Connector) --
// Standard SPI pins are routed to the breakout header.
#define SPI_MOSI_PORT       VPORTC
#define SPI_MOSI_PIN        PIN2_bm  // Mapped to PC2

#define SPI_MISO_PORT       VPORTC
#define SPI_MISO_PIN        PIN3_bm  // Mapped to PC3

#define SPI_SCK_PORT        VPORTC
#define SPI_SCK_PIN         PIN1_bm  // Mapped to PC1 (SCK is another name for CLK)

#define SPI_CS_PORT         VPORTC
#define SPI_CS_PIN          PIN0_bm  // Mapped to PC0 (Chip Select)


// -- Programming and Debugging Interface --
// The dedicated UPDI pin used for programming and debugging.
#define UPDI_PORT           VPORTA
#define UPDI_PIN            PIN0_bm  // Mapped to PA0


#endif // QUTY_BOARD_H