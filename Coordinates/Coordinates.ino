#define stp_right 2
#define dir_right 3
#define MS1_right 4
#define MS2_right 5
#define EN_right  6

#define stp_left 9
#define dir_left 10
#define MS1_left 11
#define MS2_left 12
#define EN_left  13

#define NUM_PINS 10
int PINS[] = {2, 3, 4, 5, 6, 9, 10, 11, 12, 13};

int X;
int Y;

void setup() {
  Serial.begin(9600); //Open Serial connection for debugging
//  for(int i = 0; i < NUM_PINS; i++){
//    int a = PINS[i];
//    Serial.println(a);
//    pinMode(a, OUTPUT);
//  }
  pinMode(stp_left, OUTPUT);
  pinMode(dir_left, OUTPUT);
  pinMode(MS1_left, OUTPUT);
  pinMode(MS2_left, OUTPUT);
  pinMode(EN_left, OUTPUT);

  pinMode(stp_right, OUTPUT);
  pinMode(dir_right, OUTPUT);
  pinMode(MS1_right, OUTPUT);
  pinMode(MS2_right, OUTPUT);
  pinMode(EN_right, OUTPUT);
  X = 8000;
  Y = 5600;

  resetEDPins(); //Set step, direction, microstep and enable pins to default states
  zeroCoordinates();
}

void loop() {
  digitalWrite(EN_left, LOW); //Pull enable pin low to allow motor control
  digitalWrite(EN_right, LOW); //Pull enable pin low to allow motor control
  Serial.println("Stepping at 1/8th microstep mode.");
  digitalWrite(dir_left, HIGH); //Pull direction pin high to move to the right (backward)
  digitalWrite(MS1_left, HIGH); //Pull MS1, and MS2 high to set logic to 1/8th microstep resolution
  digitalWrite(MS2_left, HIGH);
  for(int x = 1; x<8000; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp_left,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp_left,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }

  digitalWrite(dir_right, LOW); //Pull direction pin high to move to the right (backward)
  digitalWrite(MS1_right, HIGH); //Pull MS1, and MS2 high to set logic to 1/8th microstep resolution
  digitalWrite(MS2_right, HIGH);
  for(int x = 1; x<5600; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp_right,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp_right,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  
  zeroCoordinates();
}

void zeroCoordinates()
{
  digitalWrite(EN_left, LOW); //Pull enable pin low to allow motor control
  Serial.println("Stepping at 1/8th microstep mode.");
  digitalWrite(dir_left, LOW); //Pull direction pin low to move to the left (backward)
  digitalWrite(MS1_left, HIGH); //Pull MS1, and MS2 high to set logic to 1/8th microstep resolution
  digitalWrite(MS2_left, HIGH);
  for(int i = X; i >= 0; i--){
    digitalWrite(stp_left,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp_left,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }

  digitalWrite(EN_right, LOW); //Pull enable pin low to allow motor control
  digitalWrite(dir_right, HIGH); //may need to switch to high, draw Y coordinate back to 0
  digitalWrite(MS1_right, HIGH); //1/8th microstep resolution
  digitalWrite(MS2_right, HIGH);
  for(int i = Y; i >= 0; i--){
    digitalWrite(stp_right,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp_right,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  resetEDPins();
  
}

void SmallStepMode()
{
  digitalWrite(dir_left, HIGH); //Pull direction pin high to move to the right (backward)
  for(int x = 1; x < 1000; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp_left,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp_right,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  zeroCoordinates();
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
