#ifndef PROGRAMTIMER_H
#define	PROGRAMTIMER_H

#include <xc.h>
#include "timer.h"
#include "UART2.h"

uint16_t getSeconds();
void incrementSeconds(uint16_t seconds);

uint16_t getMinutes();
void incrementMinutes(uint16_t minutes);

void startTimer();
void pauseTimer();
void resetTimer();

void displaySET();
void displayCNT();
void displayFIN();

#endif
