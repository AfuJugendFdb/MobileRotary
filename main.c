#include <avr/io.h>
#include <util/delay.h>

uint8_t gabelState = 0; //aufgelegt

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
    PORTB |= (1<<PB0) | (1<<PB5);
    _delay_ms(500);
    PORTB = 0x00;
}

void dial_green(void) {
    PORTB |= (1<<PB6);
    PORTC |= (1<<PC5);
    _delay_ms(500);
    PORTB = 0x00;
    PORTC = 0x00;
}
void dial_ok(void) {
	PORTB |= (1<<PB7);
    PORTC |= (1<<PC5);
    _delay_ms(500);
    PORTB = 0x00;
    PORTC = 0x00;
	}
void startup(void){
	dial_1();
	_delay_ms(500);
	dial_1();
	_delay_ms(500);
	dial_1();
	_delay_ms(500);
	dial_1();
	_delay_ms(500);
	dial_ok();
}

uint8_t getDigit(void) {
    uint8_t counter_prim = 0;
    uint8_t counter_sec = 0;
    
    /*
    reset_counter();
    
    while (TCNT0 == 0); //Endlosschleife solange Counter == 0, "Ruhezustand"
    */
    if(TCNT0 == 0)
    {
		return 0xFF;
	}
	
	else
	{
		//Ab hier ist eine Registeränderung bekannt
		
		do {
			counter_prim = TCNT0;
			_delay_ms(1000);
			counter_sec = TCNT0;
			if(counter_sec > 10)
				reset_counter();
		} while (counter_prim != counter_sec);
		reset_counter();
		return counter_sec;
	}
}

uint8_t getGabelState(void)
{
	//Gabel an PD3 auf 1?
	if((PIND & (1 << PD3)) != 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int main(void) {
    
    DDRB = 0xff;	//Matrix
    DDRD = 0x00;	//Scheibe
    DDRC = 0xff;	//Gabel
    PORTB = 0x00;
    PORTC = 0x00;
    
    init_counter();
    startup();
    
    
    while(1) {
		
		uint8_t currentGabel = getGabelState();
        if(gabelState != currentGabel)
        {
			//Gabel hat sich geändert
			//neuen Zustand als alten speichern, um nur Änderung des Zustandes zu erkennen
			gabelState = currentGabel;
			
			if(currentGabel == 1)
			{
				//abgehoben
				dial_green();
			}
			else
			{
				//aufgelegt
				dial_red();
			}
		}
        
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
