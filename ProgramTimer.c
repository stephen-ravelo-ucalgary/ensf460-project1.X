#include "ProgramTimer.h"

uint16_t seconds = 0;
uint16_t minutes = 0;

char paused = 0;

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
    // TODO: add LED blinking
    while ((minutes > 0 || seconds > 0) && paused == 0) {
        if (seconds == 0) {
            minutes -= 1;
            seconds = 59;
        } else {
            seconds -= 1;
        }
        
        _LATB9 ^= 1;
        displayCNT();
        delay_ms(1000);
    }
    _LATB9 ^= 1;
}

void pauseTimer() {
    paused = 1;
    delay_ms(100); ///avoid to detect the same press
    while (1) {
        if(PORTAbits.RA4 == 0); // wait for next press
            delay_ms(100);      // debounce
            paused = 0;
            break;
    }
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

void displayGroupInfo() {
    Disp2String("\033[2J\033[H");
    Disp2String("2025 ENSF 460 L02 - Group 01\r");
}

