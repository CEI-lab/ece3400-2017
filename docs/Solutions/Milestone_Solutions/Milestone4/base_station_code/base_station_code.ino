/*
  ECE 3400 Team 3 Arduino to FPGA SPI Transfer

 The circuit:
  * CS Radio - to digital pin 10  (SS pin)
  * CS FPGA - to digital pin 4  (SS pin)
  * SDI - to digital pin 11 (MOSI pin)
  * CLK - to digital pin 13 (SCK pin)
*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

// set pin 4 as the slave select for the FPGA SPI channel:
// The radio defaults to using pin 10 for slave select
const int fpga_SS = 4;
const int radio_SS = 10;

// Constants to help with reading data from bytes
#define  WALL_UP 1
#define  WALL_DOWN 2
#define  WALL_LEFT 4
#define  WALL_RIGHT 8
#define  NO_TREASURE 0
#define  KHZ_7 1
#define  KHZ_9 2
#define  KHZ_11 3
#define  KHZ_13 4
#define  KHZ_15 5
#define  KHZ_17 6
#define  FINISHED 128

// Global variables
uint8_t treasure = 0;
bool finished = 0;
uint8_t rxInfo[2] ={0};
uint8_t real_x;
uint8_t real_y;
uint8_t real_pos;
uint16_t current_data;
uint16_t prev_data;

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10
RF24 radio(9,10);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0x000000000CLL, 0x000000000DLL };

// Role management
// The various roles supported by this sketch
typedef enum { role_ping_out = 1, role_pong_back } role_e;

// The debug-friendly names of those roles
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};

// The role of the current running sketch
role_e role = role_pong_back;

void setup() {
  Serial.begin(9600); // for printing debug information to the serial console
  printf_begin();

  // set the CS pins as outputs and init as high (inactive)
  pinMode(fpga_SS, OUTPUT);
  pinMode(radio_SS, OUTPUT); 
  digitalWrite(fpga_SS, HIGH);
  digitalWrite(radio_SS, HIGH);

  // initialize SPI:
  SPI.begin();

  // Setup and configure rf radio
  radio.begin();
  // set the delay between retries & # of retries
  radio.setRetries(15,15);
  radio.setAutoAck(true);
  // set the channel
  radio.setChannel(0x50);
  // set the power
  // RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MED=-6dBM, and RF24_PA_HIGH=0dBm.
  radio.setPALevel(RF24_PA_MAX);
  //RF24_250KBPS for 250kbs, RF24_1MBPS for 1Mbps, or RF24_2MBPS for 2Mbps
  radio.setDataRate(RF24_2MBPS);

  // Open 'our' pipe for writing
  // Open the 'other' pipe for reading, in position #1 (we can have up to 5 pipes open for reading)
  if ( role == role_ping_out ) {
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);
  } else {
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1,pipes[0]);
  }
  radio.startListening();

  // Dump the configuration of the rf unit for debugging
  // radio.printDetails();
}

// Used to send data over SPI to the FPGA
void digitalFPGAWrite(int value) {
  // Set the FPGA SS pin low to select the chip:
  digitalWrite(fpga_SS, LOW);
  // Transfers the value out MOSI
  SPI.transfer16(value);
  // Set the FPGA SS pin high to de-select the chip:
  digitalWrite(fpga_SS, HIGH);
}

void loop() {
  int curr_x = 0; 
  int curr_y = 0; 
  bool wall_left = 0;
  bool wall_right = 0;
  bool wall_up = 0;
  bool wall_down = 0;
  int i = 0;
  int j = 0;

  // Pong back role--Receive each packet
  if ( role == role_pong_back ) {
    // if there is data ready
    if ( radio.available() ) {
      // Dump the payloads until we've gotten everything
      bool done = false;
      while (!done) {
        // Fetch the payload, and see if this was the last one.
        done = radio.read( rxInfo, sizeof(rxInfo) );

        // Print it
        printf("Recieved %x and %x\n", rxInfo[0], rxInfo[1]);

        // Delay to let the other unit make the transition to receiver
        delay(10);
      }

      // First, stop listening so we can talk
      radio.stopListening();

      // Send the ack
      radio.write(&rxInfo, sizeof(rxInfo));
      printf("Sent response.\n\r");
      
      // Parse data from packet
      curr_y = (rxInfo[0] & 0x0F);
      curr_x = ((rxInfo[0]>> 4) & 0x0F);
      wall_up = rxInfo[1] & WALL_UP;
      wall_down = rxInfo[1] & WALL_DOWN;
      wall_left = rxInfo[1] & WALL_LEFT;
      wall_right = rxInfo[1] & WALL_RIGHT;
      treasure = (rxInfo[1] >> 4) & 0x07;
      finished = rxInfo[1] & FINISHED;

      printf("x,y: %d, %d \n up: %d \ndown: %d \nleft: %d \nright: %d\n", curr_x, curr_y, wall_up, wall_down, wall_left, wall_right);
      printf ("treasure = %d and finished = %d\n", treasure, finished);

      // Map from x,y used for mapping to x,y used for FPGA
      real_x = 3-curr_y;
      real_y = 4-curr_x;
      real_pos = ((real_x << 4) | real_y);
      current_data = ((rxInfo[1] << 8) | real_pos);

      // Send new data over to FPGA
      if (prev_data != current_data) {
        digitalFPGAWrite(current_data);
      }
      prev_data = current_data;

      // Now, resume listening so we catch the next packets.
      radio.startListening();
    }
  }
}

