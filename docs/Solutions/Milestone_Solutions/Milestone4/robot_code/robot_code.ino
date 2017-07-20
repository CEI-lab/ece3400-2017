#include <SPI.h>
#include <Servo.h>

#include "nRF24L01.h"
#include "RF24.h"

// Servo speed definitions
#define SERVO_BRAKE 90
#define SERVO_L_FORWARD_MAX 100.0
#define SERVO_R_FORWARD_MAX 80.0
#define SERVO_L_INCR_FORWARD 2.0
#define SERVO_R_INCR_FORWARD -2.0

#define ROW_NUM 5
#define COL_NUM 4

// Servo objects
Servo left_servo;
Servo right_servo;

// Control variables for line following
float error = 0;
float error_magnitude = 0;
int counter = 0;
#define ERROR_RANGE 100

// Line sensor values
int right_pid_val = 0; 
int left_pid_val = 0;
int right_turn_val = 0;
int left_turn_val = 0;

// Servo turn values
float servo_turn_value[] = {SERVO_R_FORWARD_MAX,0,SERVO_L_FORWARD_MAX, SERVO_L_FORWARD_MAX};
int servo_turn_delays[] = {300,0,300,900};



#define LOG_OUT 1 // use the log output function
#define FFT_N 128 // set to 256 point fft
#define AMP_THRESHOLD 80
#define FFT_TRIGGER 3

#include <FFT.h> // include the library
int threshold = AMP_THRESHOLD;
int fft_counter = 0; //for false positives


// Variable that dictates way robot turns at intersection
//0 left, 1 straight, 2 right, 3 180
int direction = 1;

//Wall sensing 
const int selectPins[3] = {8, 2, 4}; // Mux select signals S0~2, S1~3, S2~4
const int zInput = A0; // Connect common (Z) to A4 (analog input)
//#define WALL_SENSOR_THRESHOLD 200
#define RIGHT_WALL_SENSOR_THRESHOLD 400
#define LEFT_WALL_SENSOR_THRESHOLD 220
#define FRONT_WALL_SENSOR_THRESHOLD 100

// Inputs on mux
#define rightWall 6
#define leftWall 5
#define frontWall 7
#define right_pid 3
#define left_pid 2
#define right_turn 4
#define left_turn 1

#define ledIndicator A5

// Wall sensor values
int rightWallVal = 0;
int leftWallVal = 0;
int frontWallVal = 0;
int wallsRadio = 0;

//#define WALL_FRONT_2 5 //1
//#define WALL_LEFT_2 12 //2
//#define WALL_RIGHT_2 6 //4

// LED pin
//#define ledIndicator //3

// Radio
#define  WALL_NORTH_2 1
#define  WALL_SOUTH_2 2
#define  WALL_WEST_2 4
#define  WALL_EAST_2 8
#define  NO_TREASURE 0
#define  KHZ_7 1
#define  KHZ_9 2
#define  KHZ_11 3
#define  KHZ_13 4
#define  KHZ_15 5
#define  KHZ_17 6
#define  FINISHED 128

//Radio values
//bool wallNorth = 0;
//bool wallSouth = 0;
//bool wallWest = 0;
//bool wallEast = 0;
uint8_t treasure = 0;
bool finished = 0;
char info[2] ={0};
uint8_t xPos;
uint8_t yPos;

// Radio Setup
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
role_e role = role_ping_out;

// PINS FOR TREASURE DETECTION
 int treasure_detection_pin = 6;
 int avg_val_pin = 7;
 //unsigned int period = 0;
 unsigned int treasure_freq = 0;
 int on  = 0;
 bool treas = false; // indicates whether the current intersection has treasure in the vicinity
 
// #define TREASURE_ARR_SIZE 15
 //uint8_t   treasure_arr[TREASURE_ARR_SIZE];
 volatile int treasure_index = 0;
// int freq_count_arr[7]; // 0 7 9 11 13 15 17  
 //volatile int num_times_interrupt_triggered = 0;
 volatile int period = 0;
 

