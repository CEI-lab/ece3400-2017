#include <iostream>
#include <string>
#include <cmath>
#include <cassert>

#define ROW_NUM 5
#define COL_NUM 4

using namespace std;

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

int maze[ROW_NUM][COL_NUM];
int maze_cheatsheet[ROW_NUM][COL_NUM];
int orientation = NORTH; // the robot begins with facing north.
int cur_pos = 19; // the robot begins on grid #19.
int nex_pos;
bool visited_info[20]; // set to true if already visited
bool on_stack[20]; // set to true if is on schedule (pused to stack)
int delta_N[5] = { 0,  1,  0, -1,  0}; // used for faster accesses to the four directions: prioritizes going North
int delta_E[5] = { 1,  0, -1,  0,  1}; //
int delta_S[5] = { 0, -1,  0,  1,  0};
int delta_W[5] = {-1,  0,  1,  0, -1};
int stack[100]; // the stack that stores locations. Shouldn't be taller than 100 ints since there are only 100 grids.
int stack_ptr = 0;
int queue[100]; // the queue used for doing BFS in backtracking. Shouldn't be longer than 100 ints since there are only 20 grids
int queue_ptr = 0;
int step_cnt = 0;
int known_walls[20];
int FOUND_TREASURE = 0;

string to_bit(int in) {
  string result;
  for (int i = 0; i < 4; i++) {
    result = to_string(in & 1) + result;
    in >>= 1;
  }
  return result;
}

int getx(int id) {
  return id/4;
}

int gety(int id) {
  return id%4;
}

int get_id(int x, int y) {
  return 4*x + y;
}

void queue_push(int pos) {
  queue[queue_ptr] = pos;
  queue_ptr++;
}

bool queue_empty() {
  return (queue_ptr == 0);
}

int queue_front() {
  if (queue_empty()) return NULL;
  return queue[0];
}

