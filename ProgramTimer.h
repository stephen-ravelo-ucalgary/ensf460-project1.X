#ifndef PROGRAMTIMER_H
#define	PROGRAMTIMER_H

#include <xc.h>
#include "timer.h"
#include "UART2.h"

uint16_t getSeconds();
void setSeconds(uint16_t seconds);
void incrementSeconds(uint16_t seconds);
void decrementSeconds(uint16_t seconds);

uint16_t getMinutes();
void setMinutes(uint16_t minutes);
void incrementMinutes(uint16_t minutes);
void decrementMinutes(uint16_t minutes);

void startTimer();
void pauseTimer();
void resetTimer();

void displaySET();
void displayCNT();
void displayFIN();

void displayGroupInfo();

#endif