bool manualOverride = false;
bool whistle = false;
#define PORT_D PIND
#define overridePin A3

 // Treasure detection ISR
 ISR(ANALOG_COMP_vect){
   treas = true;
   period  = TCNT2;
   
   ////Serial.println(period);
   /*if(num_times_interrupt_triggered == 150) {
     treasure_arr[treasure_index % TREASURE_ARR_SIZE] = period;
     treasure_index++;
     treasure_index %= TREASURE_ARR_SIZE;
     num_times_interrupt_triggered = 0;    
   }
   else {
     num_times_interrupt_triggered++;
   }*/

   ////Serial.println(period);
   if(!on) {
     digitalWrite(LED_BUILTIN, HIGH);
     on = 1;
   }
   else {
     digitalWrite(LED_BUILTIN, LOW);
     on = 0;
   }
   TCNT2 = 0;
 
 }

typedef enum {
  WALL_NORTH = 1, // 0001
  WALL_EAST  = 2, // 0010
  WALL_SOUTH = 4, // 0100
  WALL_WEST  = 8, // 1000
} MAZEINFO;

typedef enum { 
  /* Take a conservative approach: always assume there is a wall at the back.
   * Assuming there is not a wall at the back will bring errors when the robot is making 180 degree turns.
   */
  WALL_FRONT = 5,  // 0101
  WALL_RIGHT = 6,  // 0110
  WALL_LEFT  = 12, // 1100
} WALLINFO;

typedef enum {
  NORTH = 1, // 0001
  EAST  = 2, // 0010
  SOUTH = 4, // 0100
  WEST  = 8, // 1000
} ORIENTATION;

int maze[ROW_NUM][COL_NUM]; // Each index is a 4-bit int that stores the wall info of that particular grid. e.g. 1101
//int maze_cheatsheet[ROW_NUM][COL_NUM]; // Used for testing purposes only. Store the "hardcoded" wall infos into this matrix.
int orientation = NORTH; // The robot begins with facing north.
int cur_pos = 19; // The robot begins on grid #19.
int nex_pos; // This variable stores the location that the robot is planning to move to.
bool visited_info[20]; // Set to true if already visited
bool on_stack[20]; // Set to true if is on schedule (pused to stack)
int delta_N[5] = { 0,  1,  0, -1,  0}; // used for faster accesses to the four directions: prioritizes going North  
int delta_E[5] = { 1,  0, -1,  0,  1};   
int delta_S[5] = { 0, -1,  0,  1,  0};      
int delta_W[5] = {-1,  0,  1,  0, -1};
int stack[50]; // The stack that stores locations. Shouldn't be taller than 100 ints since there are only 20 grids.
int stack_ptr = 0; // A pointer that indexes the stack. The pointer points to the next empty slot.
int step_cnt = 0; // A counter that counts how many steps have been used.
bool done = 0; // A flag that will be set to 1 once the robot finishes traversing the whole maze, and 0 otherwise.
int known_walls[20];
int FOUND_TREASURE = 0;
 
/*
* Given a position from 0 to 19, this function returns the y-coordinate, 
* y ranges from 0 to 4.
*/
int gety(int pos) {
  return pos/4;
}

/*
* Given a position from 0 to 19, this function returns the x-coordinate.
* x ranges from 0 to 3.
*/ 
int getx(int id) {
  return id%4;
}

/*
* Given an x value and a y value, this function returns its id, ranging [0,20).
*/ 
int get_id(int x, int y) {
  return 4*y + x;
}

void stack_push(int pos) {
  stack[stack_ptr] = pos;
  on_stack[pos] = true;
  stack_ptr++;
}

bool stack_empty() {
  return (stack_ptr == 0);
}

int stack_top() {
  if (stack_empty()) return NULL;
  return stack[stack_ptr-1];
}

void stack_pop() {
  if (stack_empty()) return ;
  stack_ptr--;
}

