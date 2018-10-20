//Declare pin functions
#define stp_left 9
#define dir_left 10
#define MS1_left 11
#define MS2_left 12
#define EN_left  13

#define stp_right 2
#define dir_right 3
#define MS1_right 4
#define MS2_right 5
#define EN_right  6

//Declare variables for functions
int x;
int y;
int state_1;
int state_2;

int PINS[] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
#define NUM_PINS 11

//200 steps/rotation

void setup() {
  for(int i = 0; i < NUM_PINS; i++){
    pinMode(PINS[i], OUTPUT);
  }
  
  
  resetEDPins(); //Set step, direction, microstep and enable pins to default states
}

//Main loop
void loop() {
      digitalWrite(EN_left, LOW); //Pull enable pin low to allow motor control
      digitalWrite(EN_right, LOW); //Pull enable pin low to allow motor control
      Draw_Square();
}

//Draw Square
void Draw_Square()
{
  //Change Direction for both motors
  state_1=digitalRead(dir_left);  
  state_2=digitalRead(dir_right);

  if(state_1 == HIGH){
      digitalWrite(dir_left, LOW);
  }
  if(state_2 == HIGH){
      digitalWrite(dir_right, LOW);
  }

  // Draw a Line
  for(x= 1; x<200; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp_left,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp_left,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }

  // Turn a corner
  for(x= 1; x<200; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp_right,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp_right,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }

  //Change Direction for both motors
  state_1=digitalRead(dir_left);  
  state_2=digitalRead(dir_right);


 //Pull direction pins high to move "backward"
  if(state_1 == LOW){
      digitalWrite(dir_left, HIGH);
  }
  if(state_2 == LOW){
      digitalWrite(dir_right, HIGH);
  }

  //Draw Line backward
  for(x= 1; x<200; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp_left,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp_left,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }

  //Turn a corner
  for(x= 1; x<200; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp_left,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp_left,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }

  
  Serial.println("Enter new option");
  Serial.println();
}

//Reset Easy Driver pins to default states
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


