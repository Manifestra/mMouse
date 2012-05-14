unsigned long totalSteps = 0;
unsigned long ideal_leftsensor = 0;                                  //calibrated ideal sensor readings.  See calibration function below
unsigned long ideal_rightsensor = 0;
//unsigned char leftSetpoint = 8;                                      //setpoint for left sensor during stepForward()
//unsigned char rightSetpoint = 8;                                     //setpoint for right sensor during stepForward()
//unsigned char frontSetpoint = 8;                                     //setpoint for the front sensor. Ideal distance from front wall
unsigned char leftMotorPower = 255;                                  //PWM output to the left motor    
unsigned char rightMotorPower = 255;                                 //PWM output to the right motor 

void left_right_calibration(){                     //calibrates the left and right sensor to the robots ideal position
     int i = 0;
     for(i; i <= 20; i++)
     {
       ideal_leftsensor += analogRead(L_SENS_PIN);
       ideal_rightsensor += analogRead(R_SENS_PIN);
     }
    ideal_leftsensor = ideal_leftsensor/i;
    ideal_rightsensor =  ideal_rightsensor/i;
}

void fast_stop(){
    for(int j = 0; j < 1350; j++)            // for PWM left: 150 Right: 155.  1350 iterations to stop.
    {
       analogWrite(EN_LEFT, 100);
       analogWrite(EN_RIGHT, 100);
       digitalWrite(L_MINUS, HIGH);
       digitalWrite(L_PLUS, LOW);
       digitalWrite(R_MINUS, HIGH);
       digitalWrite(R_PLUS, LOW); 
    }
    digitalWrite(L_PLUS, LOW);
    digitalWrite(R_PLUS, LOW);
    analogWrite(EN_LEFT, LOW);
    analogWrite(EN_RIGHT, LOW);
}

//turnLeft() - turns the robot counterclockwise clockwise 90 degrees
void turnLeft()                                                 //Turns left until calibrated steps have been reached
{
  totalSteps = leftWheelSteps + rightWheelSteps;
  unsigned long initSteps = leftWheelSteps + rightWheelSteps;
  unsigned long L_turnProgress = totalSteps - initSteps;
  unsigned long L_turnSteps = 88; 
  while(L_turnProgress < L_turnSteps)
  {
    digitalWrite(R_PLUS, HIGH); 
    digitalWrite(R_MINUS, LOW);
    digitalWrite(L_PLUS, LOW);
    digitalWrite(L_MINUS, HIGH);
    analogWrite(EN_LEFT, 15);
    analogWrite(EN_RIGHT,15);
    totalSteps = leftWheelSteps + rightWheelSteps;
    L_turnProgress = totalSteps - initSteps;
  }
    analogWrite(EN_LEFT, LOW);
    analogWrite(EN_RIGHT, LOW);
  /* Mapping */
  currentFacing = currentFacing > 0 ? --currentFacing : 3;      //updates the current facing.
}

//turnRight() - turns the robot clockwise 90 degrees
void turnRight()                                                                   //Turns right until calibrated steps have been reached
{
  totalSteps = leftWheelSteps + rightWheelSteps;
  unsigned long initSteps = leftWheelSteps + rightWheelSteps;
  unsigned long R_turnProgress = totalSteps - initSteps;
  unsigned long R_turnSteps = 88; 
  while(R_turnProgress < R_turnSteps)
  {
    digitalWrite(L_PLUS, HIGH); 
    digitalWrite(L_MINUS, LOW);
    digitalWrite(R_PLUS, LOW);
    digitalWrite(R_MINUS, HIGH);
    analogWrite(EN_LEFT, 15);
    analogWrite(EN_RIGHT,15);
    totalSteps = leftWheelSteps + rightWheelSteps;
    R_turnProgress = totalSteps - initSteps;
  }
    analogWrite(EN_LEFT, LOW);
    analogWrite(EN_RIGHT, LOW);

  /* Mapping */
  currentFacing = currentFacing < 3 ? ++currentFacing : 0;      //updates the current facing.
} 

//stepForward - runs both motors to move straight while correcting its path
void stepForward()
{
  unsigned char LKP = 1;
  unsigned char RKP = 1;
  stepProgress = 0;                                            //initialize the amount of distance traveled since last stationary
  long leftError = 0;                                          //the difference between the leftSetpoint and the actual left sensor reading
  long rightError = 0;
  unsigned long initSteps = leftWheelSteps + rightWheelSteps;
  totalSteps = leftWheelSteps + rightWheelSteps;
  //the difference between the rightSetpoint and the actual right sensor reading
  //Movement
  while(stepProgress < 250)//STEP_LENGTH)
  {
    //Serial.println(stepProgress);
    frontSensor = analogRead(F_SENS_PIN);         //updates sensor readings
    leftSensor = analogRead(L_SENS_PIN);
    rightSensor = analogRead(R_SENS_PIN);
    leftError = ideal_leftsensor - analogRead(L_SENS_PIN);          //finds how far the left sensor is from the desired state
    rightError = ideal_rightsensor - analogRead(R_SENS_PIN); 
    totalSteps = leftWheelSteps + rightWheelSteps;
    stepProgress = totalSteps - initSteps;
    Serial.println(leftError);
    //finds how far the right sensor is from the desired state
    /* apply voltage to both motors, complete with proportional control c = Error * Kp, where c is an offset to the motor's PWM voltage*/
    //set forward direction
    digitalWrite(L_PLUS, HIGH); 
    digitalWrite(L_MINUS, LOW);
    digitalWrite(R_PLUS, HIGH);
    digitalWrite(R_MINUS, LOW);
    //set speed
    if(leftError > 0 )
    { 
      unsigned long L_adjust = 90 + (leftError*LKP);
      if(L_adjust > 255)
      L_adjust = 255;
      analogWrite(EN_LEFT, L_adjust);
      analogWrite(EN_RIGHT, 95);
    }
    else
    {
      unsigned long R_adjust = 95 + (rightError*RKP );
      if(R_adjust > 255)
      R_adjust = 255;
      analogWrite(EN_RIGHT, R_adjust );
      analogWrite(EN_LEFT, 90);
    }
    
    if (frontSensor <= F_SENSOR_SETPOINT)                          //if ideal distance from front wall, stop immediately.
      {
        /* turn off both motors */
        fast_stop();
        break;
      } 
      //fast_stop();
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