void initialize_maze() {
  int m = ROW_NUM; int n = COL_NUM;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      maze[i][j] = 15; // 1111
    }
  }
}

void initialize_visited_info() {
  for (int i = 0; i < 20; i++) { // the length of this array is 20.
    visited_info[i] = false;
  }
}

void initialize_known_walls() {
  known_walls[0]  = 9; // 1001
  known_walls[1]  = 1; // 0001
  known_walls[2]  = 1; // 0001
  known_walls[3]  = 3; // 0011
  known_walls[4]  = 8; // 1000
  known_walls[5]  = 0; // 0000
  known_walls[6]  = 0; // 0000
  known_walls[7]  = 2; // 0010
  known_walls[8]  = 8; // 1000
  known_walls[9]  = 0; // 0000
  known_walls[10] = 0; // 0000
  known_walls[11] = 2; // 0010
  known_walls[12] = 8; // 1000
  known_walls[13] = 0; // 0000
  known_walls[14] = 0; // 0000
  known_walls[15] = 2; // 0010
  known_walls[16] = 12;// 1100
  known_walls[17] = 4; // 0100
  known_walls[18] = 4; // 0100
  known_walls[19] = 6; // 0110
}

void robot_go_straight() {
  // TODO: API
  //cout << "robot goes straight" << endl;
}

int my_shift_left(int input) { 
  // Only works for inputs that are 4-bit wide!
  int output = ((input << 1) & 15);
  output |= ((input >> 3) & 1);
  return output;
}

int my_shift_right(int input) { 
  // Only works for inputs that are 4-bit wide!
  int output = ((input >> 1) & 15);
  output |= ((input & 1) << 3);
  return output;
}

// Print the maze (the global maze[][]) in a friendly format.
void printmaze() {
  Serial.println("---------------------");
  for (int i = 0; i < ROW_NUM; i++) {
    for (int j = 0; j < COL_NUM; j++) {
      Serial.print(maze[i][j]);
    }
    Serial.println();
  }
  Serial.println("---------------------");
}

// Update maze[ROW_NUM][COL_NUM] with the wall sensors' readings (curr_wall_info).
void update_maze(int curr_wall_info) {
  int rel_pos = curr_wall_info; // relative wall position (to robot)
  // Update this grid in the maze array
  // Must first check robot's orientation since wall information is relative to the robot
  // At each grid space, current wall information applies to both current grid space and adjacents squares

  int curr_row;
  int curr_col;
  int glob_pos; // global wall position
  
  curr_row = gety(cur_pos);
  curr_col = getx(cur_pos);
   
  if (orientation == NORTH) {
    glob_pos = rel_pos & (11);
  }
  if (orientation == EAST) {
    // Need to round-shift the relative wall positions left to make them global positions
    glob_pos = my_shift_left((rel_pos & 11));
  }
  if (orientation == SOUTH) {
    glob_pos = my_shift_left(my_shift_left((rel_pos & 11)));
  }
  if (orientation == WEST) { 
    glob_pos = my_shift_right((rel_pos & 11));
  }

    // First update wall information for robot's current square
    maze[curr_row][curr_col] &= glob_pos; 

    // Next, update wall information for adjacent squares:
    // Update square to the North of current square if it's not at top edge of grid to have south wall if you sense north wall in current grid
    // Only want to update south wall information for North adjacent square
    if (curr_row > 0) maze[curr_row - 1][curr_col] |= ((int)(WALL_SOUTH) & (glob_pos << 2));
    // Update the grid to the West
    if (curr_col > 0) maze[curr_row][curr_col - 1] |= ((int)(WALL_EAST) & (glob_pos >> 2));
    // Update the grid to the East
    if (curr_col + 1 < COL_NUM) maze[curr_row][curr_col + 1] |= ((int)(WALL_WEST) & (glob_pos << 2));
    // Update the grid to the South
    if (curr_row + 1 < ROW_NUM) maze[curr_row + 1][curr_col] |= ((int)(WALL_NORTH) & (glob_pos >> 2));
}


