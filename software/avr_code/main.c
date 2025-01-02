#define __AVR_ATmega88__
#include <avr/interrupt.h>
#include <avr/io.h>
unsigned char zn = 51;
unsigned char zp = 17;
float unitcycle = 5.625;
volatile unsigned char angular_cycle;
volatile unsigned char radious_cycle = 20;
volatile unsigned char b = 1;
volatile unsigned char d = 1;
unsigned char w1 = 15;
unsigned char w2 = 15;
unsigned char R = 5;

void cycle_radious_motor(float final_radius) {
  float result = final_radius * (unitcycle / (360 * 2 * 3.14159265 * R));
  radious_cycle = (unsigned char)result;
};

void cycle_angular_motor(float final_angle) {
  float result = final_angle / unitcycle;
  angular_cycle = result;
};

ISR(TIMER0_OVF_vect) {
  TCNT0 = 0x55;
  if (angular_cycle > 0) {
    if (b == 8) {
      b = 1;
    } else {
      b = (b << 1);
    }
    angular_cycle -= 1;
  } else {
    TIMSK0 = 0;
  }
}

ISR(TIMER2_OVF_vect) {
  TCNT2 = 0x55;
  if (radious_cycle > 0) {
    if (d == 8) {
      d = 1;
    } else {
      d = (d << 1);
    }
    radious_cycle -= 1;
  } else {
    TIMSK2 = 0;
  }
}

int main(void) {
  DDRB = 0xFF;
  /*Timer1*/
  TCNT0 = 0x55; // From 0 to FF
  TCCR0B = 5;   // Clock with no prescalar.
  TIMSK0 = 1;
  cycle_angular_motor(unitcycle * 4);
  /*cycle_radious_motor(unitcycle * 10);*/
  /*Timer2*/
  TCNT2 = 0x55;
  TCCR2B = 5;
  TIMSK2 = 1;
  sei();
  while (1) {
    PORTB = b;
    PORTD = d;
  }
}
