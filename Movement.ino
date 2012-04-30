
unsigned char lmSetpoint = 8;                                        //setpoint for left motor during stepForward()
unsigned char rmSetpoint = 8;                                        //setpoint for left motor during stepForward()
unsigned char leftMotorPower = 255;                                  //PWM output to the left motor    
unsigned char rightMotorPower = 255;                                 //PWM output to the right motor 
unsigned char 

PID lmPID(leftSensor, leftMotorPower, lmSetpoint, 

//turnLeft() - turns the robot counterclockwise clockwise 90 degrees
void turnLeft() {
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

//stepForward - runs both motors to move straight while correcting its path
void stepForward()
{
  /* Movement */
  while (stepProgress < STEP_LENGTH)
  {
    
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
