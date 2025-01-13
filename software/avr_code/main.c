#define __AVR_ATmega88__
#include <math.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#define PI 3.141592653589793
unsigned char zn = 51;
unsigned char zp = 17;
unsigned char R = 5; // mm
/*float unitcycle = (360 / 2048);*/
/*float unitcycle = 360 / 2048;*/
float unitcycle = 0.175781;
/*float unitcycleradious = (2 * PI * R) / 2048;*/
float unitcycleradious = (10 * PI) / 2048; // mm
volatile unsigned int angular_cycle;
volatile unsigned int radious_cycle = 2048;
volatile unsigned char c = 1;
volatile unsigned char d = 1;
unsigned char time = 230;
/*unsigned char w1 = 1;*/
/*unsigned char w2 = 1;*/

void cycle_radious_motor(float final_radius) {
  float result = final_radius / unitcycleradious;
  radious_cycle = (unsigned int)round(result);
};

void cycle_angular_motor(float final_angle) {
  float result = final_angle / unitcycle;
  angular_cycle = (unsigned int)round(result);
};

ISR(TIMER0_OVF_vect) {
  if (angular_cycle) {
    if (c == 8) {
      c = 1;
    } else {
      c = (c << 1);
    }
    angular_cycle -= 1;
  }
  if (radious_cycle) {
    if (d == 8) {
      d = 1;
    } else {
      d = (d << 1);
    }
    radious_cycle -= 1;
  }
  TCNT0 = time;
}

int main(void) {
  DDRC = 0xFF;
  DDRD = 0xFF;
  cycle_radious_motor(PI * 10);
  cycle_angular_motor(90);
  // Timer1 set up
  TCNT0 = time;
  TCCR0B = 5; // Clock with 1024.
  TIMSK0 = (1 << TOIE0);
  sei();
  while (1) {
    PORTC = c;
    PORTD = d;
  }
}
