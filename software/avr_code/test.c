#define F_CPU 8000000UL
#define __AVR_ATmega88__
#include <avr/interrupt.h>
#include <avr/io.h>

volatile unsigned char steps = 92;
unsigned char time = 0x00;
volatile unsigned char d = 1;

ISR(TIMER0_OVF_vect) {
  if (steps != 0) {
    if (d == 8) {
      d = 1;
    } else {
      d = (d << 1);
    }
    steps -= 1;
  }
  TCNT0 = time;
}

int main(void) {
  DDRD = 0xFF;
  TCNT0 = time;
  TCCR0B = 3; // Clock with 1024.
  TIMSK0 = (1 << TOIE0);
  sei();
  while (1) {
    PORTD = d;
  }
}
