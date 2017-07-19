#include <Servo.h>

// PINS
#define WALL_FRONT_2         5 
#define WALL_LEFT_2          12 
#define WALL_RIGHT_2         6 
#define ledIndicator         A5
#define overridePin          A3

// Servo speed definitions
#define SERVO_BRAKE          90
#define SERVO_L_FORWARD_MAX  100.0
#define SERVO_R_FORWARD_MAX  80.0
#define SERVO_L_INCR_FORWARD 2.0
#define SERVO_R_INCR_FORWARD -2.0

#define ROW_NUM              5
#define COL_NUM              4

// Inputs on analog mux
#define rightWall            6
#define leftWall             5
#define frontWall            7
#define right_pid            3
#define left_pid             2
#define right_turn           4
#define left_turn            1

// Wall sensing thresholds
#define RIGHT_WALL_SENSOR_THRESHOLD 400
#define LEFT_WALL_SENSOR_THRESHOLD  220
#define FRONT_WALL_SENSOR_THRESHOLD 100

// Line following error range
#define ERROR_RANGE          100

 #define  WALL_NORTH  1 // 0001
 #define  WALL_EAST   2 // 0010
 #define  WALL_SOUTH  4 // 0100
 #define  WALL_WEST   8 // 1000

/* Wall information sensed by robot
 * Take a conservative approach: always assume there is a wall at the back.
 * Assuming there is not a wall at the back will bring errors when the robot is making 180 degree turns.
*/
typedef enum { 
  WALL_FRONT = 5,  // 0101
  WALL_RIGHT = 6,  // 0110
  WALL_LEFT  = 12, // 1100
} WALLINFO;

/* Robot's orientation
*/
typedef enum {
  NORTH = 1, // 0001
  EAST  = 2, // 0010
  SOUTH = 4, // 0100
  WEST  = 8, // 1000
} ORIENTATION;

/***************** Robot control Variable Declarations *************/
bool manualOverride = false;
bool whistle        = false;
/*******************************************************************/

/*************** Line Following Variable Declarations **************/
// Servo objects
Servo left_servo;
Servo right_servo;

// Control variables for line following
float error           = 0;
float error_magnitude = 0;
int   counter         = 0;

// Line sensor values
int right_pid_val  = 0; 
int left_pid_val   = 0;
int right_turn_val = 0;
int left_turn_val  = 0;

// Servo turn values
float servo_turn_value[]  = {SERVO_R_FORWARD_MAX, 0, SERVO_L_FORWARD_MAX, SERVO_L_FORWARD_MAX};
int   servo_turn_delays[] = {300,0,300,900};

/*******************************************************************/


/*************** Wall sensing Variable Declarations **************/
//Mux select signals S0, S1, S2 and Zinput
const int selectPins[3] = {8, 2, 4}; // 
const int zInput        = A0;        // 

// Wall sensor values
int rightWallVal = 0;
int leftWallVal  = 0;
int frontWallVal = 0;
int wallsRadio   = 0;

// Variable that dictates which way robot turns at intersection
// 0 left, 1 straight, 2 right, 3 180 degrees
int direction    = 1;
/*******************************************************************/

/***************** Maze-Mapping Variable Declarations *************/
int maze[ROW_NUM][COL_NUM]; // Each index is a 4-bit int that stores the wall info of that particular grid. e.g. 1101
int orientation = NORTH; // The robot begins with facing north.
int cur_pos = 19; // The robot begins on grid #19.
int nex_pos; // This variable stores the location that the robot is planning to move to.
bool visited_info[20]; // Arrayt to hold visited information; Set grid index to true if visited
bool on_stack[20]; // Set to true if is on stack (pushed to stack)

int delta_N[5] = { 0,  1,  0, -1,  0}; // An array used for faster accesses to the four directions: prioritizes going North.  
int delta_E[5] = { 1,  0, -1,  0,  1}; // An array used for faster accesses to the four directions: prioritizes going East.
int delta_S[5] = { 0, -1,  0,  1,  0}; // An array used for faster accesses to the four directions: prioritizes going South.
int delta_W[5] = {-1,  0,  1,  0, -1}; // An array used for faster accesses to the four directions: prioritizes going West.

int stack[50]; // The stack that stores locations. Shouldn't be taller than 100 ints since there are only 20 grids.
int stack_ptr  = 0; // A pointer that indexes the stack. The pointer points to the next empty slot.


int step_cnt   = 0; // A counter that counts how many steps have been used.
bool done      = 0; // A flag that will be set to 1 once the robot finishes traversing the whole maze, and 0 otherwise.
int known_walls[20]; // An array that stores the information of our knowledge of the walls of each grid.
int FOUND_TREASURE = 0; // A flag that will be set high once the treasure is found.
/*******************************************************************/


/*******************************************************************/
/************************** Subfunctions ****************************/
/*******************************************************************/

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

// Return true if the stack is empty. Only works on the stack defined globally as int stack[50].
bool stack_empty() {
  return (stack_ptr == 0);
}

// Return the value on top of the stack.
int stack_top() {
  if (stack_empty()) return NULL;
  return stack[stack_ptr-1];
}

void stack_pop() {
  if (stack_empty()) return ;
  stack_ptr--;
}

