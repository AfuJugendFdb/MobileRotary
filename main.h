#ifndef _MAIN_H_
#define _MAIN_H_

#include <avr/io.h>

void init_counter(void);
void reset_counter(void);
void dial_1(void);
void dial_2(void);
void dial_3(void);
void dial_4(void);
void dial_5(void);
void dial_6(void);
void dial_7(void);
void dial_8(void);
void dial_9(void);
void dial_10(void);
void dial_red(void);
void dial_green(void);
void dial_ok(void);
void dial_okamStart(void);
void startup(void);
uint8_t getDigit(void);
uint8_t getGabelState(void);

#endif
