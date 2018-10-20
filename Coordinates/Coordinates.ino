// pins for right Etch-A-Sketch motor (up and down movement)
#define stp_right 2
#define dir_right 3 // set low to move downward
#define MS1_right 4 // set high for 1/8 microstep revolution
#define MS2_right 5 // set high for 1/8 microstep revolution
#define EN_right  6 // set low to allow motor control

// pins for left Etch-A-Sketch motor (left and right movement)
#define stp_left 9
#define dir_left 10 // set low to move leftward
#define MS1_left 11 // set high for 1/8 microstep revolution
#define MS2_left 12 // set high for 1/8 microstep revolution
#define EN_left  13 // set low to allow motor control

/* Coordinates (X,Y)
 * Upper left corner is (0,0)
 * X increases to the right, Y increases downward
 */
int X;
int Y;

void setup() {
  Serial.begin(9600); //Open Serial connection for debugging

  // initialize pins for left motor
  pinMode(stp_left, OUTPUT);
  pinMode(dir_left, OUTPUT);
  pinMode(MS1_left, OUTPUT);
  pinMode(MS2_left, OUTPUT);
  pinMode(EN_left, OUTPUT);

  // initialize pins for right motor
  pinMode(stp_right, OUTPUT);
  pinMode(dir_right, OUTPUT);
  pinMode(MS1_right, OUTPUT);
  pinMode(MS2_right, OUTPUT);
  pinMode(EN_right, OUTPUT);

  zeroCoordinates();
  
  // initializes coordinates
  X = 0;
  Y = 0;

  resetEDPins(); //Set step, direction, microstep and enable pins to default states
}

void loop() {
  spanScreen();
}


/* Starts the X and Y coordinates at (0,0) and then goes across the width of the screen
 * (to the right) and down the height of the screen before going back to (0,0).
 */
void spanScreen(){
  zeroCoordinates();
  
  digitalWrite(EN_left, LOW);
  digitalWrite(dir_left, HIGH);
  digitalWrite(MS1_left, HIGH);
  digitalWrite(MS2_left, HIGH);
  
  for(int x = 1; x<8000; x++)  // go across the width of the screen
  {
    digitalWrite(stp_left,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp_left,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }

  digitalWrite(EN_right, LOW);
  digitalWrite(dir_right, LOW);
  digitalWrite(MS1_right, HIGH);
  digitalWrite(MS2_right, HIGH);
  
  for(int x = 1; x<5600; x++) // go down the height of the screen
  {
    digitalWrite(stp_right,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp_right,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
}

/*
 * Takes the current value of X and Y, then takes steps to move the coordinates back to (0,0).
 */
void zeroCoordinates()
{
  digitalWrite(EN_left, LOW); //Pull enable pin low to allow motor control
  digitalWrite(dir_left, LOW); //Pull direction pin low to move to the left (backward)
  digitalWrite(MS1_left, HIGH); //Pull MS1, and MS2 high to set logic to 1/8th microstep resolution
  digitalWrite(MS2_left, HIGH);

  digitalWrite(EN_right, LOW); //Pull enable pin low to allow motor control
  digitalWrite(dir_right, HIGH); //may need to switch to high, draw Y coordinate back to 0
  digitalWrite(MS1_right, HIGH); //1/8th microstep resolution
  digitalWrite(MS2_right, HIGH);

  
  for(int i = X; i >= 0; i--){
    digitalWrite(stp_left,HIGH); //Trigger one step forward
    digitalWrite(stp_right,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp_left,LOW); //Pull step pin low so it can be triggered again
    digitalWrite(stp_right,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  resetEDPins();
  
}

void resetEDPins()
{
  digitalWrite(stp_left, LOW);
  digitalWrite(dir_left, LOW);
  digitalWrite(MS1_left, LOW);
  digitalWrite(MS2_left, LOW);
  digitalWrite(EN_left, HIGH);
  digitalWrite(stp_right, LOW);
  digitalWrite(dir_right, LOW);
  digitalWrite(MS1_right, LOW);
  digitalWrite(MS2_right, LOW);
  digitalWrite(EN_right, HIGH);
}
