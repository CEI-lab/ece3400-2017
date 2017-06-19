/*
fft_adc_serial.pde
guest openmusiclabs.com 7.7.14
example sketch for testing the fft library.
it takes in data on ADC0 (Analog0) and processes them
with the fft. the data is sent out over the serial
port at 115.2kb.
*/

#define LOG_OUT 1 // use the log output function
#define FFT_N 256 // set to 256 point fft
#define LED 2
//Default ADC sampling is 16MHz/(128 prescaler*13 bits) = 9600Hz
//Actual sampling speed as measured by ShowInfo: 8928kHz
//bin size: Fs/FFT_N = 9600/(256/2) = 75Hz

#include <FFT.h> // include the library

void setup() {
  Serial.begin(115200); // use the serial port
  TIMSK0 = 0; // turn off timer0 for lower jitter
  DIDR0 = 0x01; // turn off the digital input for adc0
  pinMode(LED, OUTPUT);
}

void loop() {
  while(1) { // reduces jitter
    cli();  // UDRE interrupt slows this way down on arduino1.0
    analogWrite(11, 100);
    digitalWrite(LED, HIGH);
    for (int i = 0 ; i < 512 ; i += 2) { // save 256 samples
      /*
      //This code restarts the ADC every time (by writing 1 to ADEN (MSB in ADCSRA)), it then takes 25 clock cycles to make a conversion, instead of 13!
      //Check the actual frequency, crystals aren't accurate!
      while(!(ADCSRA & 0x10)); // wait for adc to be ready
      ADCSRA = 0xf5; // clear done flag
      byte m = ADCL; // fetch adc data
      byte j = ADCH;
      int k = (j << 8) | m; // form into an int
      k -= 0x0200; // form into a signed int
      k <<= 6; // form into a 16b signed int
      */
      int k = analogRead(A0);
      fft_input[i] = k; // put real data into even bins
      fft_input[i+1] = 0; // set odd bins to 0
    }
    fft_window(); // window the data for better frequency response
    fft_reorder(); // reorder the data before doing the fft
    fft_run(); // process the data in the fft
    fft_mag_log(); // take the output of the fft
    digitalWrite(LED, LOW);
    sei();
    Serial.println("start");
    for (byte i = 0 ; i < FFT_N/2 ; i++) { 
      Serial.println(fft_log_out[i]); // send out the data
    }
  }
}