// Print the stack for the depth-first search algorithm in an
// easy to read format. Helpful for debugging mapping algorithm.
void print_stack() { 
  if (stack_empty()) {
    Serial.println("stack is empty!");
    return ;
  }
  for (int i = stack_ptr - 1; i >= 0; i--) {
    //Serial.println("| " + stack[i] + " |");
    Serial.print("| ");
    Serial.print(stack[i]);
    Serial.println(" |");
    //Serial.println("|----|");
  }
}

// from and to should ONLY be ONE block away!
void move_one(int& from, int& to) { 
  ////Serial.print("moving from ");
  ////Serial.print(from);
  ////Serial.print(" to ");
  ////Serial.print(to);
  ////Serial.print('\n');

  int from_x = getx(from);
  int from_y = gety(from);
  int to_x = getx(to);
  int to_y = gety(to);
  int curr_wall_info = 0;
  
  if (from_x == to_x) { // moving along same col
    if (to_y == from_y) { // two locations are the same, do not move
      curr_wall_info = updateWalls();
    }  
    else if (to_y > from_y) { // move in positive direction (downwards)
      if (orientation == NORTH) curr_wall_info = move(3);
      if (orientation == EAST) curr_wall_info = move(2);
      if (orientation == SOUTH) curr_wall_info = move(1);
      if (orientation == WEST)  curr_wall_info = move(0);
      orientation = SOUTH;
    }
    else { // move in negative direction (upwards)
      if (orientation == NORTH) curr_wall_info = move(1);
      if (orientation == EAST) curr_wall_info = move(0);
      if (orientation == SOUTH) curr_wall_info = move(3);
      if (orientation == WEST)  curr_wall_info = move(2);
      orientation = NORTH;
    }
  }
  else { // moving vertically
    if (to_x > from_x) { // move in positive direction (rightwards)
      if (orientation == NORTH)  curr_wall_info = move(2);
      if (orientation == EAST)  curr_wall_info = move(1);
      if (orientation == SOUTH) curr_wall_info = move(0);
      if (orientation == WEST) curr_wall_info = move(3);
      orientation = EAST;
    }
    else { // move in negative direction (leftwards)
      if (orientation == NORTH)  curr_wall_info = move(0);
      if (orientation == EAST) curr_wall_info = move(3);
      if (orientation == SOUTH) curr_wall_info = move(2);
      if (orientation == WEST)  curr_wall_info = move(1);
      orientation = WEST;
    }
  }

  visited_info[from] = true;
  visited_info[to] = true;
  from = to; // update the location
  // //Serial.print("Current position is: ");
  // //Serial.println(cur_pos);
  
  if(FOUND_TREASURE) {
    treasure = 0;
  }
  else {
    treasure_freq = get_treasure_freq(); // Need this before send_my_radio, b/c this function populates treasure variable
    // //Serial.print("TREASURE FREQUENCY IS: ");
    FOUND_TREASURE = treasure_freq;
  
    ////Serial.println(treasure_freq);
  }
  update_maze(curr_wall_info);
  send_my_radio();
  // printmaze();
  
}

