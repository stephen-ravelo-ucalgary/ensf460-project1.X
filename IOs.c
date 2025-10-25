#include "IOs.h"

uint16_t CLRF = 0;

// Initialize peripheral IO
void IOinit() {
    // LED1
    TRISBbits.TRISB9 = 0;
    
    // LED2
    TRISAbits.TRISA6 = 0;

    // PB1
    TRISBbits.TRISB7 = 1;
    CNPU2bits.CN23PUE = 1;
    CNEN2bits.CN23IE = 1;  
    
    // PB3
    TRISBbits.TRISB4 = 1;
    CNPU1bits.CN1PUE = 1;
    CNEN1bits.CN1IE = 1;
    
    // PB3
    TRISAbits.TRISA4 = 1;
    CNPU1bits.CN0PUE = 1;
    CNEN1bits.CN0IE = 1;
}

// Execute logic for peripheral IO
void IOcheck() {   
    uint16_t count = 0;
    
    if (PORTBbits.RB7 == 0 && PORTBbits.RB4 == 1 && PORTAbits.RA4 == 1) {
        while (PORTBbits.RB7 == 0 && PORTBbits.RB4 == 1 && PORTAbits.RA4 == 1) {
            if (count >= 5 && getSeconds() % 5 == 0) {
                incrementSeconds(5);
            } else {
                incrementSeconds(1);
                count++;
            }
            displaySET();
            delay_ms(500);
        }
        count = 0;
    }
    else if (PORTBbits.RB7 == 1 && PORTBbits.RB4 == 0 && PORTAbits.RA4 == 1) {
        while (PORTBbits.RB7 == 1 && PORTBbits.RB4 == 0 && PORTAbits.RA4 == 1) {
            if (count >= 5 && getMinutes() % 5 == 0) {
                incrementMinutes(5);
            } else {
                incrementMinutes(1);
                count++;
            }
            displaySET();
            delay_ms(500);
        }
        count = 0;
    }
    else if (PORTBbits.RB7 == 0 && PORTBbits.RB4 == 0 && PORTAbits.RA4 == 1) {
        while (PORTBbits.RB7 == 0 && PORTBbits.RB4 == 0 && PORTAbits.RA4 == 1) {
            if (count == 60) {  // reset timer if PB1 and PB2 held for 500 ms
                resetTimer();
                displaySET();
            }
            delay_ms(50);
            count++;
        }
        if(count < 60) {
            startTimer();
            if (!CLRF) {        // if timer has not been cleared while running
                                // trigger alarm at end of timer
                alarm();
            }
            CLRF = 0;
        }
        count = 0;
    }
    else if (PORTBbits.RB7 == 0 && PORTBbits.RB4 == 1 && PORTAbits.RA4 == 0) {
        while (PORTBbits.RB7 == 0 && PORTBbits.RB4 == 1 && PORTAbits.RA4 == 0) {
            decrementSeconds(1);
            displaySET();
            delay_ms(500);
        }
    }
    else if (PORTBbits.RB7 == 1 && PORTBbits.RB4 == 0 && PORTAbits.RA4 == 0) {
        while (PORTBbits.RB7 == 1 && PORTBbits.RB4 == 0 && PORTAbits.RA4 == 0) {
            decrementMinutes(1);
            displaySET();
            delay_ms(500);
        }
    }
    else if (PORTBbits.RB7 == 0 && PORTBbits.RB4 == 0 && PORTAbits.RA4 == 0) {
        uint16_t groupInfoDisplayed = 1;
        while(PORTBbits.RB7 == 0 && PORTBbits.RB4 == 0 && PORTAbits.RA4 == 0) {
            if(groupInfoDisplayed == 1) {
                displayGroupInfo();
                groupInfoDisplayed = 0;
            }
        }
        displaySET();
    }
}

void IOcheckRunning() {
    int count = 0;
    if (PORTBbits.RB7 == 1 && PORTBbits.RB4 == 1 && PORTAbits.RA4 == 0) {
        while (PORTBbits.RB7 == 1 && PORTBbits.RB4 == 1 && PORTAbits.RA4 == 0) {
            if (count == 60) {  // reset timer after PB3 is held for 3 seconds
                                // while timer is running
                resetTimer();
                displayCLR();
                CLRF = 1;
            }
            delay_ms(50);
            count++;

        }
        if (count < 60) {   // otherwise, pause the timer
            pauseTimer();
        }
        count = 0;
    }
}