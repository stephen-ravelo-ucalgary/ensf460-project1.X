#include "timer.h"

void timerInit() {
    // TMR2 config
    T2CONbits.T32 = 0;      // operate timer 2 as 16 bit timer
    T2CONbits.TCKPS = 3;    // set prescalar to 256
    T2CONbits.TCS = 0;
    T2CONbits.TGATE = 0;
    T2CONbits.TSIDL = 0;
    IPC1bits.T2IP = 2;
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1;
}

void delay_ms(uint16_t time_ms) {
    PR2 = 1 * time_ms;      // PR2 coefficient: 1 ~= 0.001 * 250000 / 256
    TMR2 = 0;
    
    T2CONbits.TON = 1;
    
    Idle();                 // wait here until interrupt 
                            // TODO: needs protection againts CN interrupts
    
    return;
}