int send_my_radio() {
  //Radio values
bool wallNorth = 0;
bool wallSouth = 0;
bool wallWest = 0;
bool wallEast = 0;
// Ping out role
  if (role == role_ping_out) {

    Serial.println(cur_pos);
    int attempt = 0;

    xPos = getx(cur_pos);
    yPos = gety(cur_pos);
    wallNorth = maze[yPos][xPos] & 0x01;
    wallSouth = maze[yPos][xPos] & 0x04;
    wallWest = maze[yPos][xPos] & 0x08;
    wallEast = maze[yPos][xPos] & 0x02;

    Serial.print(wallEast);
    Serial.print(wallWest);
    Serial.print(wallSouth);
    Serial.println(wallNorth);
    

    info[1] = 0;
    info[0] = (((yPos << 4) & 0xF0) | (xPos & 0x0F));
    if ( wallNorth) info[1] |= WALL_NORTH_2;
    if ( wallSouth) info[1] |= WALL_SOUTH_2;
    if ( wallWest) info[1] |= WALL_WEST_2;
    if ( wallEast) info[1] |= WALL_EAST_2;
    if (treasure) info[1] |= (treasure << 4 & 0x70);
    if (finished) info[1] |= FINISHED;

    while ( attempt < 2 ) { //attempt to send three times
      // First, stop listening so we can talk.
      radio.stopListening();


      Serial.print("Now sending: ");Serial.print(info[0], HEX); Serial.print(" "); Serial.println(info[1], HEX);
//      printf("Now sending %d and %d.",info[0], info[1]);
      bool ok = radio.write( &info, sizeof(info) );

       if (ok)
         Serial.println("ok...");
       else {
        attempt+=1;
        continue;
//         Serial.println("failed.");
         // TODO: just continute?
       }

      // Now, continue listening
      radio.startListening();

      // Wait here until we get a response, or timeout (250ms)
      unsigned long started_waiting_at = millis();
      bool timeout = false;
      while ( ! radio.available() && ! timeout ) {
        if (millis() - started_waiting_at > 150 ) {
          timeout = true;
        }
      }
      
      // Describe the results
      if ( timeout ) {
//        printf("Failed, response timed out.\n\r");
      } else {
        // Grab the response, compare, and send to debugging spew
//        unsigned long got_time;
//        radio.read( &got_time, sizeof(unsigned long) );

        // Spew it
//        printf("Got response %lu, round-trip delay: %lu\n\r",got_time,millis()-got_time);
        // delay (2000);
        break;
      }
//       Try again 0.5s later
      delay(10);

      attempt+=1; // try again.
    }
   }

}

int get_treasure_freq() {
  //Serial.println("Treasure period: ");
  //Serial.println(period);
  int treasure_freq = 0;
  // Need this here, b/c need to give enough time at the intersection for the ISR to get called enough times
  if(treas) {
    treas = false;
    int max_count = 0;
    int max_index = 0;
    int period2 = 0;
    noInterrupts();
    //for(int i =0; i < TREASURE_ARR_SIZE; i++) {
      treasure = 0;
      period2 = period;
      //Serial.println(period2);
      
        if(period2 > 5 && period2 < 25) {
          // 7 kHZ
          treasure_freq = 7;
          treasure = KHZ_7;
          //walls |= (1 <<3);
        }
        else if(period2 >= 95 && period2 < 109) {
          // 17 kHz
          treasure_freq = 17;
          treasure = KHZ_17;
          //walls |= (6 <<3);
        }
        else if(period2 >= 110 && period2 < 129) {
          // 15 kHz
          treasure_freq = 15;
          treasure = KHZ_15;
          //walls |= (5 <<3);
        }
        else if(period2 >= 129 && period2 < 158) {
          // 13 kHz
          treasure_freq = 13;
          treasure = KHZ_13;
          //walls |= (4 <<3);
        }
        else if(period2 >= 158 && period2 < 185) {
          // 11
          treasure_freq = 11;
          treasure = KHZ_11;
          //walls |= (3 <<3);
        }
        else if (period2 >= 185 && period2 < 220) {
          // 9 khZ (~ 210 cycles)
          treasure_freq = 9;
          treasure = KHZ_9;
          //walls |= (2 <<3);
        }
        else {
          treasure_freq  = 0;
          treasure = 0;
        }
    }
    //Serial.print("The treasure freq is ");
    //Serial.println(treasure);
    interrupts();
    return treasure;
}


