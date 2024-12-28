#include <avr/io.h>
#include <avr/interrupt.h>
unsigned char zn = 51;
unsigned char zp = 17;
volatile unsigned long radious_time; //segundos
volatile unsigned long angular_time; //segundos
float w1 = 50*3.14159265/180.0;
unsigned char w2 = 15;
unsigned char R = 5;

void SinglePhaseControl(unsigned int angular_velocity, volatile uint8_t* port) {
  // TODO: speed and direction implementation.
  unsigned int i;
  for (i = 0; i < 4; i++) {
    *port = (1 << i);
  }
  /*delay();*/
}

void time_radius_motor(unsigned char final_radius) { //Microseconds 
  float time_r = (float) final_radius/(w1*R);
  radious_time = (unsigned long)time_r*1000000;
}

void time_angle_motor(float final_angle) { //Microseconds 
  float relation = (float)zp/zn;
  float time_a = final_angle/(relation*w2);
  angular_time = (unsigned long)time_a*1000000;
}

ISR(TIMER0_OVF_vect) { 
  TCNT0 = 56;
  if (radious_time > 0) radious_time -= 200;
  if (angular_time > 0) angular_time -= 200;
}

int main(void) {
  DDRB = 0xFF;
  DDRC = 0xFF;
  time_radius_motor(20);
  time_angle_motor(10);
  TCNT0 = 56; // Check the actual time
  TCCR0B = 2; // Prescalar of clk/8
  TIMSK0 = 1; // Overflow flag
  sei();
  while (1) {
    if (radious_time != 0) {
      SinglePhaseControl(3, &PORTB);
    } else {
      PORTB = 0;
    }
    if (angular_time != 0) {
      SinglePhaseControl(3, &PORTC);
    } else {
      PORTC = 0;
    }
  }
  return 0;
}
