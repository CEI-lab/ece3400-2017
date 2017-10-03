// global variables
enum State {
  START, JUNCTION, BETWEEN, DONE
};
enum Direction {
  UP, DOWN, LEFT, RIGHT, UNDEF
};
State state = START;
Direction facingDirection = UP;

// rotates robot right
void rotateRight() {
}

// rotates robot left
void rotateLeft() {
}

// move forward
void moveForward() {
}

// returns next direction robot should go
Direction algorithmNextStep(int sensors) {
}

// returns integer representing wall detection
int wallSensors() {
}

// returns integer representing line sensor
int lineSensor() {
}

// returns true if the go signal is heard
boolean goSignal() {
}

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  if (state == START) {
    if (goSignal()) {
      state = JUNCTION;
    }
  }
  
  else if (state == JUNCTION) {
    int sensors = wallSensors();
    Direction dir = algorithmNextStep(sensors);

    if (dir == UNDEF) {
      state = DONE;
    }
    
    if (dir != facingDirection) {
      rotateRight();
    }
    else {
      state = BETWEEN;
    }
  }
  
  else if (state == BETWEEN) {
    int straight;
    if (wallSensors() == straight && lineSensor() == straight) {
      moveForward();
    }
    else {
      state = JUNCTION;
    }
  }
  
  else if (state == DONE) {
    while (1);
  }
}