// The master function that let the robot traverse the maze.
void traverse() {
  int curr_row;
  int curr_col;
  int rel_walls;
  int next_pos;

  int glob_walls; // global wall position
  int go_north;
  int go_east;
  int go_west;
  int go_south;
  int all_visited = 0;
  int i;
  
  stack_push(cur_pos); // visit grid 19 initially
  int w = updateWalls();
  update_maze(w);
  send_my_radio();
  
  
  //print_stack();

  // Baseline DFS navigation algorithm
  while(!stack_empty() || all_visited) {
   
    cur_pos = stack_top();
    curr_row = gety(cur_pos);
    curr_col = getx(cur_pos);
    
    visited_info[cur_pos] = true;

    // find current wall information and translate it from relative to global
    rel_walls = updateWalls();
    Serial.print("relative wall loc: ");
    Serial.println(rel_walls);

    
    if (orientation == NORTH) {
      glob_walls = rel_walls & (11);
    }
    if (orientation == EAST) {
      // Need to round-shift the relative wall positions left to make them global positions
      glob_walls = my_shift_left((rel_walls & 11));
    }
    if (orientation == SOUTH) {
      glob_walls = my_shift_left(my_shift_left((rel_walls & 11)));
    }
    if (orientation == WEST) { 
      glob_walls = my_shift_right((rel_walls & 11));
    }

    Serial.print("global wall loc: ");
    Serial.println(glob_walls);
    
    // Determine where to go next based on wall location and visited information
    // Priority: N, E, W, S
    if ((glob_walls & WALL_NORTH) == 0) go_north = !(visited_info[get_id(curr_col, curr_row - 1)]);
    else go_north = 0;

    if ((glob_walls & WALL_EAST) == 0)  go_east  = !(visited_info[get_id(curr_col + 1, curr_row)]) & !go_north;
    else go_east  = 0;

    if ((glob_walls & WALL_WEST) == 0)  go_west =  !(visited_info[get_id(curr_col - 1, curr_row)]) & !go_east;
    else go_west = 0;

    if ((glob_walls & WALL_SOUTH) == 0)  go_south =  !(visited_info[get_id(curr_col, curr_row + 1)]) & !go_west;
    else go_south = 0;

    if (go_north){
      next_pos = get_id(curr_col, curr_row - 1);
      stack_push(next_pos);
    }
    else if (go_east){
      next_pos = get_id(curr_col + 1, curr_row);
      stack_push(next_pos);
    }
    else if (go_west){
      next_pos = get_id(curr_col - 1, curr_row);
      stack_push(next_pos);
    }
    else if (go_south){
      next_pos = get_id(curr_col, curr_row + 1);
      stack_push(next_pos);
    }
    else{
      stack_pop();

      if (stack_empty()){
        break;
      }
      next_pos = stack_top();
    }

    Serial.print("next_pos: ");
    Serial.println(next_pos);
    
    //print_stack();
    move_one(cur_pos, next_pos);

    // Determine if all nodes have been visited:
    all_visited = 1;
    for (i = 0; i < 20; i++) {
      all_visited = (all_visited & visited_info[i]);
    }

  } 
}
void initialize() {
  initialize_maze();
  initialize_visited_info();
  initialize_known_walls();
//  set_maze_cheatsheet();
}

/**
 * function move() is called from the navigation code after an intersection 
 * has been reached and the decision of what direction to go has been made
 * takes in a direction to move one block and 
 * a pointer to the array that stores wall sensor values (this probably doesn't need to be an argument, could be global)
 * wall sensor values are modified when the robot reaches the proscribed intersection
 direction: 0 if left, 1 if forward, 2 if right, 3 if 180
 **/
