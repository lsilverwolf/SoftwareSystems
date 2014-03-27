/*
  

 Author: Allen Downey 
 
 Based on http://arduino.cc/en/Tutorial/AnalogInput
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe

 License: Public Domain
 
 */
 
//#include <TimerOne.h>
//#include "TimerOne.h"
 
int ledPin = 5;       // select the pin for the LED
int buttonPin1 = 2;
int buttonPin2 = 3;
boolean toggle0 = 0;

void setup() {
  Serial.begin(9600);
//  
  pinMode(buttonPin1, INPUT_PULLUP);  
  pinMode(buttonPin2, INPUT_PULLUP);  
  DDRD = DDRD | B11100000;  // digital pins 7,6,5,4,3,2,1,0
  DDRB = B00111111;  // digital pins -,-,13,12,11,10,9,8
//  Timer1.initialize(100000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
//  Timer1.attachInterrupt( timerIsr ); // attach the service routine here

// initialize timer1 
  noInterrupts();           // disable all interrupts
//set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 300;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  interrupts();             // enable all interrupts

}

void writeByte(int x) {

  int Dpins = B00000011;
  int Bpins = B11111100;
  int Dset_pins = x & Dpins;
  int Bset_pins = x & Bpins;
  Dset_pins <<=6;
  Bset_pins >>=2;
  PORTB = Bset_pins;
  PORTD = Dset_pins | B00000100;
}

byte bitswap (byte x)
{
  byte result;
 
    asm("mov __tmp_reg__, %[in] \n\t"
      "lsl __tmp_reg__  \n\t"   /* shift out high bit to carry */
      "ror %[out] \n\t"  /* rotate carry __tmp_reg__to low bit (eventually) */
      "lsl __tmp_reg__  \n\t"   /* 2 */
      "ror %[out] \n\t"
      "lsl __tmp_reg__  \n\t"   /* 3 */
      "ror %[out] \n\t"
      "lsl __tmp_reg__  \n\t"   /* 4 */
      "ror %[out] \n\t"
 
      "lsl __tmp_reg__  \n\t"   /* 5 */
      "ror %[out] \n\t"
      "lsl __tmp_reg__  \n\t"   /* 6 */
      "ror %[out] \n\t"
      "lsl __tmp_reg__  \n\t"   /* 7 */
      "ror %[out] \n\t"
      "lsl __tmp_reg__  \n\t"   /* 8 */
      "ror %[out] \n\t"
      : [out] "=r" (result) : [in] "r" (x));
      return(result);
}

int low = 36;
int high = 255;
int stride = 5;
int counter = low;


ISR(TIMER0_COMPA_vect)          // timer compare interrupt service routine
{
  int button2 = digitalRead(buttonPin2);
  if (button2) return;  
  counter += stride;
  if (counter > high) {
    counter = low;
  }
  
  counter = bitswap(counter);
  writeByte(counter);
}

ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  int button1 = digitalRead(buttonPin1);
  if (button1) return;  
  counter += stride;
  if (counter > high) {
    counter = low;
  }
  
  counter = bitswap(counter);
  writeByte(counter);
}

void loop() {
    
  }