// Initialize each index of maze[ROW_NUM][COL_NUM] to be 15 = 1111 in bits.
// Set to 15 since we assume there are walls on all four directions at every block.
void initialize_maze() {
  int m = ROW_NUM; int n = COL_NUM;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      maze[i][j] = 15; // 1111
    }
  }
}

// Initialize each grid to be "unvisited".
void initialize_visited_info() {
  for (int i = 0; i < 20; i++) { // the length of this array is 20.
    visited_info[i] = false;
  }
}



// Initialize the informations we know about the walls. Assume our maze is 5x4.
// e.g. known_walls[0] is set to 9 = 1001 since it's on the upper left corner, so we know the information
// about the walls on north and west. While 1001 corresponds to north and west.
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


// Round-shift a 4-bit wide int one bit to the left.
// Only works for inputs that are 4-bit wide!
int my_shift_left(int input) { 
  int output = ((input << 1) & 15);
  output |= ((input >> 3) & 1);
  return output;
}

// Round-shift a 4-bit wide int one bit to the right.
// Only works for inputs that are 4-bit wide!
int my_shift_right(int input) { 
  int output = ((input >> 1) & 15);
  output |= ((input & 1) << 3);
  return output;
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
  //Serial.print("rightWallVal is ");
  //Serial.println(rightWallVal);
  //Serial.print("leftWallVal is ");
  //Serial.println(leftWallVal);
  //Serial.print("threshold value is ");
  //Serial.println(WALL_SENSOR_THRESHOLD);
  return walls;  
}


// Print the maze's wall information in an easy to read format.
// Helpful for testing wall sensing in conjunction with 
// a mapping robot.
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

// This function is responsible for moving the robot from one intersection
// to the next intersection (determined by path_finding algorithm).
// Also send wall and treasure information over radio to the base-station.
void move_one(int from, int to) { 
  int from_x = getx(from);
  int from_y = gety(from);
  int to_x = getx(to);
  int to_y = gety(to);
  
  int curr_wall_info = 0;
  curr_wall_info = updateWalls();
  
  if (from_x == to_x) { // moving along same col
    if (to_y == from_y) { // two locations are the same, do not move
      curr_wall_info = updateWalls();
    }  
    else if (to_y > from_y) { // move in positive direction (downwards)
      if (orientation == NORTH) move(3);
      if (orientation == EAST) move(2);
      if (orientation == SOUTH) move(1);
      if (orientation == WEST)  move(0);
      orientation = SOUTH;
    }
    else { // move in negative direction (upwards)
      if (orientation == NORTH) move(1);
      if (orientation == EAST) move(0);
      if (orientation == SOUTH) move(3);
      if (orientation == WEST)  move(2);
      orientation = NORTH;
    }
  }
  else { // moving vertically
    if (to_x > from_x) { // move in positive direction (rightwards)
      if (orientation == NORTH)  move(2);
      if (orientation == EAST)  move(1);
      if (orientation == SOUTH) move(0);
      if (orientation == WEST) move(3);
      orientation = EAST;
    }
    else { // move in negative direction (leftwards)
      if (orientation == NORTH)  move(0);
      if (orientation == EAST) move(3);
      if (orientation == SOUTH) move(2);
      if (orientation == WEST)  move(1);
      orientation = WEST;
    }
  }

  //visited_info[from] = true;
  //visited_info[to] = true;
  from = to; // update the location

  update_maze(curr_wall_info);
}

/**
 * function move() is called from the navigation code after an intersection 
 * has been reached and the decision of what direction to go has been made
 * takes in a direction to move one block and 
 * a pointer to the array that stores wall sensor values (this probably doesn't need to be an argument, could be global)
 * wall sensor values are modified when the robot reaches the proscribed intersection
 direction: 0 if left, 1 if forward, 2 if right, 3 if 180
 **/
void move(int direction){

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
      ////Serial.println(right_pid_val);
      ////Serial.println(left_pid_val);  
      ////Serial.println();  
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
  
  //int w = updateWalls();
  ////Serial.println("walls: " + w);
  //return w; 
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

// A bunch of Initializations.
void initialize() {
  initialize_maze();
  initialize_visited_info();
  initialize_known_walls();
}


// The master function that let the robot traverse the maze.
void traverse() {
  stack_push(cur_pos); // visit grid 19 initially
  
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
  
  print_stack();

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
    
    print_stack();
    move_one(cur_pos, next_pos);

    // Determine if all nodes have been visited:
    all_visited = 1;
    for (i = 0; i < 20; i++) {
      all_visited = (all_visited & visited_info[i]);
    }

  } 
}
void setup() {
  // Begin Serial monitor
  Serial.begin(9600);

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

  delay(2000);

}


void loop() {
  // If robot has finished mapping the maze, busy wait b/c there's nothing to do
  while(done);
  
  // Initialize the robot
  initialize();
  Serial.println("initialized");

  // Either the whistle or the manual overwrite signal has been received, now start traversing the maze.
  traverse(); 

  // Light up external LED to indicate that maze has been mapped
  pinMode(ledIndicator, OUTPUT);
  digitalWrite(ledIndicator, HIGH);
  
  done = 1;

}