int move(int direction){

  //turn if requested
  if (direction != 1){
    // Start turning until off the current line
    left_servo.write(servo_turn_value[direction]);
    right_servo.write(servo_turn_value[direction]);
    delay(servo_turn_delays[direction]);

   // Read values from center line sensors
    right_pid_val = muxRead(right_pid);
    left_pid_val = muxRead(left_pid);

    // While center sensors are not over another line, continue turning
    while((right_pid_val<900) || (left_pid_val<900)){
    right_pid_val = muxRead(right_pid);
    left_pid_val = muxRead(left_pid);
    }
  }
    // Reset intersection variables  
    right_turn_val = 0;
    left_turn_val = 0;
    counter = 50;
    
  // After turn is complete, drive forward to the next intersection, making corrections as necessary
  // while-loop is all of line following
  while(right_turn_val<700 || left_turn_val<700){
    // Don't start searching for an intersection until the intersection sensors are clear of the tape line
    if (counter>0){
      right_turn_val = 0; //set so that while loop continues
      left_turn_val = 0; //set so that while loop continues 
      counter = counter - 1;
    }
    else {
      right_turn_val = muxRead(right_turn); //signal from center right sensor
      left_turn_val = muxRead(left_turn); //signal from center left sensor   
 
    }

    // Read analog values from two center sensors
    right_pid_val = muxRead(right_pid); // signal from center right sensor
    left_pid_val = muxRead(left_pid); // signal from center left sensor  
      //Serial.println(right_pid_val);
      //Serial.println(left_pid_val);  
      //Serial.println();  
    error = left_pid_val - right_pid_val; // Positive position to right of line
    if (abs(error) <= ERROR_RANGE){
      left_servo.write(SERVO_L_FORWARD_MAX);
      right_servo.write(SERVO_R_FORWARD_MAX);
    }
    // Too right
    else if (error > ERROR_RANGE) {
      // Adjust left
      error_magnitude = abs(error)/(float)ERROR_RANGE;
      left_servo.write(SERVO_L_FORWARD_MAX - error_magnitude*SERVO_L_INCR_FORWARD);
      right_servo.write(SERVO_R_FORWARD_MAX + error_magnitude*SERVO_R_INCR_FORWARD);
    }
    // Too left
    else if (error < -ERROR_RANGE) {
      // Adjust right
      error_magnitude = abs(error)/(float)ERROR_RANGE;
      left_servo.write(SERVO_L_FORWARD_MAX + error_magnitude*SERVO_L_INCR_FORWARD);
      right_servo.write(SERVO_R_FORWARD_MAX - error_magnitude*SERVO_R_INCR_FORWARD);
    }
    delay(10);
  }
  left_servo.write(SERVO_BRAKE);
  right_servo.write(SERVO_BRAKE);
  int w = updateWalls();
  ////Serial.println("walls: " + w);
  return w; 
}

//Update wall information
int updateWalls(){
  int walls;
  walls = 4; // 0100: there is a wall in the back
  // Loop through all three wall sensors
  rightWallVal = muxRead(rightWall);
  leftWallVal = muxRead(leftWall);
  frontWallVal = muxRead(frontWall);
  
  if(rightWallVal > RIGHT_WALL_SENSOR_THRESHOLD) {
    walls |= WALL_RIGHT;
  }
  if(leftWallVal > LEFT_WALL_SENSOR_THRESHOLD) {
    walls |= WALL_LEFT;
  }
  if(frontWallVal > FRONT_WALL_SENSOR_THRESHOLD) {
    walls |= WALL_FRONT;
  }
  //Serial.print("cur_pos is ");
  //Serial.println(cur_pos);                                                        
  //Serial.print("is there a wall on the right? ");
  //Serial.println((walls & 8) >> 3);
  Serial.print("front wall val: ");
  Serial.println(frontWallVal);
  Serial.print("rightWallVal is ");
  Serial.println(rightWallVal);
  Serial.print("leftWallVal is ");
  Serial.println(leftWallVal);
  Serial.print("\n");
  
  //Serial.print("threshold value is ");
  //Serial.println(WALL_SENSOR_THRESHOLD);
  return walls;  
}

int setDirection(int wallData){
  if (wallData&001==1){
    direction = 0;
  }
  else{
    direction = 1;
  }
}

/* 
 * Read analog value from mux 
 * Returns int
 */
