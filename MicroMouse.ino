//Recient from Andrew

//digital pins 0, 1 reserved
//always use unsigned long for timers
//analog pin 2 for left wheel, analog pin 3 for right wheel
//pin A4 for left sensor
//A5 is front sensor
//A6 is right sensor


//unsigned long newTime = 0;                   //the latest recorded time reading
//unsigned long oldTime = 0;                   //the previously recorded time
//unsigned long timeDiff = 0;                  //the difference between the new time and the old time
//unsigned char iterationCounter = 0;          //determines how many iterations of loop() have occurred since the counter was last reset
//unsigned char iterationMax = 4;              //determines how many iterations of loop() are completed before the timer is updated
unsigned long stepProgress = 0;              //the linear displacement since last stopped
unsigned char leftSensor = 0;
unsigned char rightSensor = 0;
unsigned char frontSensor = 0;

const unsigned long STEP_LENGTH = 16;        //the distance between two squares
const double L_CORRECTION = 0;          //the left wheel's constant for steering control
const double R_CORRECTION = 0;          //the right wheel's constant for steering control

const double idealLeftSensor = 46;  //calibrated value for Left sensor (MUST BE CALIBRATED)
const double idealRightSensor = 60;

const double NO_FRONT_WALL = 770;
const double NO_LEFT_WALL = 550;



void setup()
{ 
  attachInterrupt(0, incrLeftSteps, RISING);  //increments leftSteps whenever a rising edge is detected from the left motor
  attachInterrupt(1, incrRightSteps, RISING); //increments rightSteps whenever a rising edge is detected from the right motor
}

void loop()
{
  //every iteration of loop() (or nth iteration of the loop if too fast) the robot takes a time reading to be compared to the amount of steps taken since the last reading
//  if (iterationCounter == 4)                    //if n loops have occurred, update the times. 
//  {
//    oldTime = newTime;
//    newTime = micros();   
//    timeDiff = newTime - oldTime;
//  }
  frontSensor = analogRead(5);
  //The below code is based on the state machine derived at Josh's
  if ((frontSensor > NO_FRONT_WALL) && (leftSensor < NO_LEFT_WALL))            //if there is a wall to the left and no wall in front, step forward
    stepForward();
  if (leftSensor > NO_LEFT_WALL)                                               //if there is no left wall, turn left
    turnLeft();
  if ((frontSensor < NO_FRONT_WALL) && (leftSensor < NO_LEFT_WALL))            //if there is a front wall and a left wall, turn right
  {
    turnRight();
    if (frontSensor < NO_FRONT_WALL)                                           //if there is a front wall after turning right, then it is a dead end, turn right again
      turnRight();
  }
  
//  iterationcounter++;                           //updates the iteration counter
}

//stepForward - runs both motors to move straight while correcting its path
void stepForward()
{
  /* Movement */
  while (stepProgress < STEP_LENGTH)
  {
    leftSensor = analogRead(4);
    if (leftSensor < idealLeftSensor)
    {
      analogWrite(2, 255);
      analogWrite(3, 255 - (R_CORRECTION * leftSensor));
    }
    else
    {
      analogWrite(2, 255);
      analogWrite(3, 255 - (L_CORRECTION * leftSensor));
    }
    
    /* Mapping */
    switch(currentFacing)                //updates the current position on the map based on the direction it just stepped.
    {
      case 0:        //steppng north
        --yPosition;
        break;
      case 1:        //stepping east
        ++xPosition;
        break;
      case 2:        //stepping south
        ++yPosition;
        break;
      case 3:        //stepping west
        --xPosition;
        break;
  }
  
}

//turnLeft() - turns the robot counterclockwise clockwise 90 degrees
void turnLeft()
{
  /* Movement */
  
  /* Mapping */
  currentFacing = currentFacing > 0 ? --currentFacing : 3;      //updates the current facing.
}

//turnRight() - turns the robot clockwise 90 degrees
void turnRight()
{
  /* Movement */
  
  /* Mapping */
  currentFacing = currentFacing < 3 ? ++currentFacing : 0;      //updates the current facing.
} 
