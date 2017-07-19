#include <SPI.h>

// Note: You should be able to easily extend this code with radio functionality to send data
// you read from the radio over SPI.

// The radio uses pin 10 (the other slave select pin on the Arduino)
const int FPGA_SS = 4;

unsigned int pack_payload(char x, char y) {
  // Top 4 bits are y and bottom 4 bits are x
  return (y << 4) | x;
}

void digitalFPGAWrite(unsigned char value) {
  digitalWrite(FPGA_SS, LOW);
  SPI.transfer(value); // send a byte over SPI
  digitalWrite(FPGA_SS, HIGH);
}

void setup() {
  pinMode(FPGA_SS, OUTPUT);
  digitalWrite(FPGA_SS, HIGH);
  SPI.begin();
  SPI.beginTransaction(SPISettings(8000000,MSBFIRST,SPI_MODE0));

  Serial.begin(9600); // for debugging
}

void loop() {
  unsigned char x, y;
  unsigned char payload;
/*
  // Send the same packet every second.
  payload = pack_payload(1, 3);
  digitalFPGAWrite(payload);
  delay(3000);
*/
  // Iterate over all maze positions, sending a new one every second.
  Serial.println("Iterating through maze positions.\n");
  for (x = 0; x < 4; x++) {
    for (y = 0; y < 5; y++) {
      // Construct and send a test payload.
      // Note that this only works because the dimensionality of our maze restricts
      // x and y to be less than 4 bits.
      payload = pack_payload(x, y);
      Serial.println(payload); // print payload to serial
      digitalFPGAWrite(payload);
      delay(1000);
    }     
  }
}
