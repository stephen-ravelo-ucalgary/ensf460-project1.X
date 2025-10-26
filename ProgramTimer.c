#include "ProgramTimer.h"

uint16_t seconds = 0;
uint16_t minutes = 0;

char paused = 0;      // pause flag

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
    //variables to track the button press
    unsigned int press_time = 0;  // press time
    const unsigned int long_press_ms = 3000; // 3 seconds
    const unsigned int delay_interval = 50;  // time interval to verify 
    
    while (minutes > 0 || seconds > 0) {
        // Check if pause button is pressed while paused
        if (paused) {
            if (PORTAbits.RA4 == 0) {
                press_time = 0;
                while (PORTAbits.RA4 == 0) {  // while still pressed
                    delay_ms(delay_interval);
                    press_time++;

                    // If pressed ? 3 s
                    if (press_time >= 60) {
                        // Reset timer
                        setSeconds(0);
                        setMinutes(0);
                        displayCNT();
                        // Keep paused
                        paused = 1;
                        return;
                    }
                }
            }

            // If not pressed or released before 3 s, stay paused
            delay_ms(50);
            continue;
        }
        delay_ms(1000);
        if (seconds == 0) {
            minutes -= 1;
            seconds = 59;
        } else {
            seconds -= 1;
        }
        // LED 1 blinking each second
        _LATB9 ^= 1;
        displayCNT();
    }
}

void pauseTimer() {
    paused = !paused;  // alternate pause state
}

void displaySET() {
    Disp2String("\033[2J\033[HSET ");
    Disp2Dec(minutes);
    Disp2String("m : ");
    Disp2Dec(seconds);
    Disp2String("s\r");
}

void displayCNT() {
    if(minutes == 0 && seconds == 0 && paused == 0){
        Disp2String("\033[2J\033[H");
        Disp2String("\033[2J\033[HFIN 00m : 00s - ALARM\r");
        _LATB9 = 1;
        return 0;
    }
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

