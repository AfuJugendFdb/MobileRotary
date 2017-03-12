#include <avr/io.h>
#include <util/delay.h>

void init_counter(void) {
    TCCR0 |= (1<<CS02) | (1<<CS01) | (0<<CS00);
    //Externe Clock-Source Rising-Edge
}

void reset_counter(void) {
    TCNT0 = 0x00;
}



void dial_1(void) {
    PORTB |= (1<<PB1) | (1<<PB6);
    _delay_ms(200);
    PORTB = 0x00;
}

void dial_2(void) {
    PORTB |= (1<<PB1) | (1<<PB7);
    _delay_ms(200);
    PORTB = 0x00;
}

void dial_3(void) {
    PORTB |= (1<<PB1) | (1<<PB5);
    _delay_ms(200);
    PORTB = 0x00;
}

void dial_4(void) {
    PORTB |= (1<<PB2) | (1<<PB6);
    _delay_ms(200);
    PORTB = 0x00;
}

void dial_5(void) {
    PORTB |= (1<<PB2) | (1<<PB7);
    _delay_ms(200);
    PORTB = 0x00;
}

void dial_6(void) {
    PORTB |= (1<<PB2) | (1<<PB5);
    _delay_ms(200);
    PORTB = 0x00;
}

void dial_7(void) {
    PORTB |= (1<<PB3) | (1<<PB6);
    _delay_ms(200);
    PORTB = 0x00;
}

void dial_8(void) {
    PORTB |= (1<<PB3) | (1<<PB7);
    _delay_ms(200);
    PORTB = 0x00;
}

void dial_9(void) {
    PORTB |= (1<<PB3) | (1<<PB5);
    _delay_ms(200);
    PORTB = 0x00;
}

void dial_10(void) {
    PORTB |= (1<<PB4) | (1<<PB7);
    _delay_ms(200);
    PORTB = 0x00;
}

void dial_red(void) {
    PORTB |= (1<<PB0) | (1<<PB6)
}

void dial_green(void) {
    PORTB |= (1<<PB0) | (1<<PB5)
}


uint8_t getDigit(void) {
    uint8_t counter_prim = 0;
    uint8_t counter_sec = 0;
    
    reset_counter();
    
    while (TCNT0 == 0); //Endlosschleife solange Counter == 0, "Ruhezustand"
    //Ab hier ist eine Registeränderung bekannt
    
    do {
        counter_prim = TCNT0;
        _delay_ms(1000);
        counter_sec = TCNT0;
        if(counter_sec > 10)
            reset_counter();
    } while (counter_prim != counter_sec);
    return counter_sec;
}

int main(void) {
    
    DDRB = 0xff;
    PORTB = 0x00;
    DDRD = 0x00;
    
    init_counter();
    
    while(1) {
        uint8_t digit = getDigit();
        //digit schreiben auf Telefon
        switch (digit) {
            case 1:
                dial_1();
                break;
            case 2:
                dial_2();
                break;
            case 3:
                dial_3();
                break;
            case 4:
                dial_4();
                break;
            case 5:
                dial_5();
                break;
            case 6:
                dial_6();
                break;
            case 7:
                dial_7();
                break;
            case 8:
                dial_8();
                break;
            case 9:
                dial_9();
                break;
            case 10:
                dial_10();
                break;
        }
        
    }
}

int debug(void) {
    DDRB = 0xff;
    PORTB = 0x00;
    while(1) {
        dial_1();
        _delay_ms(2000);
        dial_2();
        _delay_ms(2000);
        dial_3();
        _delay_ms(2000);
        dial_4();
        _delay_ms(2000);
        dial_5();
        _delay_ms(2000);
        dial_6();
        _delay_ms(2000);
        dial_7();
        _delay_ms(2000);
        dial_8();
        _delay_ms(2000);
        dial_9();
        _delay_ms(2000);
    }
}
