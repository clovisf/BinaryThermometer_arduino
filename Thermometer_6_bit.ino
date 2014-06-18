// Arduino timer CTC interrupt example (timer), from www.engblaze.com
// This example is a binary meter - shows a analog value in a binary (6-bit) output
// Modified by Clovis Fritzen, to fit as a binary thermomter (in may/2014)
 
// avr-libc library includes
#include <avr/io.h>
#include <avr/interrupt.h>
 
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor (LM35)
byte binaryValue= B00000000; // initialize port value as zeros

void setup()
{
    DDRB = DDRB | B00111111; // set 6 pins in port B as outputs
    
    // initialize Timer1
    cli();          // disable global interrupts
    TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B
 
    // set compare match register to desired timer count:
    OCR1A = 15624; // for temperature
    // turn on CTC mode:
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler:
    TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS12);
    // enable timer compare interrupt:
    TIMSK1 |= (1 << OCIE1A);
    // enable global interrupts:
    sei();
}
 
void loop()
{
    // You would put another stuff program here
}
 
ISR(TIMER1_COMPA_vect)
{
  // read the value from the sensor  :
  sensorValue = analogRead(sensorPin);
  //digitalValue= sensorValue;
  binaryValue= byte(sensorValue/2);
  PORTB = binaryValue; 
}
