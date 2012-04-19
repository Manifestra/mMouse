//FARTFARTFARTFARTPOOT
//digital pin 2 is the feedback from the left motor
//digital pin 3 is the feedback from the right motors

/*These are all ints but should be changed if it is safe. We don't know as of yet how large these numbers will get,
but if we can, we should use a reset mechanism to save space*/
volatile unsigned long leftSteps = 0;                    //the number of steps recorded from the left wheel
volatile unsigned long rightSteps = 0;                   //the number of steps recorded from the right wheel
unsigned int linearDisplacement = 0;                //the linear displacement resulting from the motors. Each time a motor records a step, the linear displacement count increases
unsigned int angularDisplacement = 0;                        //Each time the left wheel records a step, the counter is incremented, each time the right wheel records a step the counter is decremented
                                                    //wheel records a step, the counter is decremented

//incrLeftSteps - increments leftWheelSteps. To be used with interrupt
void incrLeftSteps()
{
  leftWheelSteps++;
}

//incrLeftSteps - increments leftWheelSteps. To be used with interrupt
void incrRightSteps()
{
  leftWheelSteps++;
}

// getLeftVelocity - returns the left wheel's velocity
// @return int - the left wheel's velocity
int getLeftVelocity()
{
  return leftSteps / timeDiff; 
}

// getRightVelocity - returns the right wheel's velocity
// @return int - the right wheel's velocity
int getRightVelocity()
{
  return rightSteps / timeDiff; 
}

// getAngularDisplacement - returns the angular displacement
// @return int - the angular displacement
int getAngularDisplacement()
{
  return leftSteps - rightSteps;
}





