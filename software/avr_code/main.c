#define __AVR_ATmega88__
#include <avr/interrupt.h>
#include <avr/io.h>
unsigned char zn = 51;
unsigned char zp = 17;
float unitcycle = 5.625;
volatile unsigned char angular_cycle;
volatile unsigned char counter1 = 0;
volatile unsigned char counter2 = 0;
volatile unsigned char radious_cycle;
volatile unsigned char c = 1;
volatile unsigned char d = 1;
/*unsigned char w1 = 1;*/
/*unsigned char w2 = 1;*/
unsigned char R = 5;

void cycle_radious_motor(float final_radius) {
  float result = final_radius * (unitcycle / (2 * 3.14159265 * R));
  radious_cycle = (unsigned char)result;
};

void cycle_angular_motor(float final_angle) {
  float result = final_angle / unitcycle;
  angular_cycle = result;
};

ISR(TIMER0_OVF_vect) {
  if (angular_cycle > 0 && counter1 == 1) {
    counter1 = 0;
    if (c == 8) {
      c = 1;
    } else {
      c = (c << 1);
    }
    angular_cycle -= 1;
  }
  if (radious_cycle > 0 && counter2 == 1) {
    counter2 = 0;
    if (d == 8) {
      d = 1;
    } else {
      d = (d << 1);
    }
    radious_cycle -= 1;
  }
  counter1 += 1;
  counter2 += 1;
  TCNT0 = 253;
}

int main(void) {
  DDRC = 0xFF;
  DDRD = 0xFF;
  /*Timer1*/
  cycle_radious_motor(90000);
  cycle_angular_motor(90000);
  TCNT0 = 253;
  TCCR0B = 5; // Clock with 1024.
  TIMSK0 = (1 << TOIE0);
  /*OCR0A = 255;*/
  /*OCR0B = 50;*/
  sei();
  while (1) {
    PORTC = c;
    PORTD = d;
  }
}
