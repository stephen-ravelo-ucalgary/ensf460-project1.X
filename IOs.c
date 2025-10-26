#include "IOs.h"
#include "UART2.h"
#include "ProgramTimer.h"

uint16_t time_elapsed_ms;

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
            if (count == 10) {
                // reset timer
                setSeconds(0);
                setMinutes(0);
                displaySET();
            }
            delay_ms(50);
            count++;
        }
        if(count < 10) {
            startTimer();   
            //LED 1 on
            _LATB9 = 1;
            while(1){
                //LED 2 blinking
                _LATA6 ^= 1;
                delay_ms(300);
            } 
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
    else if (PORTBbits.RB7 == 1 && PORTBbits.RB4 == 1 && PORTAbits.RA4 == 0) {
        //long press - reset during the counting
        while (PORTBbits.RB7 == 1 && PORTBbits.RB4 == 1 && PORTAbits.RA4 == 0) {
            Disp2String("\033[2J\033[H");
            Disp2String("\033[2J\033[HPB3 pressing");
            delay_ms(1000);
            if (count == 60) {
                // reset timer
                pauseTimer();
                setSeconds(0);
                setMinutes(0);
                displaySET();
            }
            delay_ms(50);
            count++;
        }
        //short press - pause timer
        if(count < 60) {
            Disp2String("\033[2J\033[H");
            Disp2String("\033[2J\033[HPB3 pressed");
            delay_ms(1000);
            pauseTimer();
        }
        count = 0;
    }
}
