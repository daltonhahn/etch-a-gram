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

#define STEP_SIZE 23 // ratio of steps to pixels

/* Coordinates (X,Y)
 * Upper left corner is (0,0)
 * X increases to the right, Y increases downward
 */
int X;
int Y;
char user_input;

void setup() {
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

  //zeroCoordinates();

  Serial.begin(9600);
  Serial.println("Enter an option: ");
  Serial.println("(0) Take first step");
  Serial.println("(1) Start drawing");
  Serial.println("(2) Reset");
  Serial.println();

  resetEDPins(); //Set step, direction, microstep and enable pins to default states
}

void loop() {
    while(Serial.available()){
      user_input = Serial.read();
      if (user_input == '0'){
        // ADD FIRST STEP HERE
        takeSteps(102, 42); 
      }
      else if (user_input =='1')
      {
        // ADD TAKE STEPS HERE
        takeSteps(155, 0);
        takeSteps(0, 155);
        takeSteps(-155, 0);
        takeSteps(0, -154);
        takeSteps(2, 2);
        takeSteps(1, 0);
        takeSteps(0, -1);
        takeSteps(2, 3);
        takeSteps(145, 0);
        takeSteps(0, 145);
        takeSteps(-145, 0);
        takeSteps(0, -144);
        takeSteps(2, -3);
        takeSteps(145, 0);
        takeSteps(0, -1);
        takeSteps(1, 1);
        takeSteps(0, 149);
        takeSteps(-1, 0);
        takeSteps(0, 1);
        takeSteps(-2, -1);
        takeSteps(-148, 0);
        takeSteps(1, 1);


      }
      else if(user_input =='2')
      {
        zeroCoordinates();
      }
      else
      {
        Serial.println("Invalid option entered.");
      }
      resetEDPins();
  }
}

void takeSteps(int distX, int distY){
  // enabling motor control
  digitalWrite(EN_left, LOW);
  digitalWrite(EN_right, LOW);

  // setting to 1/8 microstep revolution
  digitalWrite(MS1_left, HIGH);
  digitalWrite(MS2_left, HIGH);
  digitalWrite(MS1_right, HIGH);
  digitalWrite(MS2_right, HIGH);

  X += distX * STEP_SIZE;
  Y += distY * STEP_SIZE;
  
  // calculate number of steps to take
  int stepsX = abs(distX * STEP_SIZE);
  int stepsY = abs(distY * STEP_SIZE);
  
  if(distX < 0){
    digitalWrite(dir_left, LOW);
  }
  else if(stepsX > 0){
    digitalWrite(dir_left, HIGH);
  }

  if(distY < 0){
    digitalWrite(dir_right, HIGH);
  }
  else if(distY > 0){
    digitalWrite(dir_right, LOW);
  }


  for(int i = max(stepsX, stepsY); i > 0; i--){
    if(stepsX != 0){
      digitalWrite(stp_left, HIGH);
      stepsX--;
    }
    if(stepsY != 0){
      digitalWrite(stp_right, HIGH);
      stepsY--;
    }
    delay(1);
    digitalWrite(stp_left,LOW);
    digitalWrite(stp_right,LOW); 
    delay(1);
  }

  while(stepsX != 0){
    digitalWrite(stp_left, HIGH);
    delay(1);
    digitalWrite(stp_left,LOW);
    delay(1);
  }
  
  while(stepsY != 0){
    digitalWrite(stp_right, HIGH);
    delay(1);
    digitalWrite(stp_right,LOW);
    delay(1);
  }
}


/*
 * Takes the current value of X and Y, then takes steps to move the coordinates back to (0,0).
 */
void zeroCoordinates()
{
  digitalWrite(EN_left, LOW); 
  digitalWrite(dir_left, LOW);
  digitalWrite(MS1_left, HIGH); 
  digitalWrite(MS2_left, HIGH);

  digitalWrite(EN_right, LOW);
  digitalWrite(dir_right, HIGH);
  digitalWrite(MS1_right, HIGH); 
  digitalWrite(MS2_right, HIGH);

  for(int i = 0; i < 6000; i++){
    digitalWrite(stp_right,HIGH); //Trigger one step forward
    digitalWrite(stp_left,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp_left,LOW); //Pull step pin low so it can be triggered again
    digitalWrite(stp_right,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  
//  for(int i = X; i >= 0; i--){
//    digitalWrite(stp_left,HIGH); //Trigger one step forward
//    delay(1);
//    digitalWrite(stp_left,LOW); //Pull step pin low so it can be triggered again
//    delay(1);
//  }
//
//  Serial.println("after X loop");
//  
//  for(int i = Y; i >= 0; i--){
//    digitalWrite(stp_right,HIGH); //Trigger one step forward
//    delay(1);
//    digitalWrite(stp_right,LOW); //Pull step pin low so it can be triggered again
//    delay(1);
//  }
  
  X = 0;
  Y = 0;
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