int muxRead(byte pin){
  selectMuxPin(pin);
  analogRead(zInput);
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

// Turn on LED when robot has finished mapping maze
//void onLED(){
//  digitalWrite(ledIndicator,HIGH);
//}

void setup() {
  // Begin Serial monitor
  Serial.begin(9600);

    // Was originally used for testing with treasure circuit, no longer used
   

 
   // Setting up timer 2 for treasure detection
   ACSR = (1<<ACIE) | (1<<ACIS1) | (1<<ACIS0);
   TCCR2B = 2; // running with clock divided by 8
   //TCCR2B = 3; // running with clock divided by 16
   TCCR2A=0; // All other functions disabled
   TCCR2A = 0; // Turn off other timer2 functions
   TCNT2 = 0; // Initialize the counter
   pinMode (treasure_detection_pin, INPUT);
   pinMode(avg_val_pin, INPUT);

  // Connect servos 
  right_servo.attach(3); 
  left_servo.attach(5);

  // Brake servos
  right_servo.write(SERVO_BRAKE);
  left_servo.write(SERVO_BRAKE);

  // Set up the select pins as outputs:
  for (int i=0; i<3; i++)
  {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], HIGH);
  }
  pinMode(zInput, INPUT); // Set up Z (muxout) as an input
  

  // Radio Initialization
  // Setup and configure rf radio
  radio.begin();
  // optionally, increase the delay between retries & # of retries
  radio.setRetries(10,10);
  radio.setAutoAck(true);
  // set the channel  
  radio.setChannel(0x50);
  // set the power
  // RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MED=-6dBM, and RF24_PA_HIGH=0dBm.
  radio.setPALevel(RF24_PA_MAX);
  //RF24_250KBPS for 250kbs, RF24_1MBPS for 1Mbps, or RF24_2MBPS for 2Mbps
  radio.setDataRate(RF24_2MBPS);
  //radio.setCRCLength(RF24_CRC_8);

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
  // TODO: Remove?
//  radio.printDetails();

  ////Serial.println("got here");
  
  // Wait at start for 1 second
  delay(1000);
}

void loop() {
  while(done) {
  }
  // put your main code here, to run repeatedly:
  initialize();
  
     
  
   manualOverride =  (analogRead(overridePin) > 500);
   while(!whistle && !manualOverride) { // reduces jitter
      for (int i = 0 ; i < FFT_N*2 ; i += 2) { // save 256 samples
        int k = analogRead(A1);
        fft_input[i] = k; // put real data into even bins
        fft_input[i+1] = 0; // set odd bins to 0
      }
      fft_window(); // window the data for better frequency response
      fft_reorder(); // reorder the data before doing the fft
      fft_run(); // process the data in the fft
      fft_mag_log(); // take the output of the fft
      Serial.println("Start");
      if (fft_counter > FFT_TRIGGER) {
        Serial.println("On");
        whistle = true;
      }
      else {
        for (byte i = 0 ; i < FFT_N/2 ; i++) { // TODO: check if needed 
          //if ( (i  > 8) && (i < 13) ) {
            if (i == 10){
              Serial.print(fft_log_out[i]); // send out the data
              Serial.print(" ");
            if (fft_log_out[i] > threshold) {
              fft_counter+=1;
            } else {
              fft_counter=0;
            }
          } 
        }      
        delay(50);
      }
      manualOverride =  (analogRead(overridePin) > 500);
  }

  traverse(); 

  pinMode(ledIndicator, OUTPUT);
  digitalWrite(ledIndicator, HIGH);
  
  done = 1;
  int real_cur_pos = cur_pos;
  for (int i = 0; i < 20; i++) {
    if (maze[gety(i)][getx(i)] != 15 && !visited_info[i]) {
      cur_pos = i;
      treasure = 0;
      Serial.print("entered: ");Serial.println(i);
      delay(10);
      send_my_radio();
      delay(100);
    }
  }
  cur_pos = real_cur_pos;
  
  finished = 1;
  send_my_radio();

}


