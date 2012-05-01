/*
==============PID CONTROL EXAMPLE==============
int preverrorl; //left motor previous error
int preverrorr; //right motor previous error
int Ierrorl=0; //left motor intergral error
int Ierrorr=0; //right motor intergral error
int encodercountl = 0;
int encodercountr = 0;
int setpoint = 20; //setpoint

void doPID(void)
{
int errorl; //error from left encoder
int errorr; //error from right encoder
int derrorl; //derivative error left
int derrorr; //derivative error right
int cl;
int cr;
int KP = 2; //PID proportional gain constant
float KD = 1; //PID derivative gain constant
float KI = 0.5; //PID intergral gain constant


errorl = setpoint - encodercountl; //calculate error values
errorr = setpoint - encodercountr;

encodercountl = 0; //reset encoder counts ready for next sample
encodercountr = 0;

derrorl = (errorl - preverrorl);
derrorr = (errorr - preverrorr);

cl = ((KP*errorl) + (KD*derrorl) + (KI*Ierrorl)); //PID equations
cr = ((KP*errorr) + (KD*derrorr) + (KI*Ierrorr));

if((OCR0 + cl) > 255) //prevent OCR0 and OCR2 from overrunning 255
OCR0 = 255;
else
OCR0 = OCR0 + cl; //use output from PID equations to alter motor speeds
if((OCR2 + cr) > 255) //where OCR0 and OCR2 are PWM output values
OCR2 = 255;
else
OCR2 = OCR2 + cr;

preverrorl = errorl; //set previous error to current error
preverrorr = errorr;

Ierrorl = Ierrorl + errorl; //add current error to integral error
Ierrorr = Ierrorr + errorr;



}
===============================================
*/

//-> Do nothing
//    }




/*
Displacement
  Displacement: the remaining distance to travel or the remaining angle to turn
  byte leftWheelSteps;
  byte rightWheelSteps;
  byte linDisplacement = the number of steps that both motors need to perform
    to keep track of linDisplacement, we add one to a counter every time either the left wheel or
    the right wheel has a step forward.
  byte angDisplacement = the difference between the displacement of the right wheel and the
    displacement of the left wheel
    to keep track of angDisplacement, we assign positive to the forward of one motor (the left motor)
    and negative to the forward of the other. Each step forward the left wheel makes, we add one to
    the counter. Each step forward the right wheel makes, we subtract one from the counter.
*/

/*
Velocity
byte leftVelocity = linVelocity + angVelocity;
byte rightVelocity = linVelocity - angVelocity;
*/

/*
Acceleration
byte leftAcceleration = linAcceleration + angAcceleration;
byte rightAcceleration = linAcceleration - angAcceleration;
*/

/*
More Displacement
Assume a displacement D to cover. 
Assume we have acceleration acc and deceleration -acc
Assume robot has max speed vMax
Time required to accelerate to vMax is t = vMax / acc
Displacement from 0 to vMax is D == (time * vMax)/2 == (vMax * vMax)/(2 * acc)
  or assuming symmetric deceleration (acceleration 1/2 of the way, deceleration the other 1/2)
  we get D = (vMax * vMax)/acc
  if the displacement is < D = (vMax * vMax)/acc, then we never need to reach maximum speed

if (displacement > (vMax * vMax)/(2 * acc)) {    
  if(currentVelocity < vMax) {
    if(currentAccel < desiredAccel) {
      currentAccel = desiredAccel;                //sets current acceleration to the desired acceleration.
    }
    else {
      currentAccel = 0;                          //if at vMax, stop accelerating
  }
  else if(currentAccel > desiredAccel) {
    currentAcceleration = (desiredAccel * -1);
    }
  }
}
*/
