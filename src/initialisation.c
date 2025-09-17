// Replace the existing function in initialisation.c

#include "initialisation.h"
#include "quty_board.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h> // Required for _PROTECTED_WRITE

/**
 * @brief Configures all the necessary pins and peripherals for the QUTy board.
 */
void initialise_board(void)
{
    // --- Configure Main Clock Prescaler ---
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLB, CLKCTRL_PDIV_64X_gc | CLKCTRL_PEN_bm);

    // --- Configure Pushbuttons (Inputs) ---
    BUTTON_UP_PORT.DIR &= ~BUTTON_UP_PIN;
    BUTTON_DOWN_PORT.DIR &= ~BUTTON_DOWN_PIN;
    BUTTON_LEFT_PORT.DIR &= ~BUTTON_LEFT_PIN;
    BUTTON_RIGHT_PORT.DIR &= ~BUTTON_RIGHT_PIN;
    PORTA.PIN1CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN2CTRL = PORT_PULLUPEN_bm; // CORRECTED: Was PULLUPen_bm
    PORTA.PIN3CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN4CTRL = PORT_PULLUPEN_bm;

    // --- Configure Display, Buzzer, and SPI Pins ---
    DISP_MOSI_PORT.DIR |= DISP_MOSI_PIN;
    DISP_CLK_PORT.DIR |= DISP_CLK_PIN;
    DISP_ENABLE_PORT.DIR |= DISP_ENABLE_PIN;
    BUZZER_PORT.DIR |= BUZZER_PIN;
    DISP_ENABLE_PORT.OUT |= DISP_ENABLE_PIN;

    // --- Configure SPI for Display ---
    SPI0.CTRLA = SPI_MASTER_bm;
    SPI0.CTRLB = SPI_MODE_0_gc;
    SPI0.CTRLA |= SPI_ENABLE_bm;

    // --- Configure TCA0 for Buzzer Tone Generation (PWM) ---
    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_FRQ_gc;
    PORTMUX.TCAROUTEA = 0x01; 

    // --- Configure TCB0 for 100Hz Heartbeat Interrupt ---
    TCB0.CCMP = 3125;
    TCB0.CTRLA = TCB_CLKSEL_DIV1_gc; // CORRECTED: Was TCB_CLKSEL_CLKDIV1_gc
    TCB0.CTRLB = TCB_CNTMODE_INT_gc;
    TCB0.INTCTRL = TCB_CAPT_bm;
    TCB0.CTRLA |= TCB_ENABLE_bm;

    // --- Globally Enable Interrupts ---
    sei();
}