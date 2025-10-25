# ensf460-project1.X

### Key changes since Alexa's last commit

#### IOs.c
##### General
- added uint16_t CLRF (clear flag) as a variable to prevent alarm going off after resetting the timer while it is running
##### void IOcheck()
- set reset timer condition to 3 seconds, same as while the timer is running
- check for no CLRF before running alarm()

#### ProgramTimer.c
##### General
- paused changed to uint8_t
##### void startTimer()
- check for IO specific for when timer is running 10 times per loop
- delay_ms() set to 92 to account for overhead
##### void alarm()
- handles display to UART and LED blinking
- will return after a PB has been pressed, turning LEDs off
