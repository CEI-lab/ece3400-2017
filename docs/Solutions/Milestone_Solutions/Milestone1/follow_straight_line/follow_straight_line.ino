/**
 * ECE3400 Fall 2017
 * TA solution for Milestone 1: Line following 
 */

#include <Servo.h>

// Servo speed definitions
#define SERVO_BRAKE          90
#define SERVO_L_FORWARD_MAX  100.0
#define SERVO_R_FORWARD_MAX  80.0
#define SERVO_L_INCR_FORWARD 2.0
#define SERVO_R_INCR_FORWARD -2.0

// Thresholds for each sensor to determine when over a line
#define RIGHT_PID_THRESH     900
#define LEFT_PID_THRESH      900
#define RIGHT_TURN_THRESH    700
#define LEFT_TURN_THRESH     700

#define ERROR_RANGE          100

// Servo objects
Servo left_servo;
Servo right_servo;

// Inputs on mux
#define rightWall  6
#define leftWall   5
#define frontWall  7
#define right_pid  3
#define left_pid   2
#define right_turn 4
#define left_turn  1

// Control variables for line following
float error           = 0;
float error_magnitude = 0;
int   counter         = 0;

// Line sensor values
int right_pid_val     = 0; 
int left_pid_val      = 0;
int right_turn_val    = 0;
int left_turn_val     = 0;

// Servo turn values
float servo_turn_value[]   = {SERVO_R_FORWARD_MAX, 0 ,SERVO_L_FORWARD_MAX, SERVO_L_FORWARD_MAX};
int   servo_turn_delays [] = {300, 0, 300, 900};

// Mux pins
const int selectPins[3] = {8, 2, 4}; // Mux select signals S0~8, S1~2, S2~4
const int zInput        = A0;        // Connect common (Z) to A0 (analog input)

/* 
 * Read analog value from mux 
 * Returns int
 */
int muxRead(byte pin){
  selectMuxPin(pin);
  return analogRead(zInput);
}

// The selectMuxPin function sets the S0, S1, and S2 pins
// accordingly, given a pin from 0-7.
void selectMuxPin(byte pin){
  for (int i=0; i<3; i++){
    if (pin & (1<<i))
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }
}

/**
 * function move() 
 * follows a line
 **/
void move(){
      right_turn_val = muxRead(right_turn); //signal from center right sensor
      left_turn_val = muxRead(left_turn); //signal from center left sensor    


    // Read analog values from two center sensors
    right_pid_val = muxRead(right_pid); // signal from center right sensor
    left_pid_val = muxRead(left_pid);   // signal from center left sensor  

    // Print statements for debugging
      //Serial.println(right_pid_val);
      //Serial.println(left_pid_val);  
      //Serial.println();  
      
    error = left_pid_val - right_pid_val; // Positive position to right of line

    // Correct robot's driving direction according to position error
    if (abs(error) <= ERROR_RANGE){
      left_servo.write(SERVO_L_FORWARD_MAX);
      right_servo.write(SERVO_R_FORWARD_MAX);
    }
    
    // Robot is too right
    else if (error > ERROR_RANGE) {
      // Adjust left
      error_magnitude = abs(error)/(float)ERROR_RANGE;
      left_servo.write(SERVO_L_FORWARD_MAX - error_magnitude*SERVO_L_INCR_FORWARD);
      right_servo.write(SERVO_R_FORWARD_MAX + error_magnitude*SERVO_R_INCR_FORWARD);
    }
    // Robot is too left of line
    else if (error < -(ERROR_RANGE)) {
      // Adjust right
      error_magnitude = abs(error)/(float)ERROR_RANGE;
      left_servo.write(SERVO_L_FORWARD_MAX + error_magnitude*SERVO_L_INCR_FORWARD);
      right_servo.write(SERVO_R_FORWARD_MAX - error_magnitude*SERVO_R_INCR_FORWARD);
    }
    delay(10);
}

void setup() {
   // Begin Serial monitor
   Serial.begin(9600);
   
   // Connect servos 
  right_servo.attach(3); 
  left_servo.attach(5);
  
  // Set up the select pins as outputs:
  for (int i=0; i<3; i++)
  {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], HIGH);
  }
  pinMode(zInput, INPUT); // Set up Z (muxout) as an input

 // Brake servos
  right_servo.write(SERVO_BRAKE);
  left_servo.write(SERVO_BRAKE);
  
  Serial.println("initialized");

  // Wait at start for 1 second
  delay(1000);
}

void loop() {
  
  move();
}
