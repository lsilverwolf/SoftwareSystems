/*
  

 Author: Allen Downey 
 
 Based on http://arduino.cc/en/Tutorial/AnalogInput
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe

 License: Public Domain
 
 */
 
 
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
//  pinMode(ledPin, OUTPUT);
//  
//  pinMode(13, OUTPUT);  
//  pinMode(12, OUTPUT);  
//  pinMode(11, OUTPUT);  
//  pinMode(10, OUTPUT);  
//  pinMode(9, OUTPUT);  
//  pinMode(8, OUTPUT);  
//  pinMode(7, OUTPUT);  
//  pinMode(6, OUTPUT);  

  cli();//stop interrupts

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
  
  sei();
}

void writeByte(int x) {

  
//  x <<= 2;
//  int Dpins = B00000011;
//  int Bpins = B11111100;
//  int Dset_pins = x & Dpins;
//  int Bset_pins = x & Bpins;
//  Dset_pins <<=6;
//  PORTB = Bset_pins, BIN;
//  PORTD = Dset_pins, BIN;
// write to the digital pins  

    int pin;
    for (pin=13; pin>=6; pin--) {
      digitalWrite(pin, x&1);
      x >>= 1;
    }
    
}

int low = 36;
int high = 255;
int stride = 5;
int counter = low;

void loop() {
  int button1 = digitalRead(buttonPin1);
  if (button1) return;
  
  counter += stride;
  if (counter > high) {
    counter = low;
  }

  writeByte(counter);
}