void queue_pop() {
  if (queue_empty()) return ;
  for (int i = 0; i < queue_ptr; i++) {
    queue[i] = queue[i+1];
  }
  queue_ptr--;
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

void set_maze_cheatsheet() {
  
  /*
  // CUSTOM MAZE VERSION 1
  // -----------
  //maze_cheatsheet[0][0] |= ;
  maze_cheatsheet[0][1] |= (WALL_EAST);
  maze_cheatsheet[0][2] |= (WALL_WEST);
  //maze_cheatsheet[0][3] |=;
  //maze_cheatsheet[1][0] |= (WALL_NORTH);
  maze_cheatsheet[1][1] |= (WALL_EAST);
  maze_cheatsheet[1][2] |= (WALL_WEST);
  //maze_cheatsheet[1][3] |= (WALL_WEST);
  //maze_cheatsheet[2][0] |= (WALL_WEST);
  //maze_cheatsheet[2][1]
  maze_cheatsheet[2][2] |= (WALL_SOUTH);
  maze_cheatsheet[2][3] |= (WALL_SOUTH);
  //maze_cheatsheet[3][0] |= (WALL_SOUTH);
  //maze_cheatsheet[3][1] |= (WALL_SOUTH);
  maze_cheatsheet[3][2] |= (WALL_NORTH);
  maze_cheatsheet[3][3] |= (WALL_NORTH);
  //maze_cheatsheet[4][0] |= (WALL_NORTH);
  //maze_cheatsheet[4][1] |= (WALL_NORTH);
  //maze_cheatsheet[4][2] |= (WALL_NORTH);
  //maze_cheatsheet[4][3]
  */
  
  /*
  // CUSTOM MAZE VERSION 2
  // -----------
  //maze_cheatsheet[0][0] |= ;
  //maze_cheatsheet[0][1] |= (WALL_EAST);
  //maze_cheatsheet[0][2] |= (WALL_WEST);
  //maze_cheatsheet[0][3] |=;
  //maze_cheatsheet[1][0] |= (WALL_NORTH);
  //maze_cheatsheet[1][1] |= (WALL_EAST);
  //maze_cheatsheet[1][2] |= (WALL_WEST);
  //maze_cheatsheet[1][3] |= (WALL_WEST);
  //maze_cheatsheet[2][0] |= (WALL_WEST);
  //maze_cheatsheet[2][1]
  //maze_cheatsheet[2][2] |= (WALL_SOUTH);
  //maze_cheatsheet[2][3] |= (WALL_SOUTH);
  //maze_cheatsheet[3][0] |= (WALL_SOUTH);
  //maze_cheatsheet[3][1] |= (WALL_SOUTH);
  //maze_cheatsheet[3][2] |= (WALL_NORTH);
  //maze_cheatsheet[3][3] |= (WALL_NORTH);
  //maze_cheatsheet[4][0] |= (WALL_NORTH);
  //maze_cheatsheet[4][1] |= (WALL_NORTH);
  //maze_cheatsheet[4][2] |= (WALL_NORTH);
  //maze_cheatsheet[4][3]
  */

  /*
  // CUSTOM MAZE VERSION 3
  // -----------
  maze_cheatsheet[0][0] |= (WALL_SOUTH);
  maze_cheatsheet[0][1] |= (WALL_SOUTH);
  maze_cheatsheet[0][2] |= (WALL_SOUTH);
  //maze_cheatsheet[0][3] |= ;
  maze_cheatsheet[1][0] |= (WALL_NORTH);
  maze_cheatsheet[1][1] |= (WALL_NORTH);
  maze_cheatsheet[1][2] |= (WALL_NORTH | WALL_EAST);
  maze_cheatsheet[1][3] |= (WALL_WEST);
  //maze_cheatsheet[2][0] |= (WALL_WEST);
  //maze_cheatsheet[2][1] |= ;
  maze_cheatsheet[2][2] |= (WALL_EAST);
  maze_cheatsheet[2][3] |= (WALL_WEST);
  maze_cheatsheet[3][0] |= (WALL_SOUTH);
  maze_cheatsheet[3][1] |= (WALL_SOUTH);
  maze_cheatsheet[3][2] |= (WALL_EAST | WALL_SOUTH);
  maze_cheatsheet[3][3] |= (WALL_WEST);
  maze_cheatsheet[4][0] |= (WALL_NORTH);
  maze_cheatsheet[4][1] |= (WALL_NORTH);
  maze_cheatsheet[4][2] |= (WALL_NORTH);
  //maze_cheatsheet[4][3] |= ;
  */

  /*
  // CUSTOM MAZE VERSION 4
  // -----------
  //maze_cheatsheet[0][0] |= (WALL_SOUTH);
  maze_cheatsheet[0][1] |= (WALL_SOUTH);
  maze_cheatsheet[0][2] |= (WALL_SOUTH);
  //maze_cheatsheet[0][3] |= ;
  maze_cheatsheet[1][0] |= (WALL_EAST);
  maze_cheatsheet[1][1] |= (WALL_NORTH | WALL_WEST | WALL_SOUTH);
  maze_cheatsheet[1][2] |= (WALL_NORTH | WALL_SOUTH);
  //maze_cheatsheet[1][3] |= (WALL_WEST);
  //maze_cheatsheet[2][0] |= (WALL_WEST);
  maze_cheatsheet[2][1] |= (WALL_NORTH | WALL_SOUTH);
  maze_cheatsheet[2][2] |= (WALL_EAST | WALL_NORTH);
  maze_cheatsheet[2][3] |= (WALL_WEST);
  maze_cheatsheet[3][0] |= (WALL_SOUTH | WALL_EAST);
  maze_cheatsheet[3][1] |= (WALL_NORTH | WALL_WEST | WALL_EAST);
  maze_cheatsheet[3][2] |= (WALL_EAST | WALL_SOUTH | WALL_WEST);
  maze_cheatsheet[3][3] |= (WALL_WEST);
  maze_cheatsheet[4][0] |= (WALL_NORTH);
  //maze_cheatsheet[4][1] |= (WALL_NORTH);
  maze_cheatsheet[4][2] |= (WALL_NORTH);
  //maze_cheatsheet[4][3] |= ;
  */

  /*
  // CUSTOM MAZE VERSION 5
  // -----------
  maze_cheatsheet[0][0] |= (WALL_SOUTH);
  //maze_cheatsheet[0][1] |= (WALL_EAST);
  //maze_cheatsheet[0][2] |= (WALL_WEST);
  //maze_cheatsheet[0][3] |=;
  maze_cheatsheet[1][0] |= (WALL_NORTH);
  maze_cheatsheet[1][1] |= (WALL_WEST | WALL_SOUTH);
  maze_cheatsheet[1][2] |= (WALL_SOUTH | WALL_EAST);
  maze_cheatsheet[1][3] |= (WALL_WEST);
  //maze_cheatsheet[2][0] |= (WALL_WEST);
  maze_cheatsheet[2][1] |= (WALL_NORTH);
  maze_cheatsheet[2][2] |= (WALL_NORTH);
  //maze_cheatsheet[2][3] |= (WALL_SOUTH);
  maze_cheatsheet[3][0] |= (WALL_EAST);
  maze_cheatsheet[3][1] |= (WALL_SOUTH | WALL_WEST);
  maze_cheatsheet[3][2] |= (WALL_SOUTH);
  maze_cheatsheet[3][3] |= (WALL_SOUTH);
  //maze_cheatsheet[4][0] |= (WALL_NORTH);
  maze_cheatsheet[4][1] |= (WALL_NORTH);
  maze_cheatsheet[4][2] |= (WALL_NORTH);
  maze_cheatsheet[4][3] |= (WALL_NORTH);
  */

  /*
  // CUSTOM MAZE VERSION 6
  // -----------
  //maze_cheatsheet[0][0] |= (WALL_SOUTH);
  maze_cheatsheet[0][1] |= (WALL_SOUTH);
  maze_cheatsheet[0][2] |= (WALL_SOUTH);
  //maze_cheatsheet[0][3] |=;
  maze_cheatsheet[1][0] |= (WALL_EAST);
  maze_cheatsheet[1][1] |= (WALL_WEST | WALL_NORTH);
  maze_cheatsheet[1][2] |= (WALL_EAST | WALL_NORTH);
  maze_cheatsheet[1][3] |= (WALL_WEST);
  maze_cheatsheet[2][0] |= (WALL_EAST);
  maze_cheatsheet[2][1] |= (WALL_SOUTH | WALL_EAST | WALL_WEST);
  maze_cheatsheet[2][2] |= (WALL_WEST | WALL_EAST);
  maze_cheatsheet[2][3] |= (WALL_WEST);
  //maze_cheatsheet[3][0] |= (WALL_EAST);
  maze_cheatsheet[3][1] |= (WALL_NORTH);
  maze_cheatsheet[3][2] |= (WALL_EAST);
  maze_cheatsheet[3][3] |= (WALL_WEST);
  //maze_cheatsheet[4][0] |= (WALL_NORTH);
  //maze_cheatsheet[4][1] |= (WALL_NORTH);
  //maze_cheatsheet[4][2] |= (WALL_NORTH);
  //maze_cheatsheet[4][3] |= (WALL_NORTH);
  */
 
  /*
  // CUSTOM MAZE VERSION 7
  // -----------
  //maze_cheatsheet[0][0] |= (WALL_SOUTH);
  //maze_cheatsheet[0][1] |= (WALL_SOUTH);
  //maze_cheatsheet[0][2] |= (WALL_SOUTH);
  //maze_cheatsheet[0][3] |=;
  //maze_cheatsheet[1][0] |= (WALL_EAST);
  //maze_cheatsheet[1][1] |= (WALL_WEST | WALL_NORTH);
  //maze_cheatsheet[1][2] |= (WALL_EAST | WALL_NORTH);
  //maze_cheatsheet[1][3] |= (WALL_WEST);
  //maze_cheatsheet[2][0] |= (WALL_EAST);
  //maze_cheatsheet[2][1] |= (WALL_SOUTH | WALL_EAST | WALL_WEST);
  //maze_cheatsheet[2][2] |= (WALL_WEST | WALL_EAST);
  //maze_cheatsheet[2][3] |= (WALL_WEST);
  //maze_cheatsheet[3][0] |= (WALL_EAST);
  //maze_cheatsheet[3][1] |= (WALL_NORTH);
  //maze_cheatsheet[3][2] |= (WALL_EAST);
  //maze_cheatsheet[3][3] |= (WALL_WEST);
  //maze_cheatsheet[4][0] |= (WALL_NORTH);
  //maze_cheatsheet[4][1] |= (WALL_NORTH);
  maze_cheatsheet[4][2] |= (WALL_EAST);
  maze_cheatsheet[4][3] |= (WALL_WEST);  
  */
 
  /*
  // CUSTOM MAZE VERSION 8
  // Maze 4 - 33 steps
  maze_cheatsheet[0][2] |= (WALL_SOUTH);
  maze_cheatsheet[1][1] |= (WALL_EAST);
  maze_cheatsheet[1][2] |= (WALL_NORTH + WALL_EAST + WALL_WEST + WALL_SOUTH);
  maze_cheatsheet[1][3] |= (WALL_WEST);
  maze_cheatsheet[2][1] |= (WALL_EAST + WALL_SOUTH);
  maze_cheatsheet[2][2] |= (WALL_EAST + WALL_WEST + WALL_NORTH);
  maze_cheatsheet[2][3] |= (WALL_WEST);
  maze_cheatsheet[3][0] |= (WALL_EAST);
  maze_cheatsheet[3][1] |= (WALL_WEST + WALL_NORTH + WALL_SOUTH);
  maze_cheatsheet[3][2] |= (WALL_SOUTH);
  maze_cheatsheet[4][1] |= (WALL_NORTH);
  maze_cheatsheet[4][2] |= (WALL_NORTH + WALL_EAST);
  maze_cheatsheet[4][3] |= WALL_WEST;
  */

  /*
  //CUSTOM MAZE VERSION 9
  //Maze 7 - 26 steps
  maze_cheatsheet[0][0] |= WALL_SOUTH;
  maze_cheatsheet[0][1] |= WALL_SOUTH;
  //maze[0][2] |= (WALL_SOUTH + WALL_EAST);
  maze_cheatsheet[0][3] |= (WALL_SOUTH);
  maze_cheatsheet[1][0] |= (WALL_NORTH + WALL_EAST);
  maze_cheatsheet[1][1] |= (WALL_WEST + WALL_NORTH);
  maze_cheatsheet[1][2] |= (WALL_SOUTH);
  maze_cheatsheet[1][3] |= (WALL_NORTH);
  maze_cheatsheet[2][0] |= (WALL_EAST);
  maze_cheatsheet[2][1] |= (WALL_WEST | WALL_EAST);
  maze_cheatsheet[2][2] |= (WALL_WEST | WALL_NORTH);
  //maze[2][3] |= (WALL_WEST);
  maze_cheatsheet[3][0] |= WALL_EAST;
  maze_cheatsheet[3][1] |= (WALL_WEST);
  maze_cheatsheet[3][2] |= (WALL_SOUTH | WALL_EAST);
  maze_cheatsheet[3][3] |= WALL_WEST;
  //maze[4][0] |= (WALL_EAST);
  //maze[4][1] |= (WALL_WEST + WALL_EAST + WALL_NORTH + WALL_SOUTH);
  maze_cheatsheet[4][2] |= (WALL_NORTH);
  //maze[4][3] |= 0;
  */

  /*
  // CUSTOM MAZE VERSION 10
  // -----------
  maze_cheatsheet[0][0] |= WALL_SOUTH;
  maze_cheatsheet[0][1] |= WALL_SOUTH;
  //maze[0][2] |= (WALL_SOUTH + WALL_EAST);
  maze_cheatsheet[0][3] |= (WALL_SOUTH);
  maze_cheatsheet[1][0] |= (WALL_NORTH);
  maze_cheatsheet[1][1] |= (WALL_SOUTH | WALL_NORTH);
  maze_cheatsheet[1][2] |= (WALL_SOUTH);
  maze_cheatsheet[1][3] |= (WALL_NORTH);
  maze_cheatsheet[2][0] |= (WALL_EAST);
  maze_cheatsheet[2][1] |= (WALL_WEST | WALL_NORTH | WALL_SOUTH);
  maze_cheatsheet[2][2] |= (WALL_NORTH);
  //maze[2][3] |= (WALL_WEST);
  //maze_cheatsheet[3][0] |= WALL_EAST;
  maze_cheatsheet[3][1] |= (WALL_NORTH);
  maze_cheatsheet[3][2] |= (WALL_SOUTH | WALL_EAST);
  maze_cheatsheet[3][3] |= WALL_WEST;
  //maze[4][0] |= (WALL_EAST);
  //maze[4][1] |= (WALL_WEST + WALL_EAST + WALL_NORTH + WALL_SOUTH);
  maze_cheatsheet[4][2] |= (WALL_NORTH);
  //maze[4][3] |= 0;
  */
  
  /*
  // CUSTOM MAZE VERSION 11
  // maze 0 - 20
  maze_cheatsheet[2][1] |= (WALL_WEST + WALL_NORTH); 
  maze_cheatsheet[1][1] |= WALL_SOUTH;
  maze_cheatsheet[2][2] |= (WALL_EAST + WALL_NORTH); 
  maze_cheatsheet[1][2] |= WALL_SOUTH;
  maze_cheatsheet[3][1] |= (WALL_WEST + WALL_SOUTH); 
  maze_cheatsheet[2][3] |= WALL_WEST;
  maze_cheatsheet[3][2] |= (WALL_EAST + WALL_SOUTH); 
  maze_cheatsheet[3][3] |= WALL_WEST;
  maze_cheatsheet[4][2] |= (WALL_NORTH);
  maze_cheatsheet[4][1] |= (WALL_NORTH);
  maze_cheatsheet[2][0] |= (WALL_EAST);
  maze_cheatsheet[3][0] |= (WALL_EAST);
  */

  /*
  // CUSTOM MAZE VERSION 12
  // maze 1
  maze_cheatsheet[0][0] |= (WALL_SOUTH);
  maze_cheatsheet[0][1] |= (WALL_SOUTH);
  maze_cheatsheet[0][2] |= (WALL_SOUTH);
  //maze_cheatsheet[0][3]
  maze_cheatsheet[1][0] |= (WALL_NORTH);
  maze_cheatsheet[1][1] |= (WALL_NORTH);
  maze_cheatsheet[1][2] |= (WALL_NORTH + WALL_EAST);
  maze_cheatsheet[1][3] |= (WALL_WEST);
  //maze_cheatsheet[2][0]
  //maze_cheatsheet[2][1]
  maze_cheatsheet[2][2] |= (WALL_EAST);
  maze_cheatsheet[2][3] |= (WALL_WEST);
  maze_cheatsheet[3][0] |= (WALL_SOUTH);
  maze_cheatsheet[3][1] |= (WALL_SOUTH);
  maze_cheatsheet[3][2] |= (WALL_SOUTH + WALL_EAST);
  maze_cheatsheet[3][3] |= (WALL_WEST);
  maze_cheatsheet[4][0] |= (WALL_NORTH);
  maze_cheatsheet[4][1] |= (WALL_NORTH);
  maze_cheatsheet[4][2] |= (WALL_NORTH);
  //maze_cheatsheet[4][3]
  */
  
  // CUSTOM MAZE VERSION 13
  maze_cheatsheet[0][0] |= (WALL_SOUTH);
  maze_cheatsheet[0][1] |= (WALL_SOUTH);
  maze_cheatsheet[0][2] |= (WALL_SOUTH);
  maze_cheatsheet[0][3] |= (WALL_SOUTH);
  maze_cheatsheet[1][0] |= (WALL_NORTH);
  maze_cheatsheet[1][1] |= (WALL_NORTH | WALL_SOUTH);
  maze_cheatsheet[1][2] |= (WALL_NORTH | WALL_SOUTH);
  maze_cheatsheet[1][3] |= (WALL_NORTH | WALL_SOUTH);
  maze_cheatsheet[2][0] |= (WALL_EAST);
  maze_cheatsheet[2][1] |= (WALL_NORTH | WALL_WEST);
  maze_cheatsheet[2][2] |= (WALL_NORTH | WALL_EAST);
  maze_cheatsheet[2][3] |= (WALL_WEST | WALL_NORTH);
  maze_cheatsheet[3][0] |= (WALL_EAST);
  maze_cheatsheet[3][1] |= (WALL_EAST | WALL_WEST);
  maze_cheatsheet[3][2] |= (WALL_EAST | WALL_WEST);
  maze_cheatsheet[3][3] |= (WALL_WEST);
  //maze_cheatsheet[4][0] |= (WALL_NORTH);
  maze_cheatsheet[4][1] |= (WALL_EAST);
  maze_cheatsheet[4][2] |= (WALL_WEST);
  //maze_cheatsheet[4][3] |= (WALL_WEST); 
  
  // BOUNDARY
  // --------
  maze_cheatsheet[0][0] |= (WALL_NORTH + WALL_WEST);
  maze_cheatsheet[0][1] |= WALL_NORTH;
  maze_cheatsheet[0][2] |= WALL_NORTH;
  maze_cheatsheet[0][3] |= (WALL_NORTH + WALL_EAST);
  maze_cheatsheet[1][3] |= WALL_EAST;
  maze_cheatsheet[2][3] |= WALL_EAST;
  maze_cheatsheet[3][3] |= WALL_EAST;
  maze_cheatsheet[4][3] |= (WALL_EAST + WALL_SOUTH);
  maze_cheatsheet[4][2] |= WALL_SOUTH;
  maze_cheatsheet[4][1] |= WALL_SOUTH;
  maze_cheatsheet[4][0] |= (WALL_SOUTH + WALL_WEST);
  maze_cheatsheet[3][0] |= WALL_WEST;
  maze_cheatsheet[2][0] |= WALL_WEST;
  maze_cheatsheet[1][0] |= WALL_WEST;
}

void robot_go_straight() {
  // TODO: API
  cout << "robot goes straight" << endl;
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

void robot_turn_left() {
  // TODO: API
  cout << "robot turns left" << endl;
}

void robot_turn_right() {
  // TODO: API
  cout << "robot turns right" << endl;
}

void go_straight() {
  robot_go_straight();
}

void turn_left() { // only turn, do not go
  robot_turn_left();
  orientation = my_shift_right(orientation);
}

void turn_right() { // only turn, do not go
  robot_turn_right();
  orientation = my_shift_left(orientation);
}

int get_wall_info() {
  // TODO: API
  int curx = getx(cur_pos);
  int cury = gety(cur_pos);
  if (orientation == NORTH) {
    return maze_cheatsheet[curx][cury] | 4; // 4: 0100, cannot sense the south, according to the protocol, just assume there is a wall back
  }
  if (orientation == EAST) {
    return my_shift_right(maze_cheatsheet[curx][cury] | 8); // 8: 1000, cannot sense the west (facing east), just assume there is a wall east
  }
  if (orientation == SOUTH) {
    return my_shift_right(my_shift_right(maze_cheatsheet[curx][cury] | 1)); // 1: 0001, the same drill
  }
  if (orientation == WEST) {
    return my_shift_left(maze_cheatsheet[curx][cury] | 2); // 2: 0010, the same drill
  }
  else return NULL;
}

void update_maze() { // update the maze with wall sensors readings
  int curr_int = get_wall_info();
  if (orientation == NORTH) {
    maze[getx(cur_pos)][gety(cur_pos)] &= curr_int;
    if (getx(cur_pos) - 1 >= 0) maze[getx(cur_pos) - 1][gety(cur_pos)] &= ((int)(15 - pow(2,2)) | ((curr_int & 1) << 2));
    if (gety(cur_pos) - 1 >= 0) maze[getx(cur_pos)][gety(cur_pos) - 1] &= ((int)(15 - pow(2,1)) | (((curr_int >> 3) & 1) << 1));
    if (gety(cur_pos) + 1 < COL_NUM) maze[getx(cur_pos)][gety(cur_pos) + 1] &= ((int)(15 - pow(2,3)) | (((curr_int >> 1) & 1) << 3));
  }
  if (orientation == EAST) {
    maze[getx(cur_pos)][gety(cur_pos)] &= my_shift_left(curr_int);
    if (getx(cur_pos) - 1 >= 0) maze[getx(cur_pos) - 1][gety(cur_pos)] &= ((int)(15 - pow(2,2)) | (((curr_int >> 3) & 1) << 2));
    if (getx(cur_pos) + 1 < ROW_NUM) maze[getx(cur_pos) + 1][gety(cur_pos)] &= ((int)(15 - pow(2,0)) | ((curr_int >> 1) & 1));
    if (gety(cur_pos) + 1 < COL_NUM) maze[getx(cur_pos)][gety(cur_pos) + 1] &= ((int)(15 - pow(2,3)) | ((curr_int & 1) << 3));
  }
  if (orientation == SOUTH) {
    maze[getx(cur_pos)][gety(cur_pos)] &= my_shift_left(my_shift_left(curr_int));
    if (getx(cur_pos) + 1 < ROW_NUM) maze[getx(cur_pos) + 1][gety(cur_pos)] &= ((int)(15 - pow(2,0)) | (curr_int & 1));
    if (gety(cur_pos) - 1 >= 0) maze[getx(cur_pos)][gety(cur_pos) - 1] &= ((int)(15 - pow(2,1)) | (((curr_int >> 1) & 1) << 1));
    if (gety(cur_pos) + 1 < COL_NUM) maze[getx(cur_pos)][gety(cur_pos) + 1] &= ((int)(15 - pow(2,3)) | (((curr_int >> 3) & 1) << 3));
  }
  if (orientation == WEST) { 
    maze[getx(cur_pos)][gety(cur_pos)] &= my_shift_right(curr_int);
    if (getx(cur_pos) - 1 >= 0) maze[getx(cur_pos) - 1][gety(cur_pos)] &= ((int)(15 - pow(2,2)) | (((curr_int >> 1) & 1) << 2));
    if (getx(cur_pos) + 1 < ROW_NUM) maze[getx(cur_pos) + 1][gety(cur_pos)] &= ((int)(15 - pow(2,0)) | ((curr_int >> 3) & 1));
    if (gety(cur_pos) - 1 >= 0) maze[getx(cur_pos)][gety(cur_pos) - 1] &= ((int)(15 - pow(2,1)) | ((curr_int & 1) << 1));
  }
}

void correct_orientation_to(int target_orien) {
  if ( my_shift_right(orientation) == target_orien) turn_left();
  else {
    while (orientation != target_orien) turn_right();
  }
}

void printmaze() {
  cout << "---------------------" << endl;
  for (int i = 0; i < ROW_NUM; i++) {
    for (int j = 0; j < COL_NUM; j++) {
      cout << to_bit(maze[i][j]) << " ";
    }
    cout << '\n';
  }
  cout << "---------------------" << endl;
}

void print_stack() { // print the stack in a pretty format.
  if (stack_empty()) {
    cout << "stack is empty!" << endl;
    return ;
  }
  for (int i = stack_ptr - 1; i >= 0; i--) {
    if (stack[i] < 10) cout << "| " << " " << stack[i] << " |" << endl;
    else cout << "| " << stack[i] << " |" << endl;
    cout << "|----|" << endl;
  }
}

void move_one(int& from, int& to) { // from and to should ONLY be ONE block away!
  system("pause");
  print_stack();
  cout << "moving from " << from << " to " << to << endl;
  cout << "current step cnt is " << ++step_cnt << endl;
  int from_x = getx(from);
  int from_y = gety(from);
  int to_x = getx(to);
  int to_y = gety(to);
  if (from_y == to_y) { // moving vertically
    if (to_x == from_x) {// two locations are the same, do not move
    }
    else if (to_x > from_x) { // move in positive direction (downwards)
      if (orientation != SOUTH) correct_orientation_to(SOUTH);
      go_straight();
    }
    else { // move in negative direction (upwards)
      if (orientation != NORTH) correct_orientation_to(NORTH);
      go_straight();
    }
  }
  else { // moving horizontally
    if (to_y > from_y) { // move in positive direction (rightwards)
      if (orientation != EAST) correct_orientation_to(EAST);
      go_straight();
    }
    else { // move in negative direction (leftwards)
      if (orientation != WEST) correct_orientation_to(WEST);
      go_straight();
    }
  }

  visited_info[from] = true;
  visited_info[to] = true;
  from = to; // update the location
  update_maze();
  printmaze();
}

void print_backtrack_label(int in[ROW_NUM][COL_NUM]) {
  for (int i = 0; i < ROW_NUM; i++) {
    for (int j = 0; j < COL_NUM; j++) {
      cout << in[i][j] << " ";
    }
    cout << '\n';
  }
}

bool is_next_to(int a, int b) { 
  // check if the two grids are next to each other
  return ((abs(getx(a) - getx(b)) == 1) && (gety(a) == gety(b))) || ((abs(gety(a) - gety(b)) == 1) && (getx(a) == getx(b)));
}

bool is_the_same(int a, int b) { 
  // check if the two grids are the same one
  return (a == b);
}

int find_direction(int nex_pos, int cur_pos) { 
  // return nex_pos's direction with respect to cur_pos
  // 1(0001) for NORTH, 2(0010) for EAST, 4(0100) for SOUTH, 8(1000) for WEST
  assert(!is_the_same(nex_pos, cur_pos));
  assert(is_next_to(nex_pos, cur_pos));
  if (getx(cur_pos) < getx(nex_pos)) return 4; // To the south.
  else if (getx(cur_pos) > getx(nex_pos)) return 1; // To the north.
  else if (gety(cur_pos) < gety(nex_pos)) return 2; // To the east.
  else return 8; // To the west.
}

int map(int i, int orientation) {
  for (int j = 0; j <= i; j++) {
    orientation = my_shift_left(orientation);
  }
  return log2(orientation);
  /*
  if (i == 0) return 2;
  if (i == 1) return 3;
  if (i == 2) return 0;
  if (i == 3) return 1;
  else return NULL;
  */
}

void backtrack(int& from, int& to) {
  //cout << "backtracking from " << from << " to " << to << endl;
  int backtrack_label[ROW_NUM][COL_NUM]; // each index is the distance to the target grid, INF if can't reach
  int backtrack_visited[20];
  int to_x = getx(to);
  int to_y = gety(to);
  int dist = 0;
  for (int i = 0; i < 20; i++) backtrack_visited[i] = false;
  for (int i = 0; i < ROW_NUM; i++) {
    for (int j = 0; j < COL_NUM; j++) {
      backtrack_label[i][j] = INFINITY;
    }
  }
  backtrack_label[to_x][to_y] = 0;
  backtrack_visited[to] = true;
  queue_push(to);
  while(!queue_empty()) {
    int targ = queue_front();
    queue_pop();
    int targ_x = getx(targ);
    int targ_y = gety(targ);
    for (int i = 0; i < 4; i++) {
      int neigh_x = targ_x + delta_N[i];
      int neigh_y = targ_y + delta_N[i+1];
      int neigh = get_id(neigh_x, neigh_y);
      if ( !((maze[targ_x][targ_y] >> map(i, NORTH)) & 1) && (backtrack_visited[neigh] == false) ) {
        queue_push(neigh);
        backtrack_visited[neigh] = true;
        backtrack_label[neigh_x][neigh_y] = backtrack_label[targ_x][targ_y] + 1;
      }
    }
  }
  //print_backtrack_label(backtrack_label);
  while (from != to) {
    int next_x;
    int next_y;
    int next_to_go;
    int from_x = getx(from);
    int from_y = gety(from);
    int dist_to_targ = pow(2,30);//numeric_limits<int>::max();
    for (int i = 0; i < 4; i++) {
      next_x = from_x + delta_N[i];
      next_y = from_y + delta_N[i+1];
      bool inbound = (next_x >= 0) && (next_y >= 0) && (next_x < ROW_NUM) && (next_y < COL_NUM);
      bool no_wall = inbound && !(find_direction(get_id(next_x, next_y), from) & maze[from_x][from_y]);
      if ( inbound && no_wall && (backtrack_label[next_x][next_y] < dist_to_targ) ) {
        //cout << "inside the if block" << endl;
        dist_to_targ = backtrack_label[next_x][next_y];
        next_to_go = get_id(next_x, next_y);
      }
    }
    if (dist_to_targ == pow(2,30)) {//numeric_limits<int>::max()) {
      break;
    }
    //cout << "next_to_go is " << next_to_go << endl;
    move_one(from, next_to_go);
  }
}

void traverse() {
  stack_push(cur_pos);
  while(!stack_empty()) {
    nex_pos = stack_top();
    stack_pop();
    if ( visited_info[nex_pos] || (known_walls[nex_pos] == 15 && FOUND_TREASURE) ) {}
    else {
      bool next_to_and_no_wall = is_next_to(nex_pos, cur_pos) && !(find_direction(nex_pos, cur_pos) & maze[getx(cur_pos)][gety(cur_pos)]);
      if ( is_the_same(nex_pos, cur_pos) || next_to_and_no_wall ) move_one(cur_pos, nex_pos);
      else backtrack(cur_pos, nex_pos); // need to backtrack
      known_walls[cur_pos] |= 15;
      int cur_pos_x = getx(cur_pos);
      int cur_pos_y = gety(cur_pos);
      int shortcut = (int)pow(2,31);
      for (int i = 0; i < 4; i++) { // now that we are at the new location, so we push its neighbors into the stack
        int new_pos_x;
        int new_pos_y;
        int prior_orien;
        if (FOUND_TREASURE) {
          prior_orien = orientation;
          if (orientation == NORTH) {
            new_pos_x = cur_pos_x + delta_N[i];
            new_pos_y = cur_pos_y + delta_N[i+1];
          }
          if (orientation == EAST) {
            new_pos_x = cur_pos_x + delta_E[i];
            new_pos_y = cur_pos_y + delta_E[i+1];
          }
          if (orientation == SOUTH) {
            new_pos_x = cur_pos_x + delta_S[i];
            new_pos_y = cur_pos_y + delta_S[i+1];
          }
          if (orientation == WEST) {
            new_pos_x = cur_pos_x + delta_W[i];
            new_pos_y = cur_pos_y + delta_W[i+1];
          }
        }
        else {
          prior_orien = EAST;
          new_pos_x = cur_pos_x + delta_E[i];
          new_pos_y = cur_pos_y + delta_E[i+1];
        }
        int new_pos = get_id(new_pos_x, new_pos_y);
        bool inbound = (new_pos_x >= 0) && (new_pos_y >= 0) && (new_pos_x < ROW_NUM) && (new_pos_y < COL_NUM);
        bool no_wall = !(( maze[cur_pos_x][cur_pos_y] >> map(i, prior_orien) ) & 1);
        bool cant_skip = (known_walls[new_pos] != 15 || !FOUND_TREASURE);
        if ( inbound ) known_walls[new_pos] |= find_direction(cur_pos, new_pos);
        if ( inbound && no_wall && on_stack[new_pos] && !visited_info[new_pos] && cant_skip ) shortcut = new_pos;
        if ( inbound && no_wall && !on_stack[new_pos] && cant_skip ) {
          cout << "pushed " << new_pos << endl;
          stack_push(new_pos);
        }
      }
      if (shortcut != (int)pow(2,31)) {
        cout << "pushed " << shortcut << " as shortcut" << endl;
        stack_push(shortcut);
      }
    }
  }
}

void initialize() {
  initialize_maze();
  initialize_visited_info();
  initialize_known_walls();
  set_maze_cheatsheet();
}

int main() {
  initialize();
  traverse();
}