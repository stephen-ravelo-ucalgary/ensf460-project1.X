/*
 * File Name: ProgramTimer.c
 * Assignment: Project 1
 * Lab Section: B02
 * Completed by: Stephen Ravelo, Aaron Lauang, Alexa Gonzalez
 * Submission Date: October 26, 2025
 */

#include "ProgramTimer.h"
#include "IOs.h"

uint16_t seconds = 0;
uint16_t minutes = 0;
uint8_t paused = 0;

uint16_t getSeconds() {
    return seconds;
}

void setSeconds(uint16_t s) {
    seconds = s;
}

void incrementSeconds(uint16_t s) {
    seconds += s;
    if (seconds > 59) {
        seconds -= 60;
    }
}

void decrementSeconds(uint16_t s) {
    if(seconds == 0) {
        seconds += 60;
    }
    seconds -= s;
}

uint16_t getMinutes() {
    return minutes;
}

void setMinutes(uint16_t m) {
    minutes = m;
}

void incrementMinutes(uint16_t m) {
    minutes += m;
    if (minutes > 59) {
        minutes -= 60;
    }
}

void decrementMinutes(uint16_t m) {
    if(minutes == 0) {
        minutes += 60;
    }
    minutes -= m;
}

void startTimer() {
    // Variables to control intervals
    const unsigned int INTERVAL_MS = 50;           // Short interval to check the button
    const unsigned int TICKS_PER_SECOND = 1000 / INTERVAL_MS; // Number of intervals in 1 second
    const unsigned int LONG_PRESS_TICKS = 3000 / INTERVAL_MS; // 3 seconds in ticks

    unsigned int press_time = 0; // Counter to track button press duration

    while (minutes > 0 || seconds > 0) {
        int ticks = 0;

        while (ticks < TICKS_PER_SECOND) {
            // PAUSE / LONG PRESS DETECTION
            if (paused) {
                if (PORTAbits.RA4 == 0) {   // Button is pressed while paused
                    press_time++;
                    if (press_time >= LONG_PRESS_TICKS) {
                        // Long press: reset timer
                        paused = 1; // Keep paused
                        resetTimer();
                        displayCLR();
                        CLRF = 1;
                        return;     // Exit timer
                    }
                } else {
                    press_time = 0; // Button released before long press threshold
                }
                delay_ms(INTERVAL_MS);
                continue; // Stay paused
            }
            delay_ms(INTERVAL_MS);
            ticks++;
        }
        // Update timer every second if not paused
        if (!paused) {
            if (seconds == 0) {
                if (minutes > 0) minutes--;
                seconds = (minutes > 0) ? 59 : 0;
            } else {
                seconds--;
            }
            _LATB9 ^= 1; // Toggle LED each second
            displayCNT();
        }
    }
    _LATB9 = 0; // Turn off LED when countdown ends
}

void resetTimer() {
    seconds = 0;
    minutes = 0;
}

// Displays finished message, turns LED1 on, and toggles LED2 every 300 ms
// until a button is pressed
void alarm() {
    displayFIN();
    _LATB9 = 1;
    
    //  Show alarm until any button is pressed
    while (PORTBbits.RB7 == 1 && PORTBbits.RB4 == 1 && PORTAbits.RA4 == 1) {
        // LED 2 blinking
        _LATA6 ^= 1;
        delay_ms(250);
    }
    _LATB9 = 0;
    _LATA6 = 0;
    Disp2String("\033[2J\033[H\r");
}

void displaySET() {
    Disp2String("\033[2J\033[HSET ");
    Disp2Dec(minutes);
    Disp2String("m : ");
    Disp2Dec(seconds);
    Disp2String("s\r");
}

void displayCNT() {
    Disp2String("\033[2J\033[HCNT ");
    Disp2Dec(minutes);
    Disp2String("m : ");
    Disp2Dec(seconds);
    Disp2String("s\r");
}

void displayCLR() {
    Disp2String("\033[2J\033[HCLR ");
    Disp2Dec(minutes);
    Disp2String("m : ");
    Disp2Dec(seconds);
    Disp2String("s\r");
}

void displayGroupInfo() {
    Disp2String("\033[2J\033[H");
    Disp2String("2025 ENSF 460 L02 - Group 01\r");
}

void displayFIN() {
    Disp2String("\033[2J\033[H\r");
    Disp2String("\033[2J\033[HFIN 00m : 00s - ALARM\r");
}