#define F_CPU 8000000UL
#define __AVR_ATmega88__
/*#include <avr/interrupt.h>*/
#include <avr/io.h>
#include <util/delay.h>

volatile unsigned char b = 1;

int main(void) {
  DDRC = 0xFF;
  unsigned char i;
  while (1) {
    b = 1;
    for (i = 1; i < 5; i++) {
      PORTC = b;
      b = (b << 1);
      _delay_ms(0.5);
    }
  }
  return 0;
}
