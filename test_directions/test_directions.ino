/****************************************************************************** 
SparkFun Easy Driver Basic Demo
Toni Klopfenstein @ SparkFun Electronics
March 2015
https://github.com/sparkfun/Easy_Driver

Simple demo sketch to demonstrate how 5 digital pins can drive a bipolar stepper motor,
using the Easy Driver (https://www.sparkfun.com/products/12779). Also shows the ability to change
microstep size, and direction of motor movement.

Development environment specifics:
Written in Arduino 1.6.0

This code is beerware; if you see me (or any other SparkFun employee) at the local, and you've found our code helpful, please buy us a round!
Distributed as-is; no warranty is given.

Example based off of demos by Brian Schmalz (designer of the Easy Driver).
http://www.schmalzhaus.com/EasyDriver/Examples/EasyDriverExamples.html
******************************************************************************/
//Declare pin functions on Redboard
#define stp_1 9
#define dir_1 10
#define MS1_1 11
#define MS2_1 12
#define EN_1  13

#define stp_2 2
#define dir_2 3
#define MS1_2 4
#define MS2_2 5
#define EN_2  6

//Declare variables for functions
char user_input;
int x;
int y;
int state_1;
int state_2;

void setup() {
  // Driver 1 pins
  pinMode(stp_1, OUTPUT);
  pinMode(dir_1, OUTPUT);
  pinMode(MS1_1, OUTPUT);
  pinMode(MS2_1, OUTPUT);
  pinMode(EN_1, OUTPUT);

  // Driver 2 pins
  pinMode(stp_2, OUTPUT);
  pinMode(dir_2, OUTPUT);
  pinMode(MS1_2, OUTPUT);
  pinMode(MS2_2, OUTPUT);
  pinMode(EN_2, OUTPUT);
  
  resetEDPins(); //Set step, direction, microstep and enable pins to default states
  Serial.begin(9600); //Open Serial connection for debugging
  Serial.println("Begin motor control");
  Serial.println();
  //Print function list for user selection
  Serial.println("Enter number for control option:");
  Serial.println("1. Turn at default microstep mode.");
  Serial.println("2. Reverse direction at default microstep mode.");
  Serial.println("3. Turn at 1/8th microstep mode.");
  Serial.println("4. Step forward and reverse directions.");
  Serial.println();
}

//Main loop
void loop() {
  while(Serial.available()){
      user_input = Serial.read(); //Read user input and trigger appropriate function
      digitalWrite(EN_1, LOW); //Pull enable pin low to allow motor control
      digitalWrite(EN_2, LOW);
      if (user_input =='1')
      {
         StepForwardDefault();
      }
      else if(user_input =='2')
      {
        ReverseStepDefault();
      }
      else if(user_input =='3')
      {
        SmallStepMode();
      }
      else if(user_input =='4')
      {
        ForwardBackwardStep();
      }
      else
      {
        Serial.println("Invalid option entered.");
      }
      resetEDPins();
  }
}

//Reset Easy Driver pins to default states
void resetEDPins()
{
  digitalWrite(stp_1, LOW);
  digitalWrite(dir_1, LOW);
  digitalWrite(MS1_1, LOW);
  digitalWrite(MS2_1, LOW);
  digitalWrite(EN_1, HIGH);

  digitalWrite(stp_2, LOW);
  digitalWrite(dir_2, LOW);
  digitalWrite(MS1_2, LOW);
  digitalWrite(MS2_2, LOW);
  digitalWrite(EN_2, HIGH);
}

//Default microstep mode function
void StepForwardDefault()
{
  Serial.println("Moving forward at default step mode.");
  digitalWrite(dir_1, LOW); //Pull direction pin low to move "forward"
  digitalWrite(dir_2, LOW); //Pull direction pin low to move "forward"

  for(x= 1; x<1000; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp_1,HIGH); //Trigger one step forward
    digitalWrite(stp_2,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp_1,LOW); //Pull step pin low so it can be triggered again
    digitalWrite(stp_2,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  Serial.println("Enter new option");
  Serial.println();
}

//Reverse default microstep mode function
void ReverseStepDefault()
{
  Serial.println("Moving in reverse at default step mode.");
  digitalWrite(dir_1, HIGH); //Pull direction pin high to move in "reverse"
  digitalWrite(dir_2, HIGH); //Pull direction pin high to move in "reverse"
  for(x= 1; x<1000; x++)  //Loop the stepping enough times for motion to be visible
  {
    digitalWrite(stp_1,HIGH); //Trigger one step
    digitalWrite(stp_2,HIGH); //Trigger one step
    delay(1);
    digitalWrite(stp_1,LOW); //Pull step pin low so it can be triggered again
    digitalWrite(stp_2,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  Serial.println("Enter new option");
  Serial.println();
}

// 1/8th microstep foward mode function
void SmallStepMode()
{
  Serial.println("Stepping at 1/8th microstep mode.");
  digitalWrite(dir_1, LOW); //Pull direction pin low to move "forward"
  digitalWrite(MS1_1, HIGH); //Pull MS1, and MS2 high to set logic to 1/8th microstep resolution
  digitalWrite(MS2_1, HIGH); 
   
  digitalWrite(dir_2, LOW); //Pull direction pin low to move "forward"
  digitalWrite(MS1_2, HIGH); //Pull MS1, and MS2 high to set logic to 1/8th microstep resolution
  digitalWrite(MS2_2, HIGH);
  for(x= 1; x<2000; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp_1,HIGH); //Trigger one step forward
    digitalWrite(stp_2,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp_1,LOW); //Pull step pin low so it can be triggered again
    digitalWrite(stp_2,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  Serial.println("Enter new option");
  Serial.println();
}

//Forward/reverse stepping function
void ForwardBackwardStep()
{
  Serial.println("Alternate between stepping forward and reverse.");
  for(x= 1; x<5; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    //Read direction pin state and change it
    state_1=digitalRead(dir_1);
    state_2=digitalRead(dir_2);
    
    if(state_1 == HIGH && state_2 == HIGH)
    {
      digitalWrite(dir_1, LOW);
      digitalWrite(dir_2, LOW);
    }
    else if(state_1 ==LOW && state_2 == LOW)
    {
      digitalWrite(dir_1,HIGH);
      digitalWrite(dir_2,HIGH);
    }
    
    for(y=1; y<1000; y++)
    {
      digitalWrite(stp_1,HIGH); //Trigger one step
      digitalWrite(stp_2,HIGH); //Trigger one step
      delay(1);
      digitalWrite(stp_1,LOW); //Pull step pin low so it can be triggered again
      digitalWrite(stp_2,LOW); //Pull step pin low so it can be triggered again
      delay(1);
    }
  }
  Serial.println("Enter new option:");
  Serial.println();
}
